#include <QtCore/QCoreApplication>
#include "bot.h"
#include "irc.h"
#include <iostream>

using namespace spammeli;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Irc* irc = new Irc("irc.quakenet.org", 6667);
  Bot* bot = new Bot(irc);

  //PingListener* ping_listener = new PingListener;
  //bot->AddListener("irc.on_ping", ping_listener);

  int ret = bot->Run();

  delete irc;
  delete bot;
  return a.exec();
}
