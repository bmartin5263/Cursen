//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_QUEUEENTRY_H
#define CURSEN_QUEUEENTRY_H

#include "Uno/Messages/MessageType.h"
#include "Uno/Messages/DataMessage.h"

class QueueEntry : Serializable
{

public:

    QueueEntry();
    QueueEntry(MessageType type, DataMessage* msg);
    QueueEntry(const QueueEntry& other);
    QueueEntry& operator = (const QueueEntry& other);
    ~QueueEntry();

    void setSender(int id);
    int getRecipient();
    RecipientType getRecipientType();

    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;

    DataMessage* getMessage();

private:

    DataMessage* message;
    MessageType type;

};


#endif //CURSEN_QUEUEENTRY_H
