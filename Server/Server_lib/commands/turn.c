/*
** EPITECH PROJECT, 2019
** server command
** File description:
** turn.c
*/

#include "command.h"

void turn(int fd_cli, client_t *clis, server_t *server, char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    int left = str_in_str("Left", command);
    ai_t *ai;

    if (buff == NULL)
        exit(84);
    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    ai = get_ai_by_nb(server, nb);
    if (!ai || !buff)
        return error_s(fd_cli);
    switch (ai->orientation) {
    case NORTH :
        ai->orientation = (left ? WEST : EAST);
        break;
    case SOUTH :
        ai->orientation = (!left ? WEST : EAST);
        break;
    case EAST :
        ai->orientation = (left ? NORTH : SOUTH);
        break;
    case WEST :
        ai->orientation = (!left ? NORTH : SOUTH);
        break;
    }
}
