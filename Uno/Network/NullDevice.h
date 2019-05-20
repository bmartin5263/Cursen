//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_NULLDEVICE_H
#define CURSEN_NULLDEVICE_H

#include "NetworkDevice.h"

class NullDevice : public NetworkDevice {
public:

    void ProcessNetworkMessages() override
    {
        // Do nothing
    }

    void Write(QueueEntry entry) override
    {
        // Do nothing
    }


};

#endif //CURSEN_NULLDEVICE_H
