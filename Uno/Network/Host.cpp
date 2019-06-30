//
// Created by Brandon Martin on 5/20/19.
//

#include <errno.h>

#include "Uno/Messages/RequestJoinLobby.h"
#include "Uno/Messages/ConnectionSevered.h"
#include "Host.h"
#include "NetworkManager.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"

Host Host::host_device;

Host::Host() :
    num_connections(0), listening_sock(-1), listening(false)
{
    initialize();
}


Host::~Host()
{
    destroy();
}

void Host::initialize()
{
    for (int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        connections[i] = -1;
    }
}

void Host::processNetworkMessages()
{
    //((LobbyForm*)cursen::CursenApplication::GetCurrentForm())->getConsole().setWarning("Hello World!");
    fd_set read_fds;
    timeval tv;
    FD_ZERO(&read_fds);

    int max_fd = 0;

    if (listening)
    {
        FD_SET(listening_sock, &read_fds);
        max_fd = listening_sock;
    }

    for (int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        int socket = connections[i];

        if (socket > 0)
        {
            FD_SET(socket , &read_fds);
        }

        if(socket > max_fd)
        {
            max_fd = socket;
        }
    }

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    int result = select(max_fd + 1, &read_fds , NULL , NULL , &tv);

    if ((result < 0) && (errno!=EINTR) && (errno != EBADF))
    {
        auto& x = errno;
        assert(false);
    }

    if (listening && FD_ISSET(listening_sock, &read_fds))
    {
        int new_socket;
        if ((new_socket = accept(listening_sock, (sockaddr*)NULL, (socklen_t*)NULL)) < 0)
        {
            assert(false);
        }
        ((LobbyForm*)cursen::CursenApplication::GetCurrentForm())->getConsole().setText("Received Connection");
        addSock(new_socket);
    }

    for (int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        char buffer[1024];
        char size_buffer[sizeof(size_t)];
        ssize_t readVal;
        int sock = connections[i];

        if (sock != -1 && FD_ISSET(sock, &read_fds))
        {
            if ((readVal = read(sock, size_buffer, 4)) == 0)
            {
                /* Send a message that the socket disconnected */
                removeSock(sock);
                ((LobbyForm*)cursen::CursenApplication::GetCurrentForm())->getConsole().setWarning("Buh Bye");

                DataMessage* msg = new ConnectionSevered(sock);
                msg->setSendType(SendType::Local);
                DataManager::PushMessage(msg);

            }
            else
            {
                while (readVal < sizeof(size_t))
                {
                    readVal += read(sock, size_buffer + readVal, sizeof(size_t) - readVal);
                }

                size_t msg_size = 0;
                Serializable::Deserialize(size_buffer, msg_size);

                assert(msg_size > 0);
                assert(msg_size <= 1024);

                readVal = 0;
                while (readVal < msg_size)
                {
                    readVal += read(sock, buffer + readVal, msg_size - readVal);
                }

                QueueEntry* entry = new QueueEntry;

                size_t deserialized_bytes = entry->deserialize(buffer);
                entry->setSender(sock);

                assert(deserialized_bytes == msg_size);
                DataManager::ForwardToInput(entry);
            }
        }
    }
}

void Host::writeMessage(QueueEntry* entry)
{
    char buffer[1024];
    char size_buffer[sizeof(size_t)];

    int recipient = entry->getRecipient();
    RecipientType type = entry->getRecipientType();

    size_t bytes = entry->serialize(buffer);
    Serializable::Serialize(size_buffer, bytes);

    switch (type)
    {
        case RecipientType::Uninitialized:
            assert(false);
            break;
        case RecipientType::Broadcast:
            for (auto& sock : connections)
            {
                if (sock != -1)
                {
                    write(sock, size_buffer, sizeof(size_t));
                    write(sock, buffer, bytes);
                }
            }
            break;
        case RecipientType::Broadcast_Except_Recipient:
            for (auto& sock : connections)
            {
                if (sock != -1 && sock != recipient)
                {
                    write(sock, size_buffer, sizeof(size_t));
                    write(sock, buffer, bytes);
                }
            }
            break;
        case RecipientType::Single:
            write(recipient, size_buffer, sizeof(size_t));
            write(recipient, buffer, bytes);
            break;
    }
}

bool Host::startListening()
{
    sockaddr_in6 server_address;
    bzero( &server_address, sizeof(sockaddr_in6));

    int opt = 1;
    int result;

    listening_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (listening_sock < 0) return false;

    result = setsockopt(listening_sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));

    if (result < 0)
    {
        return false;
    }

    server_address.sin6_family = AF_INET6;
    server_address.sin6_addr = in6addr_any;
    server_address.sin6_port = htons(NetworkManager::PORT);

    result = bind(listening_sock, (sockaddr *)&server_address, sizeof(server_address));

    if (result < 0)
    {
        return false;
    }

    result = listen(listening_sock, 3);

    if (result < 0)
    {
        return false;
    }

    listening = true;
    return true;

}

void Host::stopListening()
{
    if (listening_sock != -1)
    {
        close(listening_sock);
        listening = false;
        listening_sock = -1;
    }
}

void Host::destroy()
{
    if (listening)
    {
        stopListening();
    }
    killAllConnections();
}

bool Host::isListening()
{
    return listening;
}

void Host::killAllConnections()
{
    for (int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        if (connections[i] != -1)
        {
            assert(close(connections[i]) == 0);
            connections[i] = -1;
        }
    }
    num_connections = 0;
}

void Host::removeSock(int id)
{
    for (auto& sock : connections)
    {
        if (sock == id)
        {
            assert(close(sock) == 0);
            sock = -1;
            num_connections--;
        }
    }
}

void Host::addSock(int new_sock)
{
    for (int& sock : connections)
    {
        if (sock == -1)
        {
            sock = new_sock;
            num_connections++;
            if (num_connections == MAX_CONNECTIONS)
            {
                stopListening();
            }
            return;
        }
    }
    assert(false);
}