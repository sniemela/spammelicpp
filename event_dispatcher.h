#ifndef SPAMMELI_EVENT_DISPATCHER_H
#define SPAMMELI_EVENT_DISPATCHER_H

#include <list>
#include <map>

namespace spammeli
{
  class Listener;
  class Event;

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
    void Attach(const char* event_name, Listener* listener);

    /**
     * Notifes all listeners with the event.
     *
     * @param evt An event object
     */
    void Notify(const Event& evt);

    /**
     * Notifies listeners attached to the event_name.
     *
     * @param event_name A name of the event
     * @event evt An event object
     */
    void Notify(const char* event_name, const Event& evt);

   private:

    /**
     * An associative array of Listener objects.
     */
    std::map<const char*, std::list<Listener*> > m_listeners;
  };
}

#endif // EVENT_DISPATCHER_H
