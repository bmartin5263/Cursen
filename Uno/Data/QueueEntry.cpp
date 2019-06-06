//
// Created by Brandon Martin on 5/20/19.
//

#include "QueueEntry.h"

QueueEntry::QueueEntry() :
        message(nullptr), sequence(-1), type(MessageType::Uninitialized)
{
}

QueueEntry::QueueEntry(int seq, MessageType type, DataMessage* msg) :
        message(msg), sequence(seq), type(type)
{

}

QueueEntry::QueueEntry(const QueueEntry& other) :
    sequence(other.sequence), type(other.type)
{
    this->message = other.message->copy();
}

QueueEntry& QueueEntry::operator=(const QueueEntry& other)
{
    if (&other != this)
    {
        this->message = other.message->copy();
        this->type = other.type;
        this->sequence = other.sequence;
    }
    return *this;
}

QueueEntry::~QueueEntry()
{
    delete this->message;
}
