/*
** EPITECH PROJECT, 2019
** server command
** File description:
** tna.c
*/

#include "command.h"

void tna(int fd_cli, client_t *none, server_t *server, char *none_c)
{
    char *buff = malloc(50);

    if (buff == NULL)
        exit(84);
    for (int y = 0; server->teams_name[y]; y++) {
        memset(buff, 0, 50);
        sprintf(buff, "tna %s\n", server->teams_name[y]);
        send(fd_cli, buff, strlen(buff), 0);
        if (DEBUG)
            printf("message send : %s", buff);
    }
    free(buff);
}