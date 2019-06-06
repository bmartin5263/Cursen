//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_MESSAGEQUEUE_H
#define CURSEN_MESSAGEQUEUE_H

#include <queue>
#include "QueueEntry.h"
#include "Uno/Messages/DataMessage.h"

class MessageQueue
{

public:

    MessageQueue();

    void enqueue(DataMessage* dataMessage);
    void enqueue(QueueEntry* queueEntry);
    QueueEntry* dequeue();

    bool isEmpty();
    void clearAll();

private:

    static int SEQUENCE;

    std::queue<QueueEntry*> queue;

};


#endif //CURSEN_MESSAGEQUEUE_H
