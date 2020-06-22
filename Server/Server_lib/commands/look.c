/*
** EPITECH PROJECT, 2019
** server command
** File description:
** look.c
*/

#include "command.h"

static char *writing_element(inventory_t *cell, bool first, int i)
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
    if (i == 15)
        strcat(send_look, "]\n");
    strcat(send_look, "\0");
    return strdup(send_look);
}

static char *find_direction(char *res, bool first, inventory_t *cell, int i)
{
    char *temp = NULL;
    char *new = NULL;

    if (first == true) {
        temp = writing_element(cell, first, i);
        res = malloc(sizeof(char) * strlen(temp) + 1);
        res = strcpy(res, temp);
    } else {
        temp = writing_element(cell, first, i);
        new = malloc(sizeof(char) * (strlen(res) + strlen(temp) + 2));
        strcpy(new, res);
        strcat(new, temp);
        return new;
    }
    free(temp);
    return res;
}

static void next_look(client_t *cli, int i)
{
    if (i == 1 || i == 4 || i == 9) {
        switch (cli->orientation) {
        case(NORTH):
            cli->look_y -= 1;
            cli->look_x -= (i == 1 ? i : i + 1);
            break;
        case(SOUTH):
            cli->look_y += 1;
            cli->look_x -= (i == 1 ? i : i + 1);
            break;
        case(EAST):
            cli->look_y -= (i == 1 ? i : i + 1);
            cli->look_x += 1;
            break;
        case(WEST):
            cli->look_y -= (i == 1 ? i : i + 1);
            cli->look_x -= 1;
            break;
        }
    } else if (cli->orientation == NORTH || cli->orientation == SOUTH) {
        cli->look_x += 1;
    } else if (cli->orientation == EAST || cli->orientation == WEST) {
        cli->look_y += 1;
    }
}

void look(int fd_cli, client_t *cli, server_t *server,
__attribute__((unused)) char *command)
{
    char *res = NULL;

    cli->look_x = cli->x;
    cli->look_y = cli->y;
    res = malloc(sizeof(char) * MESSAGE_SIZE);
    if (res == NULL)
        error("Error : malloc fail\n");
    res = find_direction(res, true, &server->map[cli->look_x][cli->look_y], 0);
    for (int i = 1; i <= 15; i++) {
        next_look(cli, i);
        if (cli->look_y >= 0 && cli->look_y <= server->y
        && cli->look_x >= 0 && cli->look_x <= server->x)
            res = find_direction(res, false, &server->map[cli->look_x][cli->look_y], i);
    }
    send(fd_cli, res, strlen(res) + 1, 0);
    free(res);
}
