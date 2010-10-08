#ifndef SPAMMELI_MESSAGE_H
#define SPAMMELI_MESSAGE_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <list>
#include "bot.h"

namespace spammeli
{
  /**
   * Message is a convinient object for accessing data sent by an irc server.
   */
  class Message
  {
   public:

    /**
     * Message constructor.
     *
     * It takes a raw data string that is sent by an irc server.
     * In constructor, it parses the raw_string and initializes member
     * variables.
     *
     * @param raw_string A raw string sent by an irc server
     * @param bot Bot object
     */
    Message(const QString& raw, Bot* bot);

    /**
     * Reply to the message.
     *
     * If a user sent a message to the bot, then a reply string is sent back
     * as PRIVMSG #user, otherwise PRIVMSG #channel.
     */
    void Reply(const char* reply_string);

    /**
     * Sends a raw message to a socket.
     */
    void SendRaw(const char* raw_message);
    void SendRaw(const QString& raw_message);

    /**
     * Returns a raw data string.
     *
     * @return QString A raw data string
     */
    QString& GetRaw() { return raw_; }

    /**
     * Returns a command string.
     * A command can be PRIVMSG etc.
     *
     * @return QString A command string
     */
    QString GetCommand() { return command_; }

    /**
     * Returns a prefix string.
     *
     * @return QString A prefix string
     */
    QString& GetPrefix() { return prefix_; }

    /**
     * Returns a list of params.
     *
     * @return QStringList A list of params
     */
    QStringList& GetParams() { return params_; }

    /**
     * Returns true if client should reply
     * to the message.
     */
    bool ShouldReply() const;

   private:

    void Parse();

    /**
     * Raw string.
     */
    QString raw_;

    QString command_;

    QString prefix_;

    QStringList params_;

    /**
     * A pointer to the bot.
     *
     * This is not used for freeing memory.
     */
    Bot* bot_;
  };
}

#endif // MESSAGE_H
