//
// Created by zichaoyang on 17-5-27.
//
#pragma once
#ifndef FTP_FSUTIL_H
#define FTP_FSUTIL_H
#define USERLIST "../UserControl/user.list"

#define ISEXIST 1
#define NOPERMISSION 2
#define NOEXIST 4
#define OPENERROR 8
#define REMOVEERROR 16
#define OK 32

#include <string>
#include <map>
#include <istream>
#include <ostream>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <stack>
#include "../UserControl/User.h"

using namespace std;
/**
 * 化简路径 比如/home/zbc/k/../b可以化简为/home/zbc/b
 * @param filepath 文件路径
 * @return
 */
inline const char *toSinglePath(char *&filepath){
    std::string path(filepath);
    bool flag = false;
    if (path[path.length()-1] == '/')
        flag = true;
    stack<string> ss; // 记录路径名
    for(int i = 0; i < path.size(); )
        {
        // 跳过斜线'/'
        while(i < path.size() && '/' == path[i])
            ++ i;
        // 记录路径名
        string s = "";
        while(i < path.size() && path[i] != '/')
            s += path[i ++];
        // 如果是".."则需要弹栈，否则入栈
        if(".." == s && !ss.empty())
            ss.pop();
        else if(s != "" && s != "." && s != "..")
            ss.push(s);
        }
    // 如果栈为空，说明为根目录，只有斜线'/'
    if(ss.empty())
        return "/";
    // 逐个连接栈里的路径名
    string s = "";
    while(!ss.empty())
    {
        s = "/" + ss.top() + s;
        ss.pop();
    }
    char *file = new char[path.length()];
    strcpy(file, s.c_str());
    if (flag)
        strcat(file, "/");
    strcpy(filepath, file);
    return filepath;
}

inline bool isFileOrDirExist(char *filepath){
    std::fstream fs;
    fs.open(filepath, std::ios::in);

    if (!fs)
        return false;
    else{
        fs.close();
        return true;
    }
}

inline std::map<std::string, User> getUserMsg() {
    std::ifstream in;
    std::map<std::string, User> usermsg;
    in.open(USERLIST, std::ios::in);
    if (!in)
    {
        perror("Open userlist error!");
        return usermsg;
    }
    std::string user;
    std::string password;
    int permission;

    while (!in.eof()){
        in >> user >> password >> permission;
        usermsg.insert(std::make_pair<std::string, User>(user.c_str(), User(user, password, permission)));
    }
    in.close();
    return usermsg;

};

//TODO 判断文件路径是不是一个目录
inline bool isDir(char *path){
//    struct stat buf;
//    lstat(path, &buf);
//    return S_ISDIR(buf.st_mode);
    return true;
}

inline bool isIndexOf(char *s1, char *s2)
{
    int i;
    for (i=0; i < strlen(s1) && i<strlen(s2); i++){
        if (s1[i] != s2[i])
            return false;
    }
    if (i < strlen(s2))
        return false;
    else
        return true;
}

inline void clearIndex(char *&s1, char *s2)
{
    if (!isIndexOf(s1, s2))
        return;
    s1+=strlen(s2);
}

#endif //FTP_FSUTIL_H
