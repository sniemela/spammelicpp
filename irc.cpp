#include "irc.h"
#include "bot.h"

namespace spammeli {
  Irc::Irc(const char* host, int port) {
    m_host = host;
    m_port = port;
    m_connected = false;
  }

  bool Irc::Connect() {
    return true;
  }

  // TODO: use exceptions
  Irc::RuntimeError Irc::Run() {
    if (!m_connected) {
      if (!Connect()) {
        return kCONNECTION;
      }
    }

    // 1. read socket
    // 2. parse line and build message

    // 3. dispatch message(Message class) to listeners
    const char* message = "!lastfm help";
    m_bot->Dispatch(message);

    return kOK;
  }

  void Irc::SetBot(Bot* bot) {
    m_bot = bot;
  }
}
