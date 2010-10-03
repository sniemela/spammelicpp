#ifndef SPAMMELI_IRC_H
#define SPAMMELI_IRC_H

#include <QTcpSocket>
#include <QEventLoop>
#include <QtCore/QThread>

namespace spammeli
{
  class Bot;
  class IrcStream;

  /**
   * Irc class is a connection between IRC network and bot.
   * It is responsible for sending and receiving messages from a socket.
   */
  class Irc: public QObject
  {
    Q_OBJECT

   public:
    /**
     * Irc constructor
     *
     * @param host The address where irc should connect
     * @param port
     */
    Irc(const char* host, int port);

    ~Irc();

    /**
     * Establishes connection to a host.
     */
    bool Connect();

    /**
    * Disconnect from host
    */
    bool Disconnect();

    /**
     * The proram main loop.
     *
     * 1. Read data from a socket
     * 2. Parse data and build a Message object
     * 3. Disconnect if interrupted or data is a shutdown message
     * 4. Dispatch the message object to the bot (listeners are informed)
     * 5. continue
     */
    bool Run();

    /**
     * Set a bot object to the irc object.
     */
    void SetBot(Bot* bot);

    /**
     * Returns pointer to the bot.
     */
    Bot* GetBot() { return m_bot; }

    /**
     * Returns pointer to the socket.
     */
    QTcpSocket* GetSocket() { return &m_socket; }

   public slots:
    void OnConnected();
    void OnDisconnected();
    void OnTimeout();

   private:
    const char*   m_host;
    int           m_port;
    bool          m_connected;
    QTcpSocket    m_socket;
    QEventLoop    m_eventloop;

    /**
     * An instace of Bot class
     */
    Bot*          m_bot;

    /**
     * An instance of stream class.
     *
     * This class has the ownership of the stream class.
     */
    IrcStream*    m_stream;
  };
}

#endif // IRC_H
