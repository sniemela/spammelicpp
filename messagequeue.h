#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <QObject>
#include <QStringList>

namespace Spammeli
{

  class MessageQueue : public QObject
  {
  Q_OBJECT
  public:

    /**
    * Enum Declaring message priorities.
    */
    enum Priority
    {
      High = 0,
      Normal,
      Low
    };

    MessageQueue(QObject *parent = 0);
    ~MessageQueue();

    void Insert(const QString& str, Priority prio = Normal);
    bool Remove(const QString& str);
    bool Remove(const QString& str, Priority prio);

    void Flush();
    void Flush(Priority prio);

    void Process();

    bool HasMessages();
    bool HasMessages(Priority prio);

    int Lenght();
    int Lenght(Priority prio);

  private:
    QStringList* GetList(Priority prio = Normal);

    QStringList   m_high;
    QStringList   m_normal;
    QStringList   m_low;
  };
}

#endif // MESSAGEQUEUE_H
