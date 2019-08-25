//
// Created by Brandon Martin on 8/24/19.
//

#ifndef CURSEN_SOCKET_H
#define CURSEN_SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

class Socket
{

public:

    enum class ErrorCd
    {
        SUCCESS, ERROR
    };

    enum class AddrFamily
    {
        LOCAL = AF_LOCAL,
        UNIX = AF_UNIX,
        INET = AF_INET,
        INET6 = AF_INET6,
    };

    enum class Type
    {
        STREAM = SOCK_STREAM,
        DGRAM = SOCK_DGRAM,
        SEQPACKET = SOCK_SEQPACKET
    };

    enum class Option
    {
        DEBUG = SO_DEBUG,
        ACCEPTCONN = SO_ACCEPTCONN,
        BROADCAST = SO_BROADCAST,
        RESUEADDR = SO_REUSEADDR,
        KEEPALIVE = SO_KEEPALIVE,
        LINGER = SO_LINGER,
        OOBINLINE = SO_OOBINLINE,
        SNDBUF = SO_SNDBUF,
        RCVBUF = SO_RCVBUF,
        ERROR = SO_ERROR,
        TYPE = SO_TYPE,
        DONTROUTE = SO_DONTROUTE,
        RCVLOWAT = SO_RCVLOWAT,
        RCVTIMEO = SO_RCVTIMEO,
        SNDLOWAT = SO_SNDLOWAT,
        SNDTIMEO = SO_SNDTIMEO,
        REUSEPORT = SO_REUSEPORT
    };

    enum class Shutdown
    {
        READ = SHUT_RD,
        WRITE = SHUT_WR,
        READ_WRITE = SHUT_RDWR
    };

    enum class Level
    {
        SOCKET = SOL_SOCKET
    };

    Socket();
    Socket(AddrFamily domain, Type type, int protocol);
    Socket(const Socket& other) = default;
    Socket& operator = (const Socket& other);
    ~Socket() = default;

    bool operator == (const Socket & other) const;
    bool operator != (const Socket & other) const;

    static ErrorCd CreateSocket(Socket& sock, AddrFamily domain, Type type, int protocol);
    static ErrorCd Inet_pton(AddrFamily af, const char* src, void* dst);
    static in_port_t Htons(int port);

    bool isValid();
    int fd();

    operator int() const = delete;

    ErrorCd accept(Socket& new_socket, sockaddr* sock_addr, socklen_t* addr_len);
    ErrorCd bind(const sockaddr *address, socklen_t address_len);
    ErrorCd close();
    ErrorCd connect(const sockaddr *address, socklen_t address_len);
    ErrorCd getPeerName(sockaddr *address, socklen_t *address_len);
    ErrorCd getSockName(sockaddr *address, socklen_t *address_len);
    ErrorCd getSockOpt(Option option_name, void *option_value, socklen_t *option_len);
    ErrorCd listen(int backlog);
    ssize_t recv(void *buffer, size_t length, int flags);
    ssize_t recvFrom(void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len);
    ssize_t recvMsg(struct msghdr *message, int flags);
    ssize_t send(const void *message, size_t length, int flags);
    ssize_t sendMsg(const struct msghdr *message, int flags);
    ssize_t sentTo(const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
    ErrorCd setSockOpt(Option option_name, const void *option_value, socklen_t option_len);
    ErrorCd shutdown(Shutdown how);

private:

    int sock_fd;

};


#endif //CURSEN_SOCKET_H
