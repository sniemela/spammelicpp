#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <QObject>
#include <QStringList>
#include <QTcpSocket>

namespace spammeli
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

    /**
    * @brief Default constructor
    * @param QObject* parent, parent class instance. Null as default.
    */
    MessageQueue(QObject *parent = 0);

    /**
     * @brief Another constructor
     * @param QTcpSocket* socket, socket object
     */
    MessageQueue(QTcpSocket* socket);
    ~MessageQueue();

    /**
    * @brief Inserts message in to the queue
    * @param const QString& str, message to be inserted
    * @param Priority prio, priority of the message. Normal as default.
    */
    void Insert(const QString& str, Priority prio = Normal);

    /**
    * @brief Remove a message from queue
    * @param const QString& str, message to be removed.
    * @return bool was_removed, true if removed
    */
    bool Remove(const QString& str);
    /**
    * Remove a message from queue. Overloaded with extra
    * parameter priority. If known in which priority queue
    * the message exist then this is faster.
    * @brief Remove a message from queue
    * @param const QString& str, message to be removed
    * @param Priority prio, priority from amongst message is to be searched
    * @return bool was_removed, true if removed.
    */
    bool Remove(const QString& str, Priority prio);

    /**
    * @brief Flush the message queue. Empty it.
    */
    void Flush();
    /**
    * @brief  Overloaded Flush, flush only messages with certain priority.
    * @param  Priority prio, priority to be flushed.
    */
    void Flush(Priority prio);

    /**
    * This function sends all messages in the queue.
    * @brief  Processes all the messages in the queue.
    */
    void Process();

    /**
    * @brief  Checks whether there is messages in the queue.
    * @return bool has_messages, return true if has messages.
    */
    bool HasMessages();
    /**
    * @brief Overloaded, check only messages with certain priority.
    * @param  Priority prio, priority of messages which are to be checked.
    * @return bool has_messages, return true if has messages.
    */
    bool HasMessages(Priority prio);

    /**
    * @brief  Returns the length of the message queue
    * @return int length, length of the queue.
    */
    int Lenght();
    /**
    * @brief  Overloaded, returns number of messages with certain priority.
    * @param  Priority prio, message priority we are interested in.
    * @return int length, number of messages within the certain priority.
    */
    int Lenght(Priority prio);

  private:
    /**
    * @brief  Gives the list corresponding the desired priority.
    * @param  Priority prio, desired priority, default Normal.
    * @return QStringList* list, pointer to the desired list.
    */
    QStringList* GetList(Priority prio = Normal);

    /**
     * @brief Process through messages of given priority.
     *
     */
    void ProcessList(Priority prio);

    QStringList   m_high;
    QStringList   m_normal;
    QStringList   m_low;
    bool          m_processing;

    QTcpSocket*   m_socket;
  };
}

#endif // MESSAGEQUEUE_H
