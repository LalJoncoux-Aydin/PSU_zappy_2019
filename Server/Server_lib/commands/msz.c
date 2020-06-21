/*
** EPITECH PROJECT, 2019
** server command
** File description:
** msz.c
*/

#include "command.h"

void msz(int fd_cli, __attribute__((unused))client_t *clis, server_t *server,
__attribute__((unused))char *command)
{
    char *buff = NULL;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL)
        error("Error : malloc failed\n");
    sprintf(buff, "msz %d %d\n", server->x, server->y);
    send(fd_cli, buff, strlen(buff), 0);;
    free(buff);
}
