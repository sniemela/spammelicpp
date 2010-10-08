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
    m_irc->Disconnect();
    delete m_event_dispatcher;
    delete m_irc;
  }

  int Bot::Run()
  {
    return m_irc->Run();
  }

  void Bot::AddListener(const char* event_name,
                        Listener* listener)
  {
    m_event_dispatcher->Attach(event_name, listener);
  }

  void Bot::SendMessage(const QString& receiver, const char *message)
  {
    QString msg = "PRIVMSG " + receiver + " :" + message;
    SendRawMessage(msg);
  }

  void Bot::SendRawMessage(const QString &message)
  {
    m_irc->SendMessage(message);
  }

  EventDispatcher* Bot::GetEventDispatcher() const
  {
    return m_event_dispatcher;
  }
}
