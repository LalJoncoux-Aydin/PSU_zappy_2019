/*
** EPITECH PROJECT, 2019
** server command
** File description:
** look.c
*/

#include "command.h"

static char *writing_element(tile_t *cell, bool first)
{
    char send_look[MESSAGE_SIZE * MESSAGE_SIZE] = "";

    if (first == false)
        strcpy(send_look, ",");
    else
        strcpy(send_look, "[player");
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
    strcat(send_look, "\0");
    return strdup(send_look);
}

static char *find_direction(char *res, bool first, tile_t *cell)
{
    char *temp = NULL;

    if (first == true) {
        temp = writing_element(cell, first);
        res = malloc(sizeof(char) * strlen(temp) + 1);
        res = strcpy(res, temp);
    } else {
        temp = writing_element(cell, first);
        res = realloc(res, strlen(res) + strlen(temp) + 2);
        strcat(res, temp);
    }
    strcat(res, "\0");
    free(temp);
    return res;
}

static void next_look(client_t *cli, int i)
{
    switch (cli->ai->orientation) {
    case(NORTH):
        cli->ai->look_y -= 1;
        break;
    case(SOUTH):
        cli->ai->look_y += 1;
        break;
    case(EAST):
        cli->ai->look_x += 1;
        break;
    case(WEST):
        cli->ai->look_x -= 1;
        break;
    }
}

void look(int fd_cli, client_t *cli, server_t *server,
__attribute__((unused)) char *command)
{
    char *res = "";

    cli->ai->look_x = cli->ai->x;
    cli->ai->look_y = cli->ai->y;
    res = malloc(sizeof(char) * MESSAGE_SIZE);
    if (res == NULL)
        error("Error : malloc fail\n");
    res = find_direction(res, true, &server->map[cli->ai->look_x][cli->ai->look_y]);
    for (int i = 1; i < 15; i++) {
        next_look(cli, i);
        if (cli->ai->look_y >= 0 && cli->ai->look_y <= server->y
        && cli->ai->look_x >= 0 && cli->ai->look_x <= server->x)
            res = find_direction(res, false, &server->map[cli->ai->look_x][cli->ai->look_y]);
    }
    strcat(res, "]\0");
    send(fd_cli, res, strlen(res), 0);
    free(res);
}
