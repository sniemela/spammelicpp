#include <QtCore/QCoreApplication>
#include "bot.h"
#include "irc.h"
#include "listener.h"
#include "event.h"
#include "listeners/disconnecter.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <QtCore/QTimer>
#include <QtCore/QObject>

using namespace spammeli;

// Test class :)
class PingListener : public Listener {
 public:
  virtual void HandleEvent(const Event& evt);
};

void PingListener::HandleEvent(const Event &evt)
{
  Message msg = evt.GetMessage();
  msg.SendRaw("PONG :" + msg.GetParams().at(1));
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

}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  std::cout << "start test\n";
  Irc* irc = new Irc("irc.quakenet.org", 6667);
  Bot* bot = new Bot(irc);

  PingListener* ping_listener = new PingListener;
  bot->AddListener("irc.ping", ping_listener);

  AutoJoin* aj = new AutoJoin;
  bot->AddListener("irc.connect", aj);

  // Disconnect automatically from irc in 3 seconds
  Disconnecter* disconnecter = new Disconnecter;
  bot->AddListener("irc.connect", disconnecter);

  int bret = bot->Run();

  std::cout << bret << std::endl;

  sleep(8); //wait 8 s

  bret = irc->Disconnect();
  std::cout << "Disconnected: " << bret << std::endl;


  delete bot;
//  delete bot;
  return a.exec();
}
