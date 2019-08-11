//
// Created by Brandon Martin on 5/20/19.
//

#include <cassert>
#include "NetworkManager.h"
#include "Local.h"
#include "Host.h"
#include "Client.h"

NetworkManager::NetworkManager() :
    device(&Local::local_device), mode(NetworkMode::Uninitialized)
{

}

NetworkManager::~NetworkManager()
{
    device->destroy();
}


void NetworkManager::SetMode(NetworkMode mode)
{
    Instance().mode = mode;
    switch (mode) {
        case NetworkMode::Local:
            Instance().device = &Local::local_device;
            break;
        case NetworkMode::Host:
            Instance().device = &Host::host_device;
            break;
        case NetworkMode::Client:
            Instance().device = &Client::client_device;
            break;
        case NetworkMode::Uninitialized:
            assert(false);
            break;
    }
}

void NetworkManager::ProcessNetworkMessages()
{
    Instance().device->processNetworkMessages();
}

void NetworkManager::WriteMessage(QueueEntry* entry)
{
    Instance().device->writeMessage(entry);
}

void NetworkManager::Destroy()
{
    Instance().device->destroy();
    Instance().device = &Local::local_device;
}


NetworkDevice& NetworkManager::GetDevice()
{
    return *Instance().device;
}

