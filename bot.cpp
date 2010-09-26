#include "bot.h"
#include "irc.h"
#include "listener.h"
#include "event_dispatcher.h"

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

  }

  // TODO: dispatch message object
  void Bot::Dispatch(const char* message)
  {

  }

  inline void Bot::AddListener(const char* event_name,
                               Listener* listener)
  {
    m_event_dispatcher->Attach(event_name, listener);
  }
}
