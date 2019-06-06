//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_CLIENT_H
#define CURSEN_CLIENT_H


#include "NetworkDevice.h"

class Client : public NetworkDevice
{
public:

    void ProcessNetworkMessages() override;
    void Write(QueueEntry* entry) override;

};


#endif //CURSEN_CLIENT_H
