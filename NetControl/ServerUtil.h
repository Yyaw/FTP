//
// Created by zichaoyang on 17-5-24.
//

#ifndef FTP_SERVERUTIL_H
#define FTP_SERVERUTIL_H

#include <netinet/in.h>
#include <memory.h>
#include <cstdio>

union SOCKADDR_IN_6{
    struct sockaddr_in ip4;
    struct sockaddr_in6 ip6;
};

//ip类型
enum SockType{
    IPV4, IPV6
};

SOCKADDR_IN_6 create(SockType type, int port);

class CreateSockAddr
{
public:
    virtual SOCKADDR_IN_6 create(int port) = 0; //创建sockaddr
};

class CreateSockAddr4: public CreateSockAddr
{
public:
    virtual SOCKADDR_IN_6 create(int port);
};

class CreateSockAddr6: public CreateSockAddr
{
public:
    virtual SOCKADDR_IN_6 create(int port);
};

#endif //FTP_SERVERUTIL_H
