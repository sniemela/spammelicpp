#ifndef SPAMMELI_BOT_H
#define SPAMMELI_BOT_H

namespace spammeli
{
  class Irc;
  class Listener;
  class EventDispatcher;

  class Bot {
   public:
    Bot(Irc* irc);
    ~Bot();
    int Run();

    inline EventDispatcher& GetEventDispatcher()
    {
      return *m_event_dispatcher;
    }

    void Dispatch(const char* message);
    void AddListener(const char* event_name, Listener* listener);

   private:
    Irc* m_irc;
    EventDispatcher* m_event_dispatcher;
  };
}

#endif // BOT_H
