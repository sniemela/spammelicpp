#include "irc.h"
#include "bot.h"
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

    //connect signals
    connect(&m_socket, SIGNAL(connected()), this, SLOT(OnConnected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
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
  Irc::RuntimeError Irc::Run()
  {
    if (!m_connected)
    {
      if (!Connect())
      {
        return kCONNECTION;
      }
    }

    // 1. read socket
    // 2. parse line and build message

    // 3. dispatch message(Message class) to listeners

    return kOK;
  }

  void Irc::SetBot(Bot* bot)
  {
    m_bot = bot;
  }

  /**
   * @todo IMPLEMENT!
   */
  void Irc::SendMessage(const QString &message)
  {

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
