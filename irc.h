#ifndef SPAMMELI_IRC_H
#define SPAMMELI_IRC_H

namespace spammeli
{
  class Bot;

  /**
   * Irc class is a connection between IRC network and bot.
   * It is responsible for sending and receiving messages from a socket.
   */
  class Irc
  {
   public:
    enum RuntimeError
    {
      kOK = 0,
      kCONNECTION = 1
    };

    /**
     * Irc constructor
     *
     * @param host The address where irc should connect
     * @param port
     */
    Irc(const char* host, int port);

    /**
     * Establishes connection to a host.
     */
    bool Connect();

    /**
     * The proram main loop.
     *
     * 1. Read data from a socket
     * 2. Parse data and build a Message object
     * 3. Disconnect if interrupted or data is a shutdown message
     * 4. Dispatch the message object to the bot (listeners are informed)
     * 5. continue
     */
    Irc::RuntimeError Run();

    /**
     * Set a bot object to the irc object.
     */
    void SetBot(Bot* bot);

   private:
    const char* m_host;
    int         m_port;
    bool        m_connected;

    /**
     * An instace of Bot class
     */
    Bot*        m_bot;
  };
}

#endif // IRC_H
