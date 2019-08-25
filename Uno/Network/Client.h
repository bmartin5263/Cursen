//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_CLIENT_H
#define CURSEN_CLIENT_H


#include <Uno/Serverus/Socket.h>
#include "NetworkDevice.h"
#include "NetworkManager.h"

class Client : public NetworkDevice
{
public:

    static Client client_device;

    void processNetworkMessages() override;
    void writeMessage(QueueEntry* entry) override;
    void initialize() override;
    void destroy() override;

    bool openConnection(const char* addr);
    void closeConnection();
    void connectionLost();

private:

    Client();
    Client(const Client& other) = delete;
    Client& operator = (const Client& other) = delete;
    ~Client();

    Socket host_sock;
    bool connected;
    char buffer[NetworkManager::MSG_SIZE] = {0};
    char size_buffer[sizeof(size_t)] = {0};


};


#endif //CURSEN_CLIENT_H
