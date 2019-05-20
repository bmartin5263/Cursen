//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_HOST_H
#define CURSEN_HOST_H


#include "NetworkDevice.h"

class Host : public NetworkDevice
{
public:

    void ProcessNetworkMessages() override;
    void Write(QueueEntry entry) override;

};


#endif //CURSEN_HOST_H
