
#include <map>
#include <list>
#include <string>
#include "event_dispatcher.h"
#include "listener.h"
#include <QDebug>

using namespace std;

namespace spammeli
{
  EventDispatcher::EventDispatcher()
  {
    // ...
  }

  EventDispatcher::~EventDispatcher()
  {
    map<string, list<Listener*> >::iterator si;

    for (si = m_listeners.begin(); si != m_listeners.end(); ++si)
    {
      list<Listener*>::iterator li;

      for (li = si->second.begin(); li != si->second.end(); ++li)
      {
        delete *li;
      }
    }
  }

  void EventDispatcher::Attach(string event_name,
                               Listener* listener)
  {
    m_listeners[event_name].push_back(listener);
  }

  void EventDispatcher::Notify(const Event& evt)
  {
    map<string, list<Listener*> >::iterator si;

    for (si = m_listeners.begin(); si != m_listeners.end(); ++si)
    {
      list<Listener*>::iterator li;

      for (li = si->second.begin(); li != si->second.end(); ++li)
      {
        (*li)->HandleEvent(evt);
      }
    }
  }

  void EventDispatcher::Notify(const string& event_name,
                               const Event &evt)
  {
    map<string, list<Listener*> >::iterator si =
        m_listeners.find(event_name);

    if (si == m_listeners.end())
    {
      return;
    }

    list<Listener*>::iterator li;

    for (li = si->second.begin(); li != si->second.end(); ++li)
    {
      (*li)->HandleEvent(evt);
    }
  }
}

