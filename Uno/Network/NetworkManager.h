//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_NETWORKMANAGER_H
#define CURSEN_NETWORKMANAGER_H


#include "NetworkType.h"
#include "NetworkDevice.h"

class NetworkManager
{

public:

    static const int PORT = 58000;

    static void CreateDevice(NetworkType type);
    static void DestroyDevice();

    static void ProcessNetworkMessages();
    static void WriteMessage(QueueEntry* entry);

    static NetworkDevice& GetDevice();

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
    NetworkType type;

};


#endif //CURSEN_NETWORKMANAGER_H
