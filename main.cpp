#include <QtCore/QCoreApplication>
#include "bot.h"
#include "irc.h"
#include "listener.h"
#include "event.h"
#include <iostream>
#include <string>

using namespace spammeli;

// Test class :)
class PingListener : public Listener {
 public:
  virtual void handleEvent(const Event& evt);
};

void PingListener::handleEvent(const Event &evt)
{
  std::string testi;

  if (evt.GetType() == Event::PING) {
    testi += "PING!";
  }

  testi += " eventti tapahtu!";
  std::cout << testi << std::endl;
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Irc* irc = new Irc("irc.quakenet.org", 6667);
  Bot* bot = new Bot(irc);

  PingListener* ping_listener = new PingListener;
  bot->AddListener("irc.on_ping", ping_listener);

  int ret = bot->Run();

  delete irc;
  delete bot;
  return a.exec();
}
