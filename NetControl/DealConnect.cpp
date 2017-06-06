//
// Created by zichaoyang on 17-5-24.
//

#include <wait.h>
#include "DealConnect.h"


static void deal_sig(int signal) {
    if (signal == SIGCHLD){
        pid_t pid;
        int status;
        pid = waitpid(pid, &status, WNOHANG);
        if (WIFEXITED(status)){
//            rmPid(pid);
            printf("子进程%d已经退出", pid);
        }else if (WIFSIGNALED(status)){
            //异常退出
        }else{
            //子进程暂停
        }
    }
}

void DealConnect::init(FtpType _type, char *root) {
    //TODO 创建属于父进程的共享内存
//    father = new ShareMemory;
//    father->setValue();
    this->root = root;
    signal(SIGCHLD, deal_sig);
}

int DealConnect::deal(int server_fd) {
    socklen_t len = static_cast<socklen_t >(sizeof(*server));
    int client = accept(server_fd, server, &len);
    perror("accept");
    pid_t pid;
    if (client < 0)
        perror("In DealConnect.cpp: accept error");
    else{
        pid = fork();
        if (pid == 0){
            close(server_fd);
            Connection *connection = new Connection(client, this->root);
            connection->start();
            rmPid(pid);
            exit(9);
        }else if (pid > 0){
            close(client);
            addPid(pid);
//            exit(0);
        }else {
            perror("DealConnect::deal : Create child process error");
            exit(0);
        }
    }
}

int DealConnect::start(FtpType _type, int server_fd) {
    int status = 0;
    while(true){
        switch (_type){
            case FtpType ::MULTITHREAD: //创建多个线程
                break;
            case FtpType ::MULTIPROCESS: //创建多个进程
                status = this->deal(server_fd);
                break;
            default:
                perror("In DealConnect.cpp: Unknown Ftp type, create mutilthread or mutilprocess error");
                return -1;
        }
    }

}

void DealConnect::addPid(pid_t pid) {
    if (this->pid_top > MAX_PROCESS)
        return;
    this->pid[this->pid_top++] = pid;
}

void DealConnect::rmPid(pid_t pid) {
    if (this->pid_top <= 0)
        return;
    int index = getPid(pid);
    if (index == -1)
        return;
    pid_top--;
    this->pid[index] = this->pid[pid_top];
}

int DealConnect::getPid(pid_t pid) {
    for (int i=0; i<this->pid_top; i++)
        if (this->pid[i] == pid)
            return i;
    return -1;
}