/*
** EPITECH PROJECT, 2019
** server command
** File description:
** bct.c
*/

#include "command.h"

static int get_players_at_level(client_t *cli)
{
    int nb_player = 0;
    int level = cli->level;
    client_t *tmp = NULL;

    for (tmp = cli; tmp->prev != NULL; tmp = tmp->prev);
    for (; tmp; tmp = tmp->next) {
        if (tmp->level == level)
            nb_player += 1;
    }
    return nb_player;
}

static void update_level(client_t *cli)
{
    switch (cli->level) {
    case(1):
        if (get_players_at_level(cli) == 1 && cli->invent->q1 == 1 && cli->invent->q2 == 0 && cli->invent->q3 == 0 && cli->invent->q4 == 0 && cli->invent->q5 == 0 && cli->invent->q6 == 0)
            cli->level = 2;
        break;
    case(2):
        if (get_players_at_level(cli) == 2 && cli->invent->q1 == 1 && cli->invent->q2 == 1 && cli->invent->q3 == 1 && cli->invent->q4 == 0 && cli->invent->q5 == 0 && cli->invent->q6 == 0)
            cli->level = 3;
        break;
    case(3):
        if (get_players_at_level(cli) == 2 && cli->invent->q1 == 2 && cli->invent->q2 == 0 && cli->invent->q3 == 1 && cli->invent->q4 == 0 && cli->invent->q5 == 0 && cli->invent->q6 == 0)
            cli->level = 4;
        break;
    case(4):
        if (get_players_at_level(cli) == 4 && cli->invent->q1 == 1 && cli->invent->q2 == 1 && cli->invent->q3 == 2 && cli->invent->q4 == 0 && cli->invent->q5 == 1 && cli->invent->q6 == 0)
            cli->level = 5;
        break;
    case(5):
        if (get_players_at_level(cli) == 4 && cli->invent->q1 == 1 && cli->invent->q2 == 2 && cli->invent->q3 == 1 && cli->invent->q4 == 3 && cli->invent->q5 == 0 && cli->invent->q6 == 0)
            cli->level = 6;
        break;
    case(6):
        if (get_players_at_level(cli) == 6 && cli->invent->q1 == 1 && cli->invent->q2 == 2 && cli->invent->q3 == 3 && cli->invent->q4 == 0 && cli->invent->q5 == 1 && cli->invent->q6 == 0)
            cli->level = 7;
        break;
    case(7):
        if (get_players_at_level(cli) == 6 && cli->invent->q1 == 2 && cli->invent->q2 == 2 && cli->invent->q3 == 2 && cli->invent->q4 == 2 && cli->invent->q5 == 2 && cli->invent->q6 == 1)
            cli->level = 8;
        break;
    }
}

void elevation(int fd_cli, client_t *cli, server_t *server, char *command)
{
    bool elev = false;
    int old_level = cli->level;

    update_level(cli);
    if (cli->level != old_level)
        elev = true;
    if (elev == false)
        send(fd_cli, "ko\n", 3, 0);
    else
        send(fd_cli, "Elevation underway\nCurrent level: k\n", 37, 0);
}
