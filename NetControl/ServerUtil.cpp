//
// Created by zichaoyang on 17-5-24.
//

#include "ServerUtil.h"

SOCKADDR_IN_6 CreateSockAddr4::create(int port) {

    SOCKADDR_IN_6 sockaddrIn6;

    struct sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof sockaddr);
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(port);

    sockaddrIn6.ip4 = sockaddr;
    return sockaddrIn6;
}

SOCKADDR_IN_6 CreateSockAddr6::create(int port) {

    SOCKADDR_IN_6 sockaddrIn6;

    struct sockaddr_in6 sockaddr;
    bzero(&sockaddr, sizeof sockaddr);
    sockaddr.sin6_family = AF_INET6;
    sockaddr.sin6_port = htons(port);
    sockaddr.sin6_flowinfo = 0;
    sockaddr.sin6_addr = in6addr_any;
    sockaddr.sin6_scope_id = 0;

    sockaddrIn6.ip6 = sockaddr;
    return sockaddrIn6;

}

SOCKADDR_IN_6 create(SockType type, int port)
{
    CreateSockAddr *createSockAddr;
    switch (type)
    {
        case SockType ::IPV4:
            createSockAddr = new CreateSockAddr4;
            break;
        case SockType ::IPV6:
            createSockAddr = new CreateSockAddr6;
        default:
            perror("IP type is not support, please check your ip type is IPV4 or IPV6");
            break;
    }
    return createSockAddr->create(port);
}