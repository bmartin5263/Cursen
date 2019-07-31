//
// Created by Brandon Martin on 5/20/19.
//

#include <Cursen/CursenApplication.h>
#include <Uno/Forms/LobbyForm.h>
#include <Uno/Messages/RequestJoinLobby.h>
#include <Uno/Match/Messages/MatchConnectionSevered.h>
#include "Uno/Messages/ConnectionSevered.h"
#include "Client.h"
#include "NetworkManager.h"

Client Client::client_device;

Client::Client() :
    host_sock(-1), connected(false)
{
    initialize();
}


void Client::processNetworkMessages()
{
    if (connected)
    {
        fd_set read_fds;
        timeval tv;
        FD_ZERO(&read_fds);
        FD_SET(host_sock, &read_fds);

        int max_fd = host_sock;

        tv.tv_sec = 0;
        tv.tv_usec = 0;

        int result = select(max_fd + 1, &read_fds , NULL , NULL , &tv);

        if ((result < 0) && (errno!=EINTR) && (errno != EBADF))
        {
            //auto& x = errno;
            assert(false);
        }

        char buffer[1024] = {};
        char size_buffer[sizeof(size_t)] = {};
        ssize_t readVal;
        if (host_sock != -1 && FD_ISSET(host_sock, &read_fds))
        {
            if ((readVal = read(host_sock, size_buffer, sizeof(size_t))) == 0)
            {
                connectionLost();
            }
            else
            {
                while (readVal < sizeof(size_t))
                {
                    readVal += read(host_sock, size_buffer + readVal, (size_t)sizeof(size_t) - readVal);
                }

                size_t msg_size = 0;
                Serializable::Deserialize(size_buffer, msg_size);

                assert(msg_size > 0);
                assert(msg_size <= 1024);

                readVal = 0;
                while (readVal < msg_size)
                {
                    readVal += read(host_sock, buffer + readVal, msg_size - readVal);
                }

                QueueEntry* entry = new QueueEntry;

                size_t deserialized_bytes = entry->deserialize(buffer);
                assert(deserialized_bytes == msg_size);
                DataManager::ForwardToInput(entry);
            }
        }
    }
}

void Client::writeMessage(QueueEntry* entry)
{
    char buffer[1024];
    char size_buffer[sizeof(size_t)];
    if (connected)
    {
        size_t bytes = entry->serialize(buffer);
        Serializable::Serialize(size_buffer, bytes);
        write(host_sock, size_buffer, sizeof(size_t));
        write(host_sock, buffer, bytes);
    }
}

void Client::initialize()
{
    host_sock = 0;
    connected = false;
}

void Client::destroy()
{
    if (connected)
    {
        closeConnection();
    }
}

bool Client::openConnection(const char* addr)
{
    sockaddr_in6 serv_addr;
    bzero(&serv_addr, sizeof(sockaddr_in6));

    int result;

    host_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (host_sock < 0)
    {
        assert(false);
        return false;
    }

    serv_addr.sin6_family = AF_INET6;
    serv_addr.sin6_port = htons(NetworkManager::PORT);

    result = inet_pton(AF_INET6, addr, &serv_addr.sin6_addr.s6_addr);
    if (result <= 0)
    {
        assert(false);
        return false;
    }

    result = connect(host_sock, (sockaddr *)&serv_addr, sizeof(serv_addr));
    if (result < 0)
    {
        assert(false);
        return false;
    }

    connected = true;
    return true;

}

void Client::closeConnection()
{
    assert(close(host_sock) == 0);
    host_sock = -1;
    connected = false;
}

Client::~Client()
{
    destroy();
}

void Client::connectionLost()
{
    DataMessage* msg;
    switch (DataManager::GetContext())
    {
        case Context::None:
            break;
        case Context::ContextLobby:
            msg = new ConnectionSevered(host_sock);
            msg->setSendType(SendType::Local);
            DataManager::PushMessage(msg);
            break;
        case Context::ContextMatch:
            msg = new MatchConnectionSevered(host_sock);
            msg->setSendType(SendType::Local);
            DataManager::PushMessage(msg);
            break;
    }
    connected = false;
    host_sock = -1;
}
