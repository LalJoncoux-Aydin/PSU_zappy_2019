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

#include "client.h"
#include "tools.h"
// 001 LOGIN : NAME OF THE USER
#define NBR_OF_COMMAND 14

typedef struct command_manager_s
{
    char *command;
    void (*func)(client_t *cli, char *command);
} command_manager_t;

void my_send(client_t *cli, char *msg);
void cli_logout(client_t *cli, char *none);

#endif