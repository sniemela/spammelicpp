#ifndef SPAMMELI_LISTENER_H
#define SPAMMELI_LISTENER_H

namespace spammeli
{
  class Event;

  class Listener
  {
   public:
    virtual void HandleEvent(const Event& evt) = 0;
  };
}

#endif // LISTENER_H
