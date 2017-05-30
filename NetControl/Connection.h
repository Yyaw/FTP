/**
 * Created by zichaoyang on 17-5-24.
 * 管理一个链接，当server获取一个链接的时候便创建一个Connection对象，此后对
 * 客户端的请求都有Connection对象管理
 */

#ifndef FTP_CONNECTION_H
#define FTP_CONNECTION_H

#include "../CmdControl/AnalyseCmd.h"
#include "ProcCommunicate.h"
#include "../FileControl/FSControl.h"
#include <thread>
#include <sys/socket.h>

#define SELECT_MAX_CLIENTS 1024
#define POLL_MAX_CLIENT 1024
#define EPOLL_MAX_CLIENT 102400

#define OPEN 1
#define LOGIN 2
#define CONNETION 4
#define DISCONNECTION 8

/**
 * Connection类主要分为两个部分，一个部分用来获取父进程传输过来的套接字，另一部分则用于
 * 处理客户端的请求
 * TODO 模型暂时选用select
 */
class Connection {

    /**
     * 共享内存,负责与父进程通信
     */
//    ShareMemory *shareMemory;

    /**
     * 文件管理系统类
     */
    FSControl *fsControl;

    AnalyseCmd analyseCmd;

    int client;

    char *root;

    int status;

public:
    Connection(int client, char *root){
        init(client, root);
    }

    /**
     * 初始化Connection
     */
    void init(int client, char *root);

    /**
     * 启动Connection
     */
    void start();

    /**
     * 发送文件
     * @param filepath 文件路径
     */
    void sendfile(char *filepath);

    /**
     * 发送文本消息
     * @param msg 消息
     */
    void sendStr(char* msg);

    void getFile(char *path);

    /**
     * 定时删除已经失去连接的套接字
     * TODO 若是在select时能判断套接字连接状态，则可以除去这个函数
     */
    void refresh();

    void stop();

    void login(char **msg);

    void pwd();

    void ls(char *);

    void cd(char *path);

    void mymkdir(char *path);

    void myrmdir(char *path);

};


#endif //FTP_CONNECTION_H
