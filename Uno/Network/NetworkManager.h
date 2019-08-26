//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_NETWORKMANAGER_H
#define CURSEN_NETWORKMANAGER_H


#include "NetworkMode.h"
#include "NetworkDevice.h"

class NetworkManager
{

public:

    static const int PORT = 58000;
    static const int MSG_SIZE = 2048;

    static void SetMode(NetworkMode mode);
    static void Destroy();

    static void ProcessNetworkMessages();
    static void WriteMessage(QueueEntry* entry);
    static NetworkDevice& GetDevice();

    static void OnConnect(const NetworkDevice::SockFunction& callback);
    static void OnDisconnect(const NetworkDevice::SockFunction& callback);
    static void DetachOnConnect();
    static void DetachOnDisconnect();

private:


    static NetworkManager& Instance() {
        static NetworkManager instance;
        return instance;
    }

    NetworkManager();
    NetworkManager(const NetworkManager& other) = delete;
    NetworkManager(NetworkManager&& other) noexcept = delete;
    NetworkManager& operator = (const NetworkManager& other) = delete;
    NetworkManager& operator = (NetworkManager&& other) = delete;
    ~NetworkManager();

    NetworkDevice* device;
    NetworkMode mode;

};


#endif //CURSEN_NETWORKMANAGER_H
