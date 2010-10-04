#include "irc_stream.h"
#include "irc.h"
#include "message.h"
#include "bot.h"
#include <QTcpSocket>
#include <QtCore/QByteArray>
#include <QtCore/QString>

namespace spammeli
{
  IrcStream::IrcStream(Irc* irc)
  {
    irc_ = irc;
    bot_ = irc->GetBot();
    socket_ = irc->GetSocket();
  }

  void IrcStream::run()
  {
    while (true)
    {
      QByteArray bytes_read = socket_->read(spammeli::kBufferSize);

      if (bytes_read.isEmpty())
      {
        qDebug() << "O OU bytes_read is empty";
        break;
      }

      QString input = QString(bytes_read);
      Parse(input);
    }
  }

  void IrcStream::Parse(const QString& line)
  {
    Message msg(line, bot_);
    qDebug() << msg.GetPrefix();
    //TODO: Verify/Validate incoming message.
  }
}
