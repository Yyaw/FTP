/**
 * Created by zichaoyang on 17-5-24.
 * 提供多种服务器类型，比如多进程
 */

#ifndef FTP_SERVERTYPE_H
#define FTP_SERVERTYPE_H

#define MAX_PROCESS 4 //进程的最大数量
#define TV_SEC 3
#define TV_USEC 500
#define MAX_CLIENTS 2048 //最大客户端连接数
//TODO 可以定义一些deal函数的返回状态码
//

#include <zconf.h>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Connection.h"
#include "ProcCommunicate.h"

enum FtpType{
    MULTIPROCESS, //多进程
    MULTITHREAD //多线程
};

/**
 * 用于不同处理服务器模型的接口
 */
//class Deal {
//public:
//    virtual pid_t createConnect(int) = 0;
//};
//
//class Deal_MutliProcess: public Deal {
//public:
//    virtual pid_t createConnect(int);
//};
//
//class Deal_MutliThread: public Deal {
//public:
//    virtual pid_t createConnect(int);
//};

class DealConnect {
    pid_t pid[MAX_PROCESS] = {-1, }; //存放子进程的数组
    int pid_top = 0; //pid数组的顶部
//    Deal *_deal;
//    ShareMemory *father;
    sockaddr *server;
    char *root;
public:
    DealConnect(FtpType _type, sockaddr *_server, char *root){init(_type, root); server=_server;}
    void init(FtpType _type, char *root);
    int deal(int);
    void addPid(pid_t pid);
    int start(FtpType _type, int server_fd);
    void rmPid(pid_t pid);
    int getPid(pid_t pid);
//    void deal_sig(int signal);
};


#endif //FTP_SERVERTYPE_H
