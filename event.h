#ifndef SPAMMELI_EVENT_H
#define SPAMMELI_EVENT_H

#include "message.h"

namespace spammeli
{
  class Event
  {
   public:
    enum EventTypes
    {
      JOIN = 0,
      PING = 1
    };

    /**
     * Event constructor.
     *
     * @param type type of the event
     * @param message Message object
     */
    Event(EventTypes type, const Message& message) :
        type_(type), message_(message) {}

    ~Event() {}

    /**
     * Returns event type.
     *
     * @return EventTypes
     */
    inline EventTypes GetType() const { return type_; }

    /**
     * Returns a Message object.
     *
     * @return Message
     */
    inline const Message& GetMessage() const { return message_; }

   private:
    EventTypes type_;
    Message message_;
  };
}

#endif // EVENT_H
