/*
** EPITECH PROJECT, 2019
** server command
** File description:
** forward.c
*/

#include "command.h"

void fork_cli(int fd_cli, client_t *cli, server_t *server,
__attribute__((unused))char *command)
{
    //
    send(fd_cli, "ok\n", 3, 0);
}
