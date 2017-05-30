//
// Created by zichaoyang on 17-5-25.
//

#ifndef FTP_PROCCOMMUNICATE_H
#define FTP_PROCCOMMUNICATE_H

#define SHM_KEY 1234
#define SEM_KEY 2345

#include <zconf.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <cstdio>
#include <signal.h>

union semun{
    int val;
    struct semid_ds *buf;
    ushort *array;
};

struct ClientSocket{
    int index = 0;
    int client[1024];
};

/**
 * 控制进程间通信的类
 */
class ProcCommunicate {
public:
    virtual void send(int sockfd) = 0;
    virtual int read() = 0;
    virtual void init() = 0;
};

class ShareMemory : public ProcCommunicate {

    int sem_id, shm_id;
    ClientSocket *clientSocket;
    bool sem_p();
    bool sem_v();
    bool sem_pv(short op);
public:
    void send(int sockfd);
    int read();
    void init();
    void setValue(); //对信号量进行赋值
};


#endif //FTP_PROCCOMMUNICATE_H
