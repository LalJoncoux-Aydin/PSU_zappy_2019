/*
** EPITECH PROJECT, 2019
** server command
** File description:
** forward.c
*/

#include "command.h"

static void set_move(client_t *cli, server_t *server)
{
    switch (cli->orientation) {
    case NORTH :
        if (cli->y > 0)
            cli->y -= 1;
        break;
    case SOUTH :
        if (cli->y < server->y)
            cli->y += 1;
        break;
    case EAST :
        if (cli->x < server->x)
            cli->x += 1;
        break;
    case WEST :
        if (cli->x > 0)
            cli->x -= 1;
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
