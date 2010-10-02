#ifndef SPAMMELI_BOT_H
#define SPAMMELI_BOT_H

#include <QtCore/QString>

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

    void AddListener(const char* event_name, Listener* listener);
    void SendRawMessage(const QString& message);
    void SendMessage(const QString& receiver, const char* message);

   private:
    Irc* m_irc;
    EventDispatcher* m_event_dispatcher;
  };
}

#endif // BOT_H
