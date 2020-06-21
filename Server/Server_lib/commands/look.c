/*
** EPITECH PROJECT, 2019
** server command
** File description:
** look.c
*/

#include "command.h"

static void writing_element(tile_t *cell, int fd_cli)
{
    char send_look[MESSAGE_SIZE] = "[" "player";
    if (cell->q0 > 0) {
        for (int i = cell->q0; i > 0; i--)
            strcat(send_look, ", food");
    } else {
        strcat(send_look, ",");
    }
    if (cell->q1 > 0) {
        for (int i = cell->q1; i > 0; i--)
            strcat(send_look, ", linemate");
    } else {
        strcat(send_look, ",");
    }
    if (cell->q2 > 0) {
        for (int i = cell->q2; i > 0; i--)
            strcat(send_look, ", deraumere");
    } else {
        strcat(send_look, ",");
    }
    if (cell->q3 > 0) {
        for (int i = cell->q3; i > 0; i--)
            strcat(send_look, ", sibur");
    } else {
        strcat(send_look, ",");
    }
    if (cell->q4 > 0) {
        for (int i = cell->q4; i > 0; i--)
            strcat(send_look, ", mendiane");
    } else {
        strcat(send_look, ",");
    }
    if (cell->q5 > 0) {
        for (int i = cell->q5; i > 0; i--)
            strcat(send_look, ", phiras");
    } else {
        strcat(send_look, ",");
    }
    if (cell->q6 > 0) {
        for (int i = cell->q6; i > 0; i--)
            strcat(send_look, ", thystame");
    } else {
        strcat(send_look, ",");
    }
    strcat(send_look, "]\n");
    send(fd_cli, send_look, strlen(send_look), 0);
}

void look(int fd_cli, client_t *clis, server_t *server,
__attribute__((unused)) char *command)
{
    writing_element(&server->map[clis->ai->y][clis->ai->x], fd_cli);
}
