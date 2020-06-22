/*
** EPITECH PROJECT, 2019
** server command
** File description:
** bct.c
*/

#include "command.h"

void elevation(int fd_cli, client_t *clis, server_t *server, char *command)
{
    bool elev = false;

    if (elev == false)
        send(fd_cli, "ko\n", 3, 0);
    else
        send(fd_cli, "Elevation underway\nCurrent level: k\n", 37, 0);
}
