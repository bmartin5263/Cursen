//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_NETWORKDEVICE_H
#define CURSEN_NETWORKDEVICE_H

#include "../Data/QueueEntry.h"

class NetworkDevice {

public:

    virtual ~NetworkDevice() = default;

    virtual void ProcessNetworkMessages() = 0;
    virtual void Write(QueueEntry entry) = 0;

};

#endif //CURSEN_NETWORKDEVICE_H
