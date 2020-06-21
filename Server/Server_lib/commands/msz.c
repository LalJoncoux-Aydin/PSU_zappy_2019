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
    char *buff = malloc(20);

    if (buff == NULL)
        exit(84);
    memset(buff, 0, 20);
    sprintf(buff, "msz %d %d\n", server->x, server->y);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s", buff);
    free(buff);
}
