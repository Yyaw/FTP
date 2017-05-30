/**
 Created by zichaoyang on 17-5-24.
 管理ftp服务器的连接以及进程的管理
*/

#ifndef FTP_CONNECTION_H
#define FTP_CONNECTION_H

#include "ServerUtil.h"
#include "DealConnect.h"
#include <netinet/in.h>
#include <sys/socket.h>

class Server {

    int _max_listen; //默认监听连接数
    int _port;  //默认端口
    int _server, _client; //套接口描述字
    char *_root;
    SockType _ip_type; //ip类型
    FtpType  _ftp_type; //服务器类型
    SOCKADDR_IN_6 sockaddrIn6; //根据_ip_type来确定实例化ip4还是ip6
    DealConnect *dealConnect;

public:
    /**
     * 初始化ftp数据
     * @param _max_listen 最大监听数
     * @param _port 开启端口号
     * @param _ip_type 地址类型
     * @param _ftp_type ftp服务类型，是多线程还是多进程
     */
    void init(int _max_listen, int _port, SockType _ip_type, FtpType _ftp_type, char *root); //初始化Server的数据

    /**
     * 启动ftp服务器
     */
    void start(); //启动ftp服务器

    /**
     * 结束ftp服务器
     */
    void end(); //停止ftp服务器
};


#endif //FTP_CONNECTION_H
