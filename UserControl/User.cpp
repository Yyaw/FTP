//
// Created by zichaoyang on 17-5-25.
//

#include "User.h"
#include "../FileControl/FSUtil.h"

bool User::checkPermission(int permission) {
    return false;
}

bool User::createUser(char *name, char *psw, int permission) {
    std::map<std::string, User> userlist = getUserMsg();
    auto find_map = userlist.find(std::string(name));
    if (find_map != userlist.end())
        return false;
    userlist.insert(std::make_pair<std::string, User>(std::string(name), {name, psw, permission}));
    std::fstream out("/home/zichaoyang/CLionProjects/FTP/UserControl/user.list");
    if (!out){
        perror("Open userlist error");
    }
    for (std::map<std::string, User>::iterator m = userlist.begin(); m != userlist.end(); m++){
        out << m->second._username << " "  << m->second._password << " " << m->second._permission << std::endl;
    }
    out.flush();
    out.close();
    return true;
}

bool User::checkUserName(std::string username) {
    std::map<std::string, User> userlist = getUserMsg();
    auto m = userlist.find(username);
    return m != userlist.end();
}



//int main()
//{
//    User user;
//    user.createUser("ziyueyang1", "1234567", 1);
//
//}