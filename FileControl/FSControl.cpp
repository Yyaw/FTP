//
// Created by zichaoyang on 17-5-25.
//

#include <dirent.h>
#include <zconf.h>
#include <sys/stat.h>
#include "FSControl.h"

char *getTime(timespec time){
    return "2014-01-01_10:02:03";
}

void FSControl::init(User user, char *root) {
    strcpy(this->root, root);
    this->user = user;
    strcpy(tmp, "/");
}

char* FSControl::getFile(char *filepath) {
    if (isIndexOf(filepath, root))
        return filepath;
    char *result = new char[256];
    strcpy(result, root);
    if (filepath[0] == '/'){
        strcat(result, filepath);
    }else{
        if (strcmp(tmp, "/"))
            strncat(result, tmp, sizeof(tmp));
        strcat(result, filepath);
    }
    toSinglePath(result);
    return result;
}

int FSControl::mvFile(char *from, char *to) {
    int status = createfile(to, from);
    if (status != OK)
        return status;
    return rmFile(to);
}

int FSControl::rmFile(char *filepath) {
    toSinglePath(filepath);
    if (!user.checkPermission(WRITE))
        return NOPERMISSION;
    if (!isFileOrDirExist(filepath))
        return NOEXIST;
    return remove(filepath) == 0 ? OK : REMOVEERROR;
}


bool FSControl::rnFile(char *filepath, char *newname) {
    toSinglePath(filepath);
    if (!user.checkPermission(WRITE))
        return false;
    if (!isFileOrDirExist(filepath))
        return false;
    return !rename(filepath, newname);
}

bool FSControl::cp(char *filepath, char *newname) {
    if (!isFileOrDirExist(filepath))
        return false;
    std::ifstream in;
    std::ofstream out;

}

bool FSControl::cd(char *filepath) {
    if (!isFileOrDirExist(filepath) || !user.checkPermission(READ)) {
        clearIndex(filepath, root);
        bzero(tmp, strlen(tmp));
        strcpy(tmp, filepath);
        return true;
    }
    return false;
}

bool FSControl::login(char *username, char *password) {
    std::map<std::string, User> userlist = getUserMsg();
    std::string user(username);
    std::string psw(password);
    auto map_node = userlist.find(user);
    if (map_node == userlist.end())
        return false;
    else
        return (strcmp(userlist[user].getPassword(), password) == 0);
}

int FSControl::createfile(char *filepath, char *from) {
    if (!from && !isFileOrDirExist(from))
        return NOEXIST;
    if (isFileOrDirExist(filepath))
        return ISEXIST;
    if (!user.checkPermission(WRITE))
        return NOPERMISSION;
    if (!from){
        FILE *file = fopen(filepath, "w");
        fclose(file);
    } else{
        std::ofstream out(filepath);
        std::ifstream in(from);
       if (!out || !in)
           return OPENERROR;
        char byte[1];
        while(!in.eof()){
            in.read(byte, 1);
            out.write(byte, 1);
        }
        return OK;
    }
}

int FSControl::ls(char *path, char **&result) {
    path = getFile(path);
    if (!isDir(path)){
        result = nullptr;
        return 0;
    }
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        result = NULL;
        return 0;
    }
    result = new char*[256];
    for (int i=0; i<256; i++)
        result[i] = new char[256];
    struct dirent *entry;
    struct stat statbuf;
    int index = 0;
    while((entry = readdir(dir)) != NULL){
        char *tmp_dir = new char[256];
        strcpy(tmp_dir, tmp);
        char *tmpdir = new char[256];
        strcpy(tmpdir, getFile(path));
        lstat(strcat(tmpdir, entry->d_name), &statbuf);
        if (entry->d_name[0] != '.'){
            if (S_ISDIR(statbuf.st_mode)){
                if(!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
                    continue;
                else
                {
                    result[index++] = strcat(tmp_dir, entry->d_name);
                    strcat(result[index-1], "/");
                    strcat(result[index-1], ",");
                    strcat(result[index-1], getTime(statbuf.st_atim));
                    strcat(result[index-1], ",");
                    char size[15];
                    sprintf(size, "%d", statbuf.st_size);
                    strcat(result[index-1], size);
                }
            }else if (S_ISREG(statbuf.st_mode)){
                result[index++] = strcat(tmp_dir, entry->d_name);
                strcat(result[index-1], ",");
                strcat(result[index-1], getTime(statbuf.st_atim));
                strcat(result[index-1], ",");
                char size[15];
                sprintf(size, "%d", statbuf.st_size);
                strcat(result[index-1], size);
            }
        }
    }
    return index;
}

bool FSControl::my_mkdir(char *file) {
    file = getFile(file);
    int status = mkdir(file, O_CREAT | 0x666);
}

bool FSControl::my_rmdir(char *file) {
    file = getFile(file);
    int status = rmdir(file);
}

char* FSControl::getRoot() {
    return this->tmp;
}


//int main(int argc, char **argv)
//{
//    FSControl fsControl;
//    fsControl.init({"zichaoyang", "1234", 1}, "/home/zichaoyang");
//    char **result;
//    int num = fsControl.ls("/", result);
//    for (int i=0; i<num; i++){
//        printf("%s\n", result[i]);
//    }
//
//
//}