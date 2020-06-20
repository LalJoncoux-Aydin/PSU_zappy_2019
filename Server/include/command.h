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

typedef struct command_manager_s
{
    char *command;
    void (*func)(int fd_cli, client_t *clis, server_t *server, char *command);
    int nb_of_arg;
} command_manager_t;

ai_t *get_ai_by_nb(server_t *server_v, int nb);
void msz(int fd_cli, __attribute__((unused))client_t *clis,
server_t *server, __attribute__((unused))char *command);
void bct(int fd_cli, __attribute__((unused))client_t *clis,
server_t *server, char *command);
void mct(int fd_cli, __attribute__((unused))client_t *clis,
server_t *server, __attribute__((unused))char *command);
void tna(int fd_cli, __attribute__((unused))client_t *clis,
server_t *server, __attribute__((unused))char *command);
void ppo_plv_pin(int fd_cli, __attribute__((unused))client_t *clis,
server_t *server, char *command);
void mouvement(int fd_cli, client_t *clis, server_t *server, char *command);
void look(int fd_cli, client_t *clis, server_t *server, char *command);
void forward(int fd_cli, __attribute__((unused))client_t *clis,
server_t *server, char *command);
void turn(int fd_cli, __attribute__((unused))client_t *clis,
server_t *server, char *command);
void pnw(client_t *cli);

#endif
