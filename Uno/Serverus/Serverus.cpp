//
// Created by Brandon Martin on 8/24/19.
//

#include <new>
#include "Serverus.h"

NullDevice Serverus::nullDevice = NullDevice();

NetDevice& Serverus::NewServer(SVErrorCd& errorCd)
{
    Server* server = new(std::nothrow) Server;
    if (server == nullptr)
    {
        errorCd = SVErrorCd::ERROR;
        return nullDevice;
    }
    errorCd = SVErrorCd::SUCCESS;
    Instance().registerDevice(server);
    return *server;
}

NetDevice& Serverus::NewClient(SVErrorCd& errorCd)
{
    Client* client = new(std::nothrow) Client;
    if (client == nullptr)
    {
        errorCd = SVErrorCd::ERROR;
        return nullDevice;
    }
    errorCd = SVErrorCd::SUCCESS;
    Instance().registerDevice(client);
    return *client;
}

NullDevice& Serverus::NewNullDevice(SVErrorCd& errorCd)
{
    errorCd = SVErrorCd::SUCCESS;
    return nullDevice;
}

SVErrorCd Serverus::DestroyDevice(NetDevice& device)
{
    Instance().deregisterDevice(&device);
    return SVErrorCd::SUCCESS;
}

void Serverus::registerDevice(NetDevice* device)
{
    this->registered_devices.push_back(device);
}

void Serverus::deregisterDevice(NetDevice* device)
{
    auto it = std::find(std::begin(registered_devices), std::end(registered_devices), device);
    if (it != std::end(registered_devices))
    {
        registered_devices.erase(it);
        delete device;
    }
}
