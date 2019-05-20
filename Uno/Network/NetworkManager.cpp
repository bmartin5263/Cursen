//
// Created by Brandon Martin on 5/20/19.
//

#include <cassert>
#include "NetworkManager.h"
#include "Local.h"
#include "Host.h"
#include "Client.h"
#include "NullDevice.h"

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager::NetworkManager() :
    device(new NullDevice), type(NetworkType::Uninitialized)
{

}

void NetworkManager::InitializeAs(NetworkType type)
{
    delete Instance().device;
    switch (type) {
        case NetworkType::Local:
            Instance().device = new Local();
            break;
        case NetworkType::Host:
            Instance().device = new Host();
            break;
        case NetworkType::Client:
            Instance().device = new Client();
            break;
        case NetworkType::Uninitialized:
            assert(false);
            break;
    }
}

void NetworkManager::ProcessNetworkMessages()
{
    Instance().device->ProcessNetworkMessages();
}

void NetworkManager::Write(QueueEntry entry)
{
    Instance().device->Write(entry);
}
