#include "irc.h"
#include "bot.h"
#include "irc_stream.h"
#include "messagequeue.h"
#include "message.h"
#include "event_dispatcher.h"
#include "event.h";
#include <QTimer>
#include <list>
#include <map>
#include <string>

//timeout value for the connection
#define CONNECTION_TIMEOUT 30000

using namespace std;

namespace spammeli
{
  Irc::Irc(const char* host, int port)
  {
    m_host          = host;
    m_port          = port;
    m_connected     = false;
    m_stream        = new IrcStream(this);
    m_message_queue = new MessageQueue(&m_socket);

    //connect signals
    connect(&m_socket, SIGNAL(connected()), this, SLOT(OnConnected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
  }

  Irc::~Irc()
  {
    if (m_stream->isRunning())
    {
      qDebug() << " STILL RUNNING!";
    }

    m_message_queue->Flush();

    delete m_message_queue;
    delete m_stream;
  }

  bool Irc::Connect()
  {
    //quick out
    if(m_connected)
      return true;

    //create timer connected to the timeout slot
    QTimer timer;
    connect(&timer,SIGNAL(timeout()),this,SLOT(OnTimeout()));
    
    //start timer
    timer.start(CONNECTION_TIMEOUT);

    //connect to host
    m_socket.connectToHost(m_host, m_port);

    if(m_socket.state() < 3) // if smaller then not yet connected
      m_eventloop.exec();

    //stop timer
    timer.stop();
    //disconnect timer from timeout slot
    disconnect(&timer,SIGNAL(timeout()), this,SLOT(OnTimeout()));

    return m_connected;
  }

  bool Irc::Disconnect()
  {
    //quick out
    if(!m_connected)
      return true;

    //create timer connected to the timeout slot
    QTimer timer;
    connect(&timer,SIGNAL(timeout()),this,SLOT(OnTimeout()));

    //start timer
    timer.start(CONNECTION_TIMEOUT);

    // Terminate the stream
    if (m_stream->isRunning())
    {
      m_stream->terminate();
      m_stream->wait(1);
    }

    //disconnect from host
    m_socket.disconnectFromHost();

    if(m_socket.state() != 0) // if 0, then already disconnected
      m_eventloop.exec();

    //stop timer
    timer.stop();
    //disconnect timer from timeout slot
    disconnect(&timer,SIGNAL(timeout()), this,SLOT(OnTimeout()));

    return !m_connected;    //return inverse of m_connected. eg. if m_connected false then the function succeeded
  }

  // TODO: use exceptions
  bool Irc::Run()
  {
    if (!Connect())
    {
      return false;
    }

    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
    m_eventloop.exec();

    // Start delivering messages from the queue
    m_message_queue->Process();

    return true;
  }

  void Irc::OnReadyRead()
  {
    QString line;
    while (m_socket.canReadLine())
    {
      line = m_socket.readLine();
      Parse(line);
    }
  }

  void Irc::Parse(const QString& line)
  {
    Message msg(line, m_bot);
    qDebug() << line;
    QString cmd = msg.GetCommand();
    map<QString, list<Event> > events;

    // Should be 001-004
    if (cmd == "001")
    {
      Event evt(Event::CONNECT, msg);
      events["irc.connect"].push_back(evt);
    }
    else if (cmd == "NOTICE")
    {
      Event evt(Event::NOTICE, msg);
      events["irc.notice"].push_back(evt);
    }
    else if (cmd == "PRIVMSG")
    {
      Event evt(Event::OTHER, msg);
      events["irc.privmsg"].push_back(evt);
    }
    else
    {
      Event evt(Event::OTHER, msg);
      QString key = "irc." + msg.GetCommand().toLower();
      events[key].push_back(evt);
    }

    EventDispatcher* ed = m_bot->GetEventDispatcher();
    map<QString, list<Event> >::iterator mi;
    list<Event>::iterator li;
    for (mi = events.begin(); mi != events.end(); ++mi)
    {
      for (li = mi->second.begin(); li != mi->second.end(); ++li)
      {
        ed->Notify(mi->first.toStdString(), *li);
      }
    }
  }

  void Irc::SetBot(Bot* bot)
  {
    m_bot = bot;
  }

  void Irc::SendMessage(const QString &message,
                        MessageQueue::Priority prio)
  {
    m_message_queue->Insert(message, prio);
  }

  void Irc::OnConnected()
  {
    //connected succesfully. We may leave the eventloop.
    m_eventloop.exit();

    // Send NICK and USER messages
    SendMessage("NICK spammeli");
    SendMessage("USER spammeli 0 * :Spam Anneli");

    m_connected = true;
  }

  void Irc::OnDisconnected()
  {
    //disconnected succesfully. We may leave the eventloop.
    m_eventloop.exit();
    m_connected = false;
  }

  void Irc::OnTimeout()
  {
    //timeout occurred.
    m_eventloop.exit();
  }
}
