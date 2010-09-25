#ifndef SPAMMELI_IRC_H
#define SPAMMELI_IRC_H

namespace spammeli {
  class Bot;

  class Irc {
   public:
    enum RuntimeError {
      kOK = 0,
      kCONNECTION = 1
    };

    Irc(const char* host, int port);
    bool Connect();
    Irc::RuntimeError Run();
    void SetBot(Bot* bot);

   private:
    const char* m_host;
    int         m_port;
    bool        m_connected;
    Bot*        m_bot;
  };
}

#endif // IRC_H
