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
    int nb_of_arg;
} command_manager_t;

#define NBR_OF_COMMAND 10

void msz(int fd_cli, client_t *clis, server_t *server ,char *command);
void bct(int fd_cli, client_t *clis, server_t *server ,char *command);
void mct(int fd_cli, client_t *clis, server_t *server ,char *command);
void tna(int fd_cli, client_t *clis, server_t *server ,char *command);
// ! player command :
void ppo_plv(int fd_cli, client_t *clis, server_t *server ,char *command);
//void pin(int fd_cli, client_t *clis, server_t *server ,char *command);
// ! player  :
void mouvement(int fd_cli, client_t *clis, server_t *server ,char *command);
void look(int fd_cli, client_t *clis, server_t *server ,char *command);


void pnw(client_t *cli);

// pwn done

static command_manager_t commands[NBR_OF_COMMAND] = {
    {"msz", msz, 0},
    {"bct", bct, 2},
    {"mct", mct, 0},
    {"tna", tna, 0},
    {"ppo", ppo_plv, 1},
    {"plv", ppo_plv, 1},
    {"Forward", mouvement, 1},
    {"Right", mouvement, 1},
    {"Left", mouvement, 1},
    {"Look", look, 1}
 //   {"pin", pin},
//    {"", }
};


#endif