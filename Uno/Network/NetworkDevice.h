//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_NETWORKDEVICE_H
#define CURSEN_NETWORKDEVICE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>

#include "../Data/QueueEntry.h"

class NetworkDevice {

public:

    typedef std::function<void(int)> SockFunction;

    NetworkDevice() = default;
    virtual ~NetworkDevice() = default;

    virtual void initialize() = 0;
    virtual void processNetworkMessages() = 0;
    virtual void writeMessage(QueueEntry* entry) = 0;
    virtual void destroy() = 0;

};

#endif //CURSEN_NETWORKDEVICE_H
