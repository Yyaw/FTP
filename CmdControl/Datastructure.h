//
// Created by zichaoyang on 17-5-26.
//

#ifndef FTP_DATASTRUCTURE_H
#define FTP_DATASTRUCTURE_H

/**
 * 定义一些常用的数据结构
 */
struct Cmd {

    int cmdType;
    char **msg;

    Cmd(){
        msg = new char*[48];
        for (int i=0; i<48;i++)
            msg[i] = new char[256];
    }

};


#endif //FTP_DATASTRUCTURE_H
