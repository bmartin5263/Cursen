//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_QUEUEENTRY_H
#define CURSEN_QUEUEENTRY_H


#include "../Messages/MessageType.h"
#include "../Messages/DataMessage.h"

class QueueEntry
{

public:

    QueueEntry();
    QueueEntry(int seq, MessageType type, DataMessage* msg);

    DataMessage* message;
    int sequence;
    MessageType type;

};


#endif //CURSEN_QUEUEENTRY_H
