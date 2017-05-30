#include "NetControl/Server.h"

int main(int argc, char **argv)
{
    Server server;
    server.init(10, 8888, SockType::IPV4, FtpType::MULTIPROCESS, "/home/zichaoyang/Code");
    server.start();
    server.end();
}