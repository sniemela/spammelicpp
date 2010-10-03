#ifndef SPAMMELI_IRC_STREAM_H
#define SPAMMELI_IRC_STREAM_H

#include <QtCore/QThread>
#include <QTcpSocket>

namespace spammeli
{
  class Irc;
  class Bot;

  const int kBufferSize = 512;

  class IrcStream : public QThread
  {
    Q_OBJECT

   public:

    IrcStream(Irc* irc);

    /**
     * Main loop. Reads data from socket, parses data
     * and triggers events.
     *
     * @see QThread
     */
    void run();

   private:
    /**
     * Parses incoming lines, builds events and dispatches them.
     */
    void Parse(const QString& line);

    QTcpSocket* socket_;
    Irc* irc_;
    Bot* bot_;
  };
}

#endif // IRC_STREAM_H
