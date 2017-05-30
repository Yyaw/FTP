//
// Created by zichaoyang on 17-5-25.
//

#ifndef FTP_USER_H
#define FTP_USER_H

#include <map>
#include <string>
#include <fstream>
#include <cstring>

#define READ 1
#define WRITE 2
#define REWR 3


class User {
    char *_username;
    char *_password;
    int _permission;
    bool checkUserName(std::string);

public:
    User(){_username = new char[64]; _password = new char[64];}
    User(char *username, char *password, int permission):_username(username), _password(password), _permission(permission){}
    User(std::string username, std::string password, int permission){
        _username = new char[64];
        _password = new char[64];
        strcpy(_username, username.c_str());
        strcpy(_password, password.c_str());
        _permission = permission;
    }
    bool checkPermission(int permission);
    bool createUser(char *name, char *psw, int permission);
    char *getUsername(){return _username;}
    char *getPassword(){return _password;}
    int getPermission(){return _permission;}
};


#endif //FTP_USER_H
