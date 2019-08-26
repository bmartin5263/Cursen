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

    void onConnect(const SockFunction& callback)
    {
        f_onConnect = callback;
    }

    void onDisconnect(const SockFunction& callback)
    {
        f_onDisconnect = callback;
    }

    void detachOnConnect()
    {
        f_onConnect = 0;
    }

    void detachOnDisconnect()
    {
        f_onDisconnect = 0;
    }

    void callOnConnect(int sock)
    {
        if (f_onConnect) f_onConnect(sock);
    }

    void callOnDisconnect(int sock)
    {
        if (f_onDisconnect) f_onDisconnect(sock);
    }

protected:

    SockFunction f_onConnect;
    SockFunction f_onDisconnect;

private:



};

#endif //CURSEN_NETWORKDEVICE_H
