#include "bot.h"
#include "irc.h"
#include "listener.h"

namespace spammeli {
  Bot::Bot(Irc* irc) {
    m_irc = irc;
    m_irc->SetBot(this);
  }

  Bot::~Bot() {
    delete m_irc;

    // remove listeners
    std::vector<Listener*>::iterator it;
    for (it = m_listeners.begin(); it != m_listeners.end(); ++it) {
      delete *it;
    }
  }

  int Bot::Run() {

  }

  // TODO: dispatch message object
  void Bot::Dispatch(const char* message) {

  }

  void Bot::AddListener(Listener* listener) {
    listener->SetIrc(m_irc);
    m_listeners.push_back(listener);
  }
}
