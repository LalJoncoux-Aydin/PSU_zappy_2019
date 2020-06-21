/*
** EPITECH PROJECT, 2019
** server command
** File description:
** pnw.c
*/

#include "command.h"

void pnw(client_t *cli)
{
    char *buf = NULL;

    buf = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buf == NULL)
        error("Error : malloc failed\n");
    sprintf(buf, "pnw %d %d %d %d %d %s\n", cli->ai->player_number, cli->ai->x,
    cli->ai->y, cli->ai->orientation, cli->ai->level, cli->ai->team);
    send(cli->fd, buf, strlen(buf), 0);
}
