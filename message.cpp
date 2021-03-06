#include "message.h"
#include <QtCore/QRegExp>
#include <QDebug>

namespace spammeli
{
  Message::Message(const QString& raw, Bot* bot)
  {
    raw_ = raw;
    bot_ = bot;
    Parse();
  }

  void Message::Reply(const char* reply_string)
  {
    if (!ShouldReply())
    {
      // Should we do this silently?
      return;
    }

    // Send message to channel or user
    bot_->SendMessage(params_.at(0), reply_string);
  }

  void Message::SendRaw(const char *raw_message)
  {
    bot_->SendRawMessage(raw_message);
  }

  void Message::SendRaw(const QString &raw_message)
  {
    bot_->SendRawMessage(raw_message);
  }

  bool Message::ShouldReply() const
  {
    return command_ == "PRIVMSG";
  }

  void Message::Parse()
  {
    if (raw_.isEmpty())
    {
      return;
    }

    QRegExp irc_rx("(^:(\\S+) )?(\\S+)(.*)");

    if (!irc_rx.exactMatch(raw_))
    {
      return;
    }

    prefix_ = irc_rx.cap(2);
    command_ = irc_rx.cap(3);

    QString raw_params = irc_rx.cap(4);
    raw_params = raw_params.trimmed();

    QRegExp param_reg("(?:^:| :)(.*)$");
    int pos = param_reg.indexIn(raw_params);

    if (pos != -1)
    {
      QString matched_string = param_reg.capturedTexts().at(0);
      int position = raw_params.size() - matched_string.size();

      params_ = raw_params.left(position).split(" ");
      params_.append(param_reg.cap(1));
    }
    else
    {
      params_ = raw_params.split(" ");
    }
  }
}
