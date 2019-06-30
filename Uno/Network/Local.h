//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_LOCAL_H
#define CURSEN_LOCAL_H


#include "NetworkDevice.h"

class Local : public NetworkDevice
{
public:

    static Local local_device;

    void processNetworkMessages() override;
    void writeMessage(QueueEntry* entry) override;
    void initialize() override;
    void destroy() override;

private:

    Local() = default;

};


#endif //CURSEN_LOCAL_H
