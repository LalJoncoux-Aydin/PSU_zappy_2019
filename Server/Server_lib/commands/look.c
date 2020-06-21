/*
** EPITECH PROJECT, 2019
** server command
** File description:
** look.c
*/

#include "command.h"

static char *writing_element(tile_t *cell, char *send_look)
{
    if (cell->q0 > 0) {
        for (int i = cell->q0; i > 0; i--)
            strcat(send_look, " food");
    }
    if (cell->q1 > 0) {
        for (int i = cell->q1; i > 0; i--)
            strcat(send_look, " linemate");
    }
    if (cell->q2 > 0) {
        for (int i = cell->q2; i > 0; i--)
            strcat(send_look, " deraumere");
    }
    if (cell->q3 > 0) {
        for (int i = cell->q3; i > 0; i--)
            strcat(send_look, " sibur");
    }
    if (cell->q4 > 0) {
        for (int i = cell->q4; i > 0; i--)
            strcat(send_look, " mendiane");
    }
    if (cell->q5 > 0) {
        for (int i = cell->q5; i > 0; i--)
            strcat(send_look, " phiras");
    }
    if (cell->q6 > 0) {
        for (int i = cell->q6; i > 0; i--)
            strcat(send_look, " thystame");
    }
    return send_look;
}

void look(int fd_cli, client_t *cli, server_t *server,
__attribute__((unused)) char *command)
{
    char *buff = NULL;

    buff = calloc(5000, sizeof(char));
    if (buff == NULL)
        error("Error : malloc fail\n");
    strcat(buff, "[");
    strcat(buff, "player");
    for (int i = 0; i < 15; i++) {
        buff = writing_element(&server->map[cli->ai->y][cli->ai->x], buff);
        if (i != 14)
            strcat(buff, ",");
    }
    strcat(buff, "]\n");
    send(fd_cli, buff, strlen(buff), 0);
    free(buff);
}
