//
// Created by Brandon Martin on 5/20/19.
//

#include <Cursen/CursenApplication.h>
#include <Uno/Forms/LobbyForm.h>
#include <Uno/Messages/RequestJoinLobby.h>
#include <Uno/Match/Messages/MatchConnectionSevered.h>
#include "Uno/Messages/ConnectionSevered.h"
#include "Client.h"

Client Client::client_device;

Client::Client() :
    host_sock(), connected(false)
{
    initialize();
}


void Client::processNetworkMessages()
{
    if (connected)
    {
        int host_fd = host_sock.fd();
        fd_set read_fds;
        timeval tv;
        FD_ZERO(&read_fds);
        FD_SET(host_fd, &read_fds);

        int max_fd = host_fd;

        tv.tv_sec = 0;
        tv.tv_usec = 0;

        int result = select(max_fd + 1, &read_fds , NULL , NULL , &tv);

        if ((result < 0) && (errno!=EINTR) && (errno != EBADF))
        {
            //auto& x = errno;
            assert(false);
        }

        ssize_t readVal;
        if (host_fd != -1 && FD_ISSET(host_fd, &read_fds))
        {
            if ((readVal = read(host_fd, size_buffer, sizeof(size_t))) == 0)
            {
                connectionLost();
            }
            else
            {
                while (readVal < sizeof(size_t))
                {
                    readVal += read(host_fd, size_buffer + readVal, (size_t)sizeof(size_t) - readVal);
                }

                size_t msg_size = 0;
                Serializable::Deserialize(size_buffer, msg_size);

                assert(msg_size > 0);
                assert(msg_size <= NetworkManager::MSG_SIZE);

                readVal = 0;
                while (readVal < msg_size)
                {
                    readVal += read(host_fd, buffer + readVal, msg_size - readVal);
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
    char buffer[NetworkManager::MSG_SIZE];
    char size_buffer[sizeof(size_t)];
    if (connected)
    {
        size_t bytes = entry->serialize(buffer);
        Serializable::Serialize(size_buffer, bytes);
        write(host_sock.fd(), size_buffer, sizeof(size_t));
        write(host_sock.fd(), buffer, bytes);
    }
}

void Client::initialize()
{
    host_sock = Socket();
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
    sockaddr_in6 serv_addr = {0};

    if (Socket::CreateSocket(host_sock, Socket::AddrFamily::INET6, Socket::Type::STREAM, 0) == Socket::ErrorCd::ERROR)
    {
        assert(false);
        return false;
    }

    serv_addr.sin6_family = static_cast<int>(Socket::AddrFamily::INET6);
    serv_addr.sin6_port = Socket::Htons(NetworkManager::PORT);

    if (Socket::Inet_pton(Socket::AddrFamily::INET6, addr, &serv_addr.sin6_addr.s6_addr) == Socket::ErrorCd::ERROR)
    {
        assert(false);
        return false;
    }

    if (host_sock.connect((sockaddr *)&serv_addr, sizeof(serv_addr)) == Socket::ErrorCd::ERROR)
    {
        assert(false);
        return false;
    }

    connected = true;
    return true;

}

void Client::closeConnection()
{
    host_sock.shutdown(Socket::Shutdown::READ_WRITE);
    host_sock.close();
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
            msg = new ConnectionSevered(host_sock.fd());
            msg->setSendType(SendType::Local);
            DataManager::PushMessage(msg);
            break;
        case Context::ContextMatch:
            msg = new MatchConnectionSevered(host_sock.fd());
            msg->setSendType(SendType::Local);
            DataManager::PushMessage(msg);
            break;
    }
    //callOnDisconnect(host_sock.fd());
    connected = false;
    host_sock = Socket();
}
