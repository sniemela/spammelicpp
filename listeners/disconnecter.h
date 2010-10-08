#ifndef SPAMMELI_LISTENERS_DISCONNECTER_H
#define SPAMMELI_LISTENERS_DISCONNECTER_H

#include "../event.h"
#include "../listener.h"
#include <QtCore/QTimer>

namespace spammeli
{
  /**
   * For testing purposes
   */
  class Disconnecter : public QObject, public Listener
  {
    Q_OBJECT

  public:
    Disconnecter() : timer_(NULL), event_(NULL) {}
    ~Disconnecter();
    virtual void HandleEvent(const Event& evt);

  public slots:
    void OnTimeout();

  private:
    QTimer* timer_;
    const Event* event_;
  };

}

#endif // SPAMMELI_LISTENERS_DISCONNECTER_H
