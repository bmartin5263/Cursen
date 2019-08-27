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

void NetworkManager::OnConnect(const NetworkDevice::SockFunction& callback)
{
    Instance().f_onConnect = callback;
}

void NetworkManager::OnDisconnect(const NetworkDevice::SockFunction& callback)
{
    Instance().f_onDisconnect = callback;
}

void NetworkManager::DetachOnConnect()
{
    Instance().f_onConnect = 0;
}

void NetworkManager::DetachOnDisconnect()
{
    Instance().f_onDisconnect = 0;
}

void NetworkManager::CallOnConnect(int sock)
{
    Instance().f_onConnect(sock);
}

void NetworkManager::CallOnDisconnect(int sock)
{
    Instance().f_onDisconnect(sock);
}

