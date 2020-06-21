/*
** EPITECH PROJECT, 2019
** server command
** File description:
** look.c
*/

#include "command.h"

void take(int fd_cli, client_t *cli, server_t *server, char *command)
{
    tile_t *ia_cell = &server->map[cli->ai->y][cli->ai->x];
    char *type_obj = NULL;

    type_obj = str_breaker(command, ' ', 2, 0);
    if (type_obj == NULL)
        error("Error : Malloc fail");
    if (strncmp(type_obj, "food", 4) == 0) {
        if (ia_cell->q0 > 0) {
            send(fd_cli, "ok\n", 3, 0);
            ia_cell->q0 -= 1;
        } else
            send(fd_cli, "ko\n", 3, 0);
    }
    if (strncmp(type_obj, "stone1", 6) == 0) {
        if (ia_cell->q1 > 0) {
            send(fd_cli, "ok\n", 3, 0);
            ia_cell->q1 -= 1;
        } else
            send(fd_cli, "ko\n", 3, 0);
    }
    if (strncmp(type_obj, "stone2", 6) == 0) {
        if (ia_cell->q2 > 0) {
            send(fd_cli, "ok\n", 3, 0);
            ia_cell->q2 -= 1;
        } else
            send(fd_cli, "ko\n", 3, 0);
    }
    if (strncmp(type_obj, "stone3", 6) == 0) {
        if (ia_cell->q3 > 0) {
            send(fd_cli, "ok\n", 3, 0);
            ia_cell->q3 -= 1;
        } else
            send(fd_cli, "ko\n", 3, 0);
    }
    if (strncmp(type_obj, "stone4", 6) == 0) {
        if (ia_cell->q4 > 0) {
            send(fd_cli, "ok\n", 3, 0);
            ia_cell->q4 -= 1;
        } else
            send(fd_cli, "ko\n", 3, 0);
    }
    if (strncmp(type_obj, "stone5", 6) == 0) {
        if (ia_cell->q5 > 0) {
            send(fd_cli, "ok\n", 3, 0);
            ia_cell->q5 -= 1;
        } else
            send(fd_cli, "ko\n", 3, 0);
    }
    if (strncmp(type_obj, "stone6", 6) == 0) {
        if (ia_cell->q6 > 0) {
            send(fd_cli, "ok\n", 3, 0);
            ia_cell->q6 -= 1;
        } else
            send(fd_cli, "ko\n", 3, 0);
    }
    free(type_obj);
}
