#include "messagequeue.h"
#include <QTcpSocket>

namespace spammeli
{
  MessageQueue::MessageQueue(QObject *parent) :
      QObject(parent)
  {
  }

  MessageQueue::MessageQueue(QTcpSocket* socket)
  {
    m_socket = socket;
    m_processing = false;
  }

  MessageQueue::~MessageQueue()
  {
    //remove all remaining messages.
    Flush();
  }

  void MessageQueue::Insert(const QString& str, Priority prio)
  {
    GetList(prio)->push_back(str);
    Process();
  }

  bool MessageQueue::Remove(const QString& str)
  {
    //init return value
    bool bret = false;

    /* go through high-low lists and try to remove the string */
    bret = Remove(str, High);
    if(!bret) bret = Remove(str, Normal);
    if(!bret) bret = Remove(str, Low);

    //return true on success
    return bret;
  }

  bool MessageQueue::Remove(const QString& str, Priority prio)
  {
    // try to remove the target one. return true on success
    return GetList(prio)->removeOne(str);
  }

  void MessageQueue::Flush()
  {
    /* go through all and flush them */
    m_high.clear();
    m_normal.clear();
    m_low.clear();
  }

  void MessageQueue::Flush(Priority prio)
  {
    GetList(prio)->clear();
  }

  /**
   * TODO: FLood PrOtection!!
   */
  void MessageQueue::Process()
  {
    ProcessList(High);
    ProcessList(Normal);
    ProcessList(Low);
  }

  void MessageQueue::ProcessList(Priority prio)
  {
    QStringList* messages = GetList(prio);

    for (int i = 0; i < messages->size(); ++i)
    {
      QString message = QString(messages->at(i) + "\r\n");
      QString log = QString(">>> Sending: " + message);
      qDebug() << log;

      QByteArray bytes = message.toUtf8();
      qint64 bytes_write = m_socket->write(bytes);

      if (bytes_write == 0)
      {
        qDebug() << "Couldn't write to socket...";
        sleep(2);
        continue;
      }

      messages->removeAt(i);
    }
  }

  bool MessageQueue::HasMessages()
  {
    //init return value
    bool bret = false;

    bret = HasMessages(High);
    if(!bret) bret = HasMessages(Normal);
    if(!bret) bret = HasMessages(Low);

    // return false on empty
    return bret;
  }

  bool MessageQueue::HasMessages(Priority prio)
  {
    // return the negated value
    return !GetList(prio)->isEmpty();
  }

  int MessageQueue::Lenght()
  {
    //init return value
    int ret = 0;

    ret += Lenght(High);
    ret += Lenght(Normal);
    ret += Lenght(Low);

    //return messagequeue length
    return ret;
  }

  int MessageQueue::Lenght(Priority prio)
  {
    //return messagequeue length
    return GetList()->length();
  }

  QStringList* MessageQueue::GetList(Priority prio)
  {
    QStringList* list = 0;

    switch(prio)
    {
    case High:
      list = &m_high;
      break;
    case Normal:
      list = &m_normal;
      break;
    case Low:
      list = &m_low;
      break;
    default:
      break;
    }

    return list;
  }
}
