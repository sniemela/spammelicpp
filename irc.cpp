#include "irc.h"
#include "bot.h"
#include "irc_stream.h"
#include <QTimer>

//timeout value for the connection
#define CONNECTION_TIMEOUT 30000

namespace spammeli
{
  Irc::Irc(const char* host, int port)
  {
    m_host = host;
    m_port = port;
    m_connected = false;
    m_stream = new IrcStream(this);

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

    // Start reading from the socket
    m_stream->start();

    // Start delivering messages from the queue
    // m_message_queue.process();

    return true;
  }

  void Irc::SetBot(Bot* bot)
  {
    m_bot = bot;
  }

  void Irc::OnConnected()
  {
    //connected succesfully. We may leave the eventloop.
    m_eventloop.exit();
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
