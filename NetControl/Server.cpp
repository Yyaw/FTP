//
// Created by zichaoyang on 17-5-24.
//

#include <iostream>
#include "Server.h"

void Server::init(int _max_listen=100, int _port=2100, SockType _ip_type=SockType::IPV4, FtpType _ftp_type=FtpType::MULTIPROCESS, char *root= "") {
    this->_max_listen = _max_listen;
    this->_port = _port;
    this->_ip_type = _ip_type;
    this->_ftp_type = _ftp_type;
    this->_root = root;
    sockaddrIn6 = create(_ip_type, _port);
    switch (_ip_type)
    {
        case SockType ::IPV4:
            _server = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
            dealConnect = new DealConnect(_ftp_type, (struct sockaddr *)&(this->sockaddrIn6.ip4), root);
            break;
        case SockType ::IPV6:
            _server = socket(AF_INET6, SOCK_STREAM, IPPROTO_IPV6);
            dealConnect = new DealConnect(_ftp_type, (struct sockaddr *)&(this->sockaddrIn6.ip4), root);
        default:
            perror("IP type is not support, please check your ip type is IPV4 or IPV6");
    }

}

void Server::start() {
    struct sockaddr_in sockaddrIn = this->sockaddrIn6.ip4;
    socklen_t len = sizeof sockaddrIn;
    int status = bind(_server, (struct sockaddr *)&sockaddrIn, len);
    perror("bind");
    listen(_server, _max_listen);
    perror("listen");
    this->dealConnect->init(_ftp_type, _root);
    this->dealConnect->start(_ftp_type, _server);
}

void Server::end() {
    
}
//int main(int argc, char **argv)
//{
//
//}