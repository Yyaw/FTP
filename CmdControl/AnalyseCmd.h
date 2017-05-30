/**
 * Created by zichaoyang on 17-5-25.
 * 用于解析客户端传过来的参数,然后执行相应的操作
 */
#ifndef FTP_ANALYSECMD_H
#define FTP_ANALYSECMD_H

#include "Datastructure.h"

/**
 * 定义了一些操作状态的宏
 */
#define RMFILE 1
#define MVFILE 2
#define RNFILE 4
#define SNFILE 8
#define SNMSG 16
#define CPFILE 32
#define EXIT 64
#define OPENHOST 128
#define LOGINFTP 256
#define PWD 512
#define LS 1024
#define CD 2048
#define MKDIR 4096
#define GET 9192
#define PUT 18384


class AnalyseCmd {
public:
    Cmd analyse(char *msg);

};


#endif //FTP_ANALYSECMD_H
