#include <QtCore/QCoreApplication>
#include "bot.h"
#include "irc.h"
#include "listener.h"
#include "event.h"
#include <iostream>
#include <string>
#include <QDebug>

using namespace spammeli;

// Test class :)
class PingListener : public Listener {
 public:
  virtual void HandleEvent(const Event& evt);
};

void PingListener::HandleEvent(const Event &evt)
{
  std::string testi;

  if (evt.GetType() == Event::PING) {
    testi += "PING!";
  }

  testi += " eventti tapahtu!";
  std::cout << testi << std::endl;
}

class AutoJoin : virtual public Listener
{
public:
  virtual void HandleEvent(const Event& evt);
};

void AutoJoin::HandleEvent(const Event& evt)
{
  // Ensure that event is CONNECT
  if (evt.GetType() != Event::CONNECT)
  {
    return;
  }

  Message msg = evt.GetMessage();
  msg.Reply("HEIPPA");
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  std::cout << "start test\n";
  Irc* irc = new Irc("irc.quakenet.org", 6667);
//  Bot* bot = new Bot(irc);
//
//  PingListener* ping_listener = new PingListener;
//  bot->AddListener("irc.on_ping", ping_listener);
//
//  AutoJoin* aj = new AutoJoin;
//  bot->AddListener("irc.connect", aj);
//
//  int ret = bot->Run();

  bool bret = irc->Run();
  std::cout << bret << std::endl;

  sleep(5); //wait 5 s

  bret = irc->Disconnect();
  std::cout << "Disconnected: " << bret << std::endl;


  delete irc;
//  delete bot;
  return a.exec();
}
