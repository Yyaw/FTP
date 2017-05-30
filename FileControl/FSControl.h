//
// Created by zichaoyang on 17-5-25.
//

#ifndef FTP_FSCONTROL_H
#define FTP_FSCONTROL_H


#include "FSUtil.h"
#include <cstdio>
#include "../UserControl/User.h"
#include <cstring>
#include <iostream>
#include <fstream>

/**
 * TODO
 * 检查用户权限
 */
class FSControl {
    char root[1024] = {0}; //ftp根目录
    char tmp[1024] = {0};
    User user; //用户相关信息
public:
    FSControl (){}
    FSControl(User user, char *root){init(user, root);}
    void init(User user, char *root);
    char *getFile(char *filepath);
    int mvFile(char *from, char *to);
    bool rnFile(char *filepath, char *newname);
    int rmFile(char *filepath);
    bool cd(char *filepath);
    bool cp(char *filepath, char *newname);
    bool login(char *username, char *password);
    int createfile(char *username, char *from);
    char *getRoot();
    int ls(char *, char** &);
    bool my_mkdir(char *file);
    bool my_rmdir(char *file);

    static User getUser(char *username){
        std::map<std::string, User> userlist = getUserMsg();
        auto m = userlist.find(std::string(username));
        if (m == userlist.end())
            return {};
        return m->second;
    }

};


#endif //FTP_FSCONTROL_H
