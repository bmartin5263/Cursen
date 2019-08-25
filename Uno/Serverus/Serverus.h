//
// Created by Brandon Martin on 8/24/19.
//

#ifndef CURSEN_SERVERUS_H
#define CURSEN_SERVERUS_H


#include "Server.h"
#include "Client.h"
#include "NullDevice.h"

class Serverus
{

public:

    /* Network Device Management */

    static Server& NewServer();
    static Client& NewClient();
    static NullDevice& NewNullDevice();

    static void DestroyDevice(NetDevice& device);

private:

};


#endif //CURSEN_SERVERUS_H
