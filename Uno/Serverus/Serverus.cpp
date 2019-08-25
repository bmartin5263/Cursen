//
// Created by Brandon Martin on 8/24/19.
//

#include "Serverus.h"

Server& Serverus::NewServer()
{
    Server* server = new Server;
    return *server;
}

Client& Serverus::NewClient()
{
    Client* client = new Client;
    return *client;
}

NullDevice& Serverus::NewNullDevice()
{
    NullDevice* nullDevice = new NullDevice;
    return *nullDevice;
}

void Serverus::DestroyDevice(NetDevice& device)
{
}
