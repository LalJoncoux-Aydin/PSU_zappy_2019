/*
** EPITECH PROJECT, 2019
** server command
** File description:
** forward.c
*/

#include "command.h"

void fork_cli(int fd_cli, __attribute__((unused))client_t *cli,
__attribute__((unused))server_t *server, __attribute__((unused))char *command)
{
    //
    send(fd_cli, "ok\n", 3, 0);
}
