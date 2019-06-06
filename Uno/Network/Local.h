//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_LOCAL_H
#define CURSEN_LOCAL_H


#include "NetworkDevice.h"

class Local : public NetworkDevice
{
public:

    void ProcessNetworkMessages() override;
    void Write(QueueEntry* entry) override;

};


#endif //CURSEN_LOCAL_H
