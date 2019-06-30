//
// Created by Brandon Martin on 5/20/19.
//

#include "QueueEntry.h"

QueueEntry::QueueEntry() :
        message(nullptr), type(MessageType::Uninitialized)
{
}

QueueEntry::QueueEntry(MessageType type, DataMessage* msg) :
        message(msg), type(type)
{

}

QueueEntry::QueueEntry(const QueueEntry& other) :
    type(other.type)
{
    this->message = other.message->clone();
}

QueueEntry& QueueEntry::operator=(const QueueEntry& other)
{
    if (&other != this)
    {
        this->message = other.message->clone();
        this->type = other.type;
    }
    return *this;
}

QueueEntry::~QueueEntry()
{
    delete this->message;
}

size_t QueueEntry::serialize(char* const buffer) const
{
    size_t written = 0;
    written += Serializable::Serialize(buffer + written, (int)type);
    written += message->serialize(buffer + written);
    return written;
}

size_t QueueEntry::deserialize(const char* const buffer)
{
    size_t read = 0;
    int raw_type;
    read += Serializable::Deserialize(buffer + read, raw_type);
    type = (MessageType)raw_type;
    message = DataMessage::Parse(type);
    read += message->deserialize(buffer + read);
    return read;
}

size_t QueueEntry::sizeOf() const
{
    return sizeof(QueueEntry);
}

DataMessage* QueueEntry::getMessage()
{
    return message;
}

void QueueEntry::setSender(int id)
{
    message->setSender(id);
}

int QueueEntry::getRecipient()
{
    return message->getRecipient();
}

RecipientType QueueEntry::getRecipientType()
{
    return message->getRecipientType();
}
