//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_NETWORKDEVICE_H
#define CURSEN_NETWORKDEVICE_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <cassert>

#include "../Data/QueueEntry.h"

class NetworkDevice {

public:

    NetworkDevice() = default;
    virtual ~NetworkDevice() = default;

    virtual void initialize() = 0;
    virtual void processNetworkMessages() = 0;
    virtual void writeMessage(QueueEntry* entry) = 0;
    virtual void destroy() = 0;

private:

};

#endif //CURSEN_NETWORKDEVICE_H
