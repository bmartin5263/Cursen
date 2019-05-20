//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_DATAMESSAGE_H
#define CURSEN_DATAMESSAGE_H


#include "MessageType.h"
#include "SendType.h"

class DataMessage
{

public:

    DataMessage() = default;
    virtual ~DataMessage() = default;

    virtual SendType getSendType() = 0;
    virtual MessageType getType() = 0;
    virtual void execute() = 0;

};


#endif //CURSEN_DATAMESSAGE_H
