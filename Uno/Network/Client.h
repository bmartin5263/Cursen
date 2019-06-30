//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_CLIENT_H
#define CURSEN_CLIENT_H


#include "NetworkDevice.h"

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

    int host_sock;
    bool connected;


};


#endif //CURSEN_CLIENT_H
