//
// Created by Brandon Martin on 5/20/19.
//

#ifndef CURSEN_HOST_H
#define CURSEN_HOST_H

#include "NetworkDevice.h"
#include "Uno/Serverus/Socket.h"

class Host : public NetworkDevice
{
public:

    static Host host_device;
    static const int MAX_CONNECTIONS = 3;

    void initialize() override ;
    void destroy() override;
    void processNetworkMessages() override;
    void writeMessage(QueueEntry* entry) override;

    bool startListening();
    void stopListening();
    bool isListening();
    void killAllConnections();

    void addSock(Socket sock);
    void removeSock(Socket sock);

private:

    Host();
    Host(const Host& other) = delete;
    Host& operator = (const Host& other) = delete;
    ~Host();

    Socket listening_sock;
    int num_connections;
    Socket connections[MAX_CONNECTIONS];
    bool listening;

};


#endif //CURSEN_HOST_H
