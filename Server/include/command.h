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
#include <time.h>

#include "server_struct.h"
#include "tools.h"

#define LEFT_DIR 0
#define RIGHT_DIR 1

typedef struct command_manager_s
{
    char *command;
    void (*func)(int fd_cli, client_t *clis, server_t *server, char *command);
    int nb_of_arg;
} command_manager_t;

void msz(int fd_cli, client_t *clis,
server_t *server, char *command);
void bct(int fd_cli, client_t *clis,
server_t *server, char *command);
void mct(int fd_cli, client_t *clis,
server_t *server, char *command);
void tna(int fd_cli, client_t *clis,
server_t *server, char *command);
void ppo_plv_pin(int fd_cli, client_t *clis,
server_t *server, char *command);
void mouvement(int fd_cli, client_t *clis, server_t *server, char *command);
void look(int fd_cli, client_t *cli, server_t *server, char *command);
void forward(int fd_cli, client_t *clis,
server_t *server, char *command);
void turn(int fd_cli, client_t *clis,
server_t *server, char *command);
void take(int fd_cli, client_t *cli, server_t *server, char *command);
void nbp(int fd_cli, client_t *cli, server_t *server, char *command);
void fork_cli(int fd_cli, client_t *cli, server_t *server, char *command);
void elevation(int fd_cli, client_t *clis, server_t *server, char *command);
void pnw(client_t *cli);

#endif
