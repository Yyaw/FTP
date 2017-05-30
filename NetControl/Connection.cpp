//
// Created by zichaoyang on 17-5-24.
//

#include <netinet/in.h>
#include <netinet/tcp.h>
#include "Connection.h"

#define SNBLOCK 1024

#define OK "OK\n"
#define LOGIN_ERROR "LOGIN_ERROR\n"
#define DISCONNECT "LOGOUT"
#define PWDERROR "PWDERROR\n"
#define LSERROR "LSERROR\n"

bool checkExit(char *msg){

}

void Connection::init(int client, char *root) {
    this->client = client;
    fsControl = new FSControl;
    this->root = root;
    const int op = 0;
    setsockopt(client, SOL_SOCKET, SO_KEEPALIVE, &op, sizeof op);
    setsockopt(client, IPPROTO_TCP, TCP_NODELAY, &op, sizeof op);
}

void Connection::start() {
    char msg[1024 * 8];
    ssize_t status;
    while(true)
    {
        status = read(client, msg, 1024 * 8);
        if (status < 0){
            if (errno == EINTR)
                continue;
            perror("Recv data error");
            this->stop();
            break;
        }else if(status == 0)
            continue;
        else{
            printf("Status:%d\n", status);
            msg[status] = '\0';
            Cmd cmd = analyseCmd.analyse(msg);
            printf("%s", msg);
            perror("开始处理数据");
            switch (cmd.cmdType){
                case SNMSG:
                    sendStr(OK);
                    break;
                case OPENHOST:
                    sendStr(OK);
                    break;
                case LOGINFTP:
                    login(cmd.msg);
                    break;
                case EXIT:
                    sendStr(DISCONNECT);
                    stop();
                    break;
                case PWD:
                    pwd();
                    break;
                case LS:
                    ls(cmd.msg[1]);
                    break;
                case CD:
                    cd(cmd.msg[1]);
                    break;
                case MKDIR:
                    mymkdir(cmd.msg[1]);
                    break;
                case GET:
                    sendfile(cmd.msg[1]);
                    break;
                case PUT:
                    getFile(cmd.msg[1]);
                    break;
                default:
                    break;
            }
        }
    }
}

void Connection::refresh() {

}

void Connection::sendfile(char *filepath) {
    filepath = fsControl->getFile(filepath);
    std::ifstream in(filepath, std::fstream::out|std::fstream::binary);
    char buf[1024] = {0};
    int ret = 0;
    while(!in.eof()){
        in.read(buf, sizeof(buf));
        ret = send(client, buf, 1024, 0);
        if (ret < 0){
            perror("Send file error");
            break;
        }
    }
    in.close();

}

void Connection::getFile(char *path) {
    path = fsControl->getFile(path);
    std::ofstream out(path, std::fstream::out | std::fstream::binary);
    int status = 0;
    char buf[1024];
    while (true){
        status = recv(client, buf, 1024, 0);
        if (status <= 0)
            break;
        out.write(buf, status);
    }
    out.close();
}

void Connection::sendStr(char *msg) {
    size_t size = strlen(msg);
//    msg[size] = '\0';
    printf("Size ");
    int index = 0;
    ssize_t send_size = 0;
    ssize_t block = SNBLOCK;
//    int flag = fcntl(client, F_GETFL, 0);
//    fcntl(client, F_SETFL, flag|O_NONBLOCK);
    if (size < block)
        block = size;
    while (index < size){
        send_size = write(client, msg + index, block);
        if (send_size < 0)
            printf("Send msg error");
        else
            index += send_size;
        if (size - index < block)
            block = size - index;
    }
//    fcntl(client, F_SETFL, flag);
    printf("Send Success");
}

void Connection::stop() {
    close(client);
    delete fsControl;
}

void Connection::login(char **msg) {
    char *username = msg[1];
    char *password = msg[2];
    if (username == nullptr || password == nullptr){
        sendStr(LOGIN_ERROR);
    }
    printf("%s-%s-%s", msg[0], msg[1], msg[2]);
    bool flag = fsControl->login(username, password);
    if (flag){
        sendStr(OK);
        status = CONNETION;
        User user = FSControl::getUser(username);
        fsControl->init(user, root);
    } else
        sendStr(LOGIN_ERROR);
}

void Connection::pwd() {
    char *root = fsControl->getRoot();
    if (root == NULL){
        sendStr(PWDERROR);
    }
    int len = strlen(root);
    root[len] = '\n';
    root[len + 1] = '\0';
    sendStr(root);
}

void Connection::cd(char *path) {
    path =fsControl->getFile(path);
    if (fsControl->cd(path)){
        ls(path);
    }
}

void Connection::ls(char *path) {

    char** msg;
    int index = fsControl->ls(path, msg);
    if (index == 0) {
        sendStr(LSERROR);
    }
    char *result = new char[1024 * 8];
    for (int i=0; i<index; i++)
    {
        strcat(result, msg[i]);
        strcat(result, "----");
    }
    strcat(result, "\n");
    sendStr(result);
}

void Connection::mymkdir(char *path) {
    fsControl->my_mkdir(path);
    sendStr(OK);
}