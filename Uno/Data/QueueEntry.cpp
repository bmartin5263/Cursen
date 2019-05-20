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
