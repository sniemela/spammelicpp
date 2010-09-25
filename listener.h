#ifndef SPAMMELI_LISTENER_H
#define SPAMMELI_LISTENER_H

namespace spammeli {
  class Irc;

  class Listener {
   public:
    virtual void SetIrc(Irc* irc) { m_irc = irc; }

   private:
    Irc* m_irc;
  };
}

#endif // LISTENER_H
