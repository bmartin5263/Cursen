//
// Created by Brandon Martin on 5/20/19.
//

#include <cassert>
#include "NetworkManager.h"
#include "Local.h"
#include "Host.h"
#include "Client.h"

NetworkManager::NetworkManager() :
    device(&Local::local_device), type(NetworkType::Uninitialized)
{

}

NetworkManager::~NetworkManager()
{
}


void NetworkManager::CreateDevice(NetworkType type)
{
    Instance().type = type;
    switch (type) {
        case NetworkType::Local:
            Instance().device = &Local::local_device;
            break;
        case NetworkType::Host:
            Instance().device = &Host::host_device;
            break;
        case NetworkType::Client:
            Instance().device = &Client::client_device;
            break;
        case NetworkType::Uninitialized:
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

void NetworkManager::DestroyDevice()
{
    Instance().device->destroy();
}


NetworkDevice& NetworkManager::GetDevice()
{
    return *Instance().device;
}

