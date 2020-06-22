/*
** EPITECH PROJECT, 2019
** server command
** File description:
** forward.c
*/

#include "command.h"

static void set_move(client_t *cli, server_t *server)
{
    switch (cli->ai->orientation) {
    case NORTH :
        if (cli->ai->y > 0)
            cli->ai->y -= 1;
        break;
    case SOUTH :
        if (cli->ai->y < server->y)
            cli->ai->y += 1;
        break;
    case EAST :
        if (cli->ai->x < server->x)
            cli->ai->x += 1;
        break;
    case WEST :
        if (cli->ai->x > 0)
            cli->ai->x -= 1;
        break;
    }
}

void forward(int fd_cli, client_t *cli, server_t *server,
__attribute__((unused))char *command)
{
    char *buff = NULL;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL)
        error("Error : malloc failed\n");
    set_move(cli, server);
    send(fd_cli, "ok\n", 3, 0);
}
