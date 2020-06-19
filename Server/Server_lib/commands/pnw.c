/*
** EPITECH PROJECT, 2019
** server command
** File description:
** pnw.c
*/
#include "command.h"

void pnw(client_t *cli)
{
    char *buf = malloc(50);

    memset(buf, 0, 50);
    sprintf(buf, "pnw %d %d %d %d %d %s\n", cli->ai->player_number, cli->ai->x,
    cli->ai->y, cli->ai->orientation, cli->ai->level, cli->ai->team);
    if (DEBUG)
        printf("%s", buf);
    for (; cli->prev; cli = cli->prev);
    for (; cli; cli = cli->next)
        send(cli->fd, buf, strlen(buf), 0);
}
