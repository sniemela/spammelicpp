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

  int ret = bot->Run();

  delete bot;
  return a.exec();
}
