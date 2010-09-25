#ifndef SPAMMELI_BOT_H
#define SPAMMELI_BOT_H

#include <vector>

namespace spammeli {
  class Irc;
  class Listener;

  class Bot {
   public:
    Bot(Irc* irc);
    ~Bot();
    int Run();
    void Dispatch(const char* message);
    void AddListener(Listener* listener);
   private:
    Irc* m_irc;
    std::vector<Listener*> m_listeners;
  };
}

#endif // BOT_H
