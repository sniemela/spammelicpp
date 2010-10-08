#include <QtCore/QTimer>
#include <QtCore/QObject>
#include "disconnecter.h"

namespace spammeli
{
  Disconnecter::~Disconnecter()
  {
    if (timer_ != NULL)
    {
      delete timer_;
    }
  }

  void Disconnecter::HandleEvent(const Event &evt)
  {
    qDebug("TRIGGERED");
    event_ = &evt;
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(OnTimeout()));
    timer_->start(3000);
  }

  void Disconnecter::OnTimeout()
  {
    timer_->stop();

    if (event_ != NULL)
    {
      qDebug("Sending QUIT");
      Message msg = event_->GetMessage();
      msg.SendRaw("QUIT");
    }
  }
}
