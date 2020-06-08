/*
** EPITECH PROJECT, 2019
** server
** File description:
** command.h
*/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include "tools.h"
// 001 LOGIN : NAME OF THE USER

typedef struct command_manager_s
{
    char *command;
    void (*func)(int fd_cli, client_t *clis, server_t *server ,char *command);
} command_manager_t;

#define NBR_OF_COMMAND 2

void msz(int fd_cli, client_t *clis, server_t *server ,char *command);
void bct(int fd_cli, client_t *clis, server_t *server ,char *command);

static command_manager_t commands[NBR_OF_COMMAND] = {
    {"msz", msz},
    {"bct", bct},
//    {"", }
};


#endif