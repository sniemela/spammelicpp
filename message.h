#ifndef SPAMMELI_MESSAGE_H
#define SPAMMELI_MESSAGE_H

namespace spammeli
{
  class Bot;

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
    Message(const char* raw_string, Bot* bot) :
        raw_(raw_string), bot_(bot) {}

    /**
     * Reply to the message.
     *
     * If a user sent a message to the bot, then a reply string is sent back
     * as PRIVMSG #user, otherwise PRIVMSG #channel.
     */
    void Reply(const char* reply_string);

   private:
    /**
     * Raw string.
     */
    const char* raw_;

    /**
     * Pointer to a bot object.
     *
     * This is not used for freeing memory.
     */
    Bot* bot_;
  };
}

#endif // MESSAGE_H
