//
// Created by Brandon Martin on 8/24/19.
//

#ifndef CURSEN_SERVERUS_H
#define CURSEN_SERVERUS_H


#include <vector>
#include "Server.h"
#include "Client.h"
#include "NullDevice.h"

enum class SVErrorCd
{
    SUCCESS = 0,
    ERROR = 1
};

class Serverus
{

public:

    /* Network Device Management */

    static NetDevice& NewServer(SVErrorCd& errorCd);
    static NetDevice& NewClient(SVErrorCd& errorCd);
    static NullDevice& NewNullDevice(SVErrorCd& errorCd);

    static SVErrorCd DestroyDevice(NetDevice& device);

private:

    static NullDevice nullDevice;
    static Serverus& Instance() {
        static Serverus instance;
        return instance;
    }

    void registerDevice(NetDevice* device);
    void deregisterDevice(NetDevice* device);

    std::vector<NetDevice*> registered_devices;

};


#endif //CURSEN_SERVERUS_H
