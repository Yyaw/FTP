//
// Created by zichaoyang on 17-5-25.
//

#include <cstring>
#include <errno.h>
#include "ProcCommunicate.h"

struct sembuf *getSembuf(short op)
{
    struct sembuf *sbuf;
    sbuf->sem_flg = SEM_UNDO;
    sbuf->sem_num = 0;
    sbuf->sem_op = op;
    return sbuf;
}

void ShareMemory::init() {
    sem_id = semget(SEM_KEY, 1, IPC_CREAT|0666);
    if (sem_id == -1)
        perror("In ProcCommunicate.cpp: Create sem_id error!");
    shm_id = shmget(SHM_KEY, sizeof(struct ClientSocket), IPC_CREAT|0666);
    if (shm_id == -1)
        perror("In ProcCommunicate.cpp: Create shm_id error!");
    void *tpm = shmat(shm_id, 0, 0);
    if (tpm == (void *)-1)
        perror("In ProcCommunicate.cpp: Create clientSocket error!");
    clientSocket = static_cast<ClientSocket *>(tpm);

}

void ShareMemory::send(int sockfd) {
    sem_p();
    clientSocket->client[clientSocket->index++] = sockfd;
    sem_v();
}

int ShareMemory::read() {
    int sockfd;
    sem_p();
    if (clientSocket->index <= 0)
        sockfd = -1;
    else {
        --clientSocket->index;
        sockfd = clientSocket->client[clientSocket->index];
    }
    sem_v();
    return sockfd;
}

bool ShareMemory::sem_p() {
    return sem_pv(-1);
}

bool ShareMemory::sem_v() {
    return sem_pv(1);
}

bool ShareMemory::sem_pv(short op) {
    struct sembuf *sbuf = getSembuf(op);
    int status = semop(this->sem_id, sbuf, 1);
    if (status == -1){
        char *msg = static_cast<char *>("In ProcCommunicate.cpp: PV control error,");
        strcat(msg, strerror(errno));
        perror(msg);
        return false; //P操作错误
    }
    return true;
}

void ShareMemory::setValue() {
    union semun un;
    un.val = 1;
    semctl(this->sem_id, 1, SETVAL, un);
}