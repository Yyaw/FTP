//
// Created by zichaoyang on 17-5-25.
//

#include <cstring>
#include <getopt.h>
#include <cstdio>
#include <iostream>
#include "AnalyseCmd.h"

#define LOGIN 1

char **spilt(char *msg, char *s, char **msgs){
    int index = 0;
    for (int i=0;i<48;i++)
        msgs[i] = nullptr;
    msgs[index++] = strtok(msg, s);
    while ((msgs[index++] = strtok(NULL, s)) != NULL);
    return msgs;
}

Cmd AnalyseCmd::analyse(char *msg) {
    Cmd cmd;
    char *msgs[48];
    spilt(msg, " ", msgs);
    char *result = msgs[0];
    cmd.msg = msgs;
    if (!strcmp(result, "open")) {
        cmd.cmdType = OPENHOST;
    } else if (!strcmp(result, "login")){
        cmd.cmdType = LOGINFTP;
    } else if (!strcmp(result, "bye") || !strcmp(result, "quit") || !strcmp(result, "close")) {
        cmd.cmdType = EXIT;
    } else if (!strcmp(result, "pwd")) {
        cmd.cmdType = PWD;
    } else if (!strcmp(result, "ls")) {
        cmd.cmdType = LS;
    } else if (!strcmp(result, "cd")) {
        cmd.cmdType = CD;
    } else if (!strcmp(result, "mkdir")) {
        cmd.cmdType = MKDIR;
    } else if (!strcmp(result, "get")) {
        cmd.cmdType = GET;
    } else if (!strcmp(result, "put")) {
        cmd.cmdType = PUT;
    }
    return cmd;
}
