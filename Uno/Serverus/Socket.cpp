//
// Created by Brandon Martin on 8/24/19.
//

#include "Socket.h"
#include <unistd.h>

Socket::Socket() :
    sock_fd(-1)
{
}

Socket::ErrorCd Socket::CreateSocket(Socket& sock, AddrFamily domain, Type type, int protocol)
{
    sock.sock_fd = socket(static_cast<int>(domain), static_cast<int>(type), protocol);
    if (sock.sock_fd == -1) return ErrorCd::ERROR;
    return ErrorCd::SUCCESS;
}


Socket::ErrorCd Socket::accept(Socket& new_socket, sockaddr* sock_addr, socklen_t* addr_len)
{
    new_socket.sock_fd = ::accept(sock_fd, sock_addr, addr_len);
    if (new_socket.sock_fd == -1) return ErrorCd::ERROR;
    return ErrorCd::SUCCESS;

}

Socket::ErrorCd Socket::bind(const sockaddr* address, socklen_t address_len)
{
    int cd = ::bind(sock_fd, address, address_len);
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

Socket::ErrorCd Socket::close()
{
    int cd = ::close(sock_fd);
    if (cd == 0)
    {
        sock_fd = -1;
        return ErrorCd::SUCCESS;
    }
    else
    {
        return ErrorCd::ERROR;
    }
}

Socket::ErrorCd Socket::connect(const sockaddr* address, socklen_t address_len)
{
    int cd = ::connect(sock_fd, address, address_len);
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

Socket::ErrorCd Socket::getPeerName(sockaddr* address, socklen_t* address_len)
{
    int cd = getpeername(sock_fd, address, address_len);
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

Socket::ErrorCd Socket::getSockName(sockaddr* address, socklen_t* address_len)
{
    int cd = getsockname(sock_fd, address, address_len);
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

Socket::ErrorCd Socket::getSockOpt(Option option_name, void* option_value, socklen_t* option_len)
{
    int cd = getsockopt(sock_fd, static_cast<int>(Level::SOCKET), static_cast<int>(option_name), option_value, option_len);
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

Socket::ErrorCd Socket::listen(int backlog)
{
    int cd = ::listen(sock_fd, backlog);
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

ssize_t Socket::recv(void* buffer, size_t length, int flags)
{
    return ::recv(sock_fd, buffer, length, flags);
}

ssize_t Socket::recvFrom(void* buffer, size_t length, int flags, sockaddr* address, socklen_t* address_len)
{
    return ::recvfrom(sock_fd, buffer, length, flags, address, address_len);
}

ssize_t Socket::recvMsg(msghdr* message, int flags)
{
    return recvmsg(sock_fd, message, flags);
}

ssize_t Socket::send(const void* message, size_t length, int flags)
{
    return ::send(sock_fd, message, length, flags);
}

ssize_t Socket::sendMsg(const msghdr* message, int flags)
{
    return ::sendmsg(sock_fd, message, flags);
}

ssize_t Socket::sentTo(const void* message, size_t length, int flags, const sockaddr* dest_addr, socklen_t dest_len)
{
    return ::sendto(sock_fd, message, length, flags, dest_addr, dest_len);
}

Socket::ErrorCd Socket::setSockOpt(Option option_name, const void* option_value, socklen_t option_len)
{
    int cd = ::setsockopt(sock_fd, static_cast<int>(Level::SOCKET), static_cast<int>(option_name), option_value, option_len);
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

Socket::ErrorCd Socket::shutdown(Shutdown how)
{
    int cd = ::shutdown(sock_fd, static_cast<int>(how));
    return cd == 0 ? ErrorCd::SUCCESS : ErrorCd::ERROR;
}

bool Socket::isValid()
{
    return sock_fd != -1;
}

int Socket::fd()
{
    return sock_fd;
}

bool Socket::operator==(const Socket& other) const
{
    return this->sock_fd == other.sock_fd;
}

bool Socket::operator!=(const Socket& other) const
{
    return !(*this == other);
}

Socket& Socket::operator=(const Socket& other)
{
    this->sock_fd = other.sock_fd;
    return *this;
}
