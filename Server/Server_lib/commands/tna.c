/*
** EPITECH PROJECT, 2019
** server command
** File description:
** tna.c
*/

#include "command.h"

void tna(int fd_cli, __attribute__((unused))client_t *none, server_t *server,
__attribute__((unused))char *none_c)
{
    char *buff = NULL;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL)
        error("Error : malloc failed\n");
    for (int y = 0; server->teams_name[y]; y++) {
        memset(buff, 0, MESSAGE_SIZE);
        sprintf(buff, "tna %s\n", server->teams_name[y]);
        send(fd_cli, buff, strlen(buff), 0);
    }
    free(buff);
}
