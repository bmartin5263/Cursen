//
// Created by Brandon Martin on 5/20/19.
//

#include "MessageQueue.h"

int MessageQueue::SEQUENCE = 0xAA00;

MessageQueue::MessageQueue()
{

}

void MessageQueue::enqueue(DataMessage* dataMessage)
{
    QueueEntry* entry = new QueueEntry(SEQUENCE++, dataMessage->getType(), dataMessage);
    queue.push(entry);
}

void MessageQueue::enqueue(QueueEntry* queueEntry)
{
    queue.push(queueEntry);
}

QueueEntry* MessageQueue::dequeue()
{
    QueueEntry* entry = queue.front();
    queue.pop();
    return entry;
}

void MessageQueue::clearAll()
{
    while (!isEmpty()) {
        QueueEntry* entry = queue.front();
        delete entry;
        queue.pop();
    }
}

bool MessageQueue::isEmpty()
{
    return queue.empty();
}
