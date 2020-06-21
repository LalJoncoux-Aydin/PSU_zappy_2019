/*
** EPITECH PROJECT, 2019
** server command
** File description:
** bct.c
*/

#include "command.h"

void elevation(int fd_cli, client_t *clis, server_t *server, char *command)
{
    char *buff = NULL;

    fd_cli = fd_cli;
    clis = clis;
    server = server;
    command = command;
    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    strcpy(buff, "Elevation underway\0");
    send(fd_cli, buff, strlen(buff), 0);
    free(buff);
}
