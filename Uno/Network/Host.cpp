//
// Created by Brandon Martin on 5/20/19.
//

#include <errno.h>

#include "Uno/Messages/RequestJoinLobby.h"
#include "Uno/Messages/ConnectionSevered.h"
#include "Host.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"

Host Host::host_device;

Host::Host() :
    num_connections(0), listening(false)
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
        connections[i] = Socket();
    }
}

void Host::processNetworkMessages()
{
    //((LobbyForm*)cursen::CursenApplication::GetCurrentForm())->getConsole().setWarning("Hello World!");
    fd_set read_fds;
    timeval tv;
    FD_ZERO(&read_fds);

    int max_fd = 0;
    int listening_fd = listening_sock.fd();

    if (listening)
    {
        FD_SET(listening_fd, &read_fds);
        max_fd = listening_fd;
    }

    for (int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        Socket socket = connections[i];
        int socket_fd = socket.fd();

        if (socket_fd > 0)
        {
            FD_SET(socket_fd, &read_fds);
        }

        if(socket_fd > max_fd)
        {
            max_fd = socket_fd;
        }
    }

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    int result = select(max_fd + 1, &read_fds , NULL , NULL , &tv);

    if ((result < 0) && (errno!=EINTR) && (errno != EBADF))
    {
        //auto& x = errno;
        assert(false);
    }

    if (listening && FD_ISSET(listening_fd, &read_fds))
    {
        Socket new_socket;
        if (listening_sock.accept(new_socket, nullptr, nullptr) == Socket::ErrorCd::ERROR)
        {
            assert(false);
        }
        ((LobbyForm*)cursen::CursenApplication::GetCurrentForm())->getConsole().setText("Received Connection");
        addSock(new_socket);
        //callOnConnect(new_socket.fd());
    }

    for (int i = 0; i < MAX_CONNECTIONS; ++i)
    {
        ssize_t readVal;
        Socket sock = connections[i];
        int sock_fd = sock.fd();

        if (sock.isValid() && FD_ISSET(sock_fd, &read_fds))
        {
            if ((readVal = read(sock_fd, size_buffer, 4)) == 0)
            {
                /* Send a message that the socket disconnected */
                removeSock(sock);
                if (DataManager::GetContext() == Context::ContextLobby) {
                    ((LobbyForm*)cursen::CursenApplication::GetCurrentForm())->getConsole().setWarning("Buh Bye");
                    DataMessage* msg = new ConnectionSevered(sock_fd);
                    msg->setSender(sock_fd);
                    msg->setSendType(SendType::Local);
                    DataManager::PushMessage(msg);
                }
                //callOnDisconnect(sock.fd());

            }
            else
            {
                while (readVal < sizeof(size_t))
                {
                    readVal += read(sock_fd, size_buffer + readVal, sizeof(size_t) - readVal);
                }

                size_t msg_size = 0;
                Serializable::Deserialize(size_buffer, msg_size);

                assert(msg_size > 0);
                assert(msg_size <= NetworkManager::MSG_SIZE);

                readVal = 0;
                while (readVal < msg_size)
                {
                    // TODO what if read returns 0?
                    readVal += read(sock_fd, buffer + readVal, msg_size - readVal);
                }

                QueueEntry* entry = new QueueEntry;

                size_t deserialized_bytes = entry->deserialize(buffer);
                static_cast<void>(deserialized_bytes);
                entry->setSender(sock_fd);

                assert(deserialized_bytes == msg_size);
                DataManager::ForwardToInput(entry);
            }
        }
    }
}

void Host::writeMessage(QueueEntry* entry)
{
    if (num_connections > 0)
    {
        int recipient = entry->getRecipient();
        char buffer[NetworkManager::MSG_SIZE];
        char size_buffer[sizeof(size_t)];

        RecipientType type = entry->getRecipientType();

        size_t bytes = entry->serialize(buffer);
        Serializable::Serialize(size_buffer, bytes);

        switch (type)
        {
            case RecipientType::Uninitialized:
                assert(false);
                break;
            case RecipientType::Broadcast:
                for (auto sock : connections)
                {
                    if (sock.fd() != -1)
                    {
                        write(sock.fd(), size_buffer, sizeof(size_t));
                        write(sock.fd(), buffer, bytes);
                    }
                }
                break;
            case RecipientType::Broadcast_Except_Recipient:
                for (auto sock : connections)
                {
                    if (sock.fd() != -1 && sock.fd() != recipient)
                    {
                        write(sock.fd(), size_buffer, sizeof(size_t));
                        write(sock.fd(), buffer, bytes);
                    }
                }
                break;
            case RecipientType::Single:
                if (recipient != -1 && recipient != DataManager::LOOP_BACK)
                {
                    write(recipient, size_buffer, sizeof(size_t));
                    write(recipient, buffer, bytes);
                    break;
                }
        }
    }
}

bool Host::startListening()
{
    sockaddr_in6 server_address;
    bzero(&server_address, sizeof(sockaddr_in6));

    int opt = 1;
    if (Socket::CreateSocket(listening_sock, Socket::AddrFamily::INET6, Socket::Type::STREAM, 0) == Socket::ErrorCd::ERROR)
    {
        return false;
    }
    if (listening_sock.setSockOpt(Socket::Option::REUSEPORT, &opt, sizeof(int)) == Socket::ErrorCd::ERROR)
    {
        return false;
    }
    server_address.sin6_family = AF_INET6;
    server_address.sin6_addr = in6addr_any;
    server_address.sin6_port = htons(NetworkManager::PORT);
    if (listening_sock.bind((sockaddr *)&server_address, sizeof(server_address)) == Socket::ErrorCd::ERROR)
    {
        return false;
    }
    if (listening_sock.listen(3) == Socket::ErrorCd::ERROR)
    {
        return false;
    }
    listening = true;
    return true;

}

void Host::stopListening()
{
    if (listening_sock.isValid())
    {
        listening_sock.shutdown(Socket::Shutdown::READ_WRITE);
        listening_sock.close();
        listening = false;
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
        if (connections[i].isValid())
        {
            connections[i].shutdown(Socket::Shutdown::READ_WRITE);
            connections[i].close();
        }
    }
    num_connections = 0;
}

void Host::removeSock(Socket socket)
{
    for (auto& sock : connections)
    {
        if (sock == socket)
        {
            sock.shutdown(Socket::Shutdown::READ_WRITE);
            sock.close();
            num_connections--;
        }
    }
}

void Host::addSock(Socket new_sock)
{
    for (auto& sock : connections)
    {
        if (!sock.isValid())
        {
            sock = new_sock;
            ++num_connections;
            if (num_connections == MAX_CONNECTIONS)
            {
                stopListening();
            }
            return;
        }
    }
    assert(false);
}