#ifndef SPAMMELI_EVENT_DISPATCHER_H
#define SPAMMELI_EVENT_DISPATCHER_H

#include <list>
#include <map>

namespace spammeli
{
  class Listener;

  /**
   * Event dispatcher is responsible for dispatching events to
   * listeners.
   */
  class EventDispatcher
  {
   public:
    EventDispatcher();

    /**
     * EventDispatcher destructor
     *
     * Loops through all listeners and deletes them
     * from memory.
     */
    ~EventDispatcher();

    /**
     * Attach a listener object to the named event.
     *
     * @param event_name
     * @param listener Listener object
     */
    inline void Attach(const char* event_name, Listener* listener);

   private:

    /**
     * An associative array of Listener objects.
     */
    std::map<const char*, std::list<Listener*> > m_listeners;
  };
}

#endif // EVENT_DISPATCHER_H
