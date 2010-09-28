#include "bot.h"
#include "irc.h"
#include "listener.h"
#include "event_dispatcher.h"
#include "event.h"
#include "message.h"

namespace spammeli
{
  Bot::Bot(Irc* irc)
  {
    m_irc = irc;
    m_irc->SetBot(this);
    m_event_dispatcher = new EventDispatcher;
  }

  Bot::~Bot()
  {
    delete m_event_dispatcher;
  }

  int Bot::Run()
  {
   // testing...
    Message msg("PING: 1111", this);
    Event evt(Event::PING, msg);

    Message msg2("", this);
    Event evt2(Event::CONNECT, msg2);

    m_event_dispatcher->Notify(evt);
    m_event_dispatcher->Notify("irc.connect", evt2);
    return 1;
  }

  void Bot::AddListener(const char* event_name,
                        Listener* listener)
  {
    m_event_dispatcher->Attach(event_name, listener);
  }
}
