/*
** EPITECH PROJECT, 2019
** server command
** File description:
** turn.c
*/

#include "command.h"

static void set_orientation(client_t *cli, bool _dir, int fd_cli)
{
    switch (cli->orientation) {
    case NORTH :
        cli->orientation = (_dir == LEFT_DIR ? WEST : EAST);
        break;
    case SOUTH :
        cli->orientation = (_dir == LEFT_DIR ? EAST : WEST);
        break;
    case EAST :
        cli->orientation = (_dir == LEFT_DIR ? NORTH : SOUTH);
        break;
    case WEST :
        cli->orientation = (_dir == LEFT_DIR ? SOUTH : NORTH);
        break;
    }
    send(fd_cli, "ok\n", 3, 0);
}

void turn(int fd_cli, client_t *cli, __attribute__((unused))server_t *server,
char *command)
{
    char *buff = NULL;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL)
        error("Error : malloc failed\n");
    if (strncmp(command, "Left\n", 5) == 0) {
        set_orientation(cli, LEFT_DIR, fd_cli);
    } if (strncmp(command, "Right\n", 6) == 0) {
        set_orientation(cli, RIGHT_DIR, fd_cli);
    }
}
