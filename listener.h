#ifndef SPAMMELI_LISTENER_H
#define SPAMMELI_LISTENER_H

namespace spammeli
{
  class Irc;

  class Listener
  {
   public:
    virtual void SetIrc(const Irc* irc) { m_irc = irc; }

   protected:
    const Irc* m_irc;
  };
}

#endif // LISTENER_H
