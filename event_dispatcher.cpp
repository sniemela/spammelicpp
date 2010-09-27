
#include <map>
#include <list>
#include "event_dispatcher.h"
#include "listener.h"

namespace spammeli
{
  EventDispatcher::EventDispatcher()
  {
    // ...
  }

  EventDispatcher::~EventDispatcher()
  {
    std::map<const char*, std::list<Listener*> >::iterator si;
    std::list<Listener*>::iterator li;

    for (si = m_listeners.begin(); si != m_listeners.end(); ++si)
    {
      for (li = si->second.begin(); li != si->second.end(); ++li)
      {
        delete *li;
      }
    }
  }

  void EventDispatcher::Attach(const char* event_name,
                               Listener* listener)
  {
    m_listeners[event_name].push_back(listener);
  }

  void EventDispatcher::Notify(const Event& evt)
  {
    std::map<const char*, std::list<Listener*> >::iterator si;
    std::list<Listener*>::iterator li;
    for (si = m_listeners.begin(); si != m_listeners.end(); ++si)
    {
      for (li = si->second.begin(); li != si->second.end(); ++li)
      {
        (*li)->handleEvent(evt);
      }
    }
  }

  void EventDispatcher::Notify(const char *event_name,
                               const Event &evt)
  {
    // implement!
  }
}

