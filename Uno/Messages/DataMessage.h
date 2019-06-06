//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_DATAMESSAGE_H
#define CURSEN_DATAMESSAGE_H


#include "Uno/Data/Context.h"
#include "MessageType.h"
#include "SendType.h"
#include "Serializable.h"

class DataMessage : public Serializable
{

public:

    DataMessage() :
            sendType(SendType::Uninitialized)
    {}

    virtual ~DataMessage() = default;

    virtual MessageType getType() = 0;
    virtual Context getContext() = 0;
    virtual void execute() = 0;
    virtual DataMessage* copy() = 0;

    SendType getSendType() { return sendType; };
    void setSendType(SendType type) { this->sendType = type; };

private:

    SendType sendType;

};


#endif //CURSEN_DATAMESSAGE_H
