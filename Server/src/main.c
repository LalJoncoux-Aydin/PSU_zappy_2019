/*
** EPITECH PROJECT, 2019
** nom_server
** File description:
** main.c
*/

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>

int create_map(server_t *server_v)
{
    if (server_v->x < 0 || server_v->y < 0)
        return -1;
    server_v->map = malloc(sizeof(tile_t *) * (server_v->y + 1));
    for (int y = 0; y < server_v->y; y++) {
        server_v->map[y] = malloc(sizeof(tile_t) * (server_v->x + 1));
        for (int x = 0; x < server_v->x; x++) {
            server_v->map[y][x].q0 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q1 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q2 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q3 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q4 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q5 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q6 = get_rand_num(0, 6, 50);
        }
    }
    return 0;
}

void manage_op2(char op, char *opt_arg, server_t *server)
{
    switch (op) {
    case 'f':
        server->freq = atoi(opt_arg);
        break;
    case 'p':
        server->port = strdup(opt_arg);
        break;
    case 'c':
        server->nbr_max_per_teams = atoi(opt_arg);
        break;
    }
}

int manage_op(char op, char *opt_arg, server_t *server, char *limit)
{
    int i = 0;

    switch (op) {
    case 'n':
        for (char *buff_name = opt_arg; *buff_name != '-' &&
            (strcmp(limit, buff_name));
            buff_name = buff_name + strlen(buff_name) + 1)
            server->teams_name[i++] = strdup(buff_name);
        server->teams_name[i] = NULL;
        break;
    case 'x':
        server->x = atoi(opt_arg);
        break;
    case 'y':
        server->y = atoi(opt_arg);
        break;
    }
    manage_op2(op, opt_arg, server);
    return 0;
}

int main(int ac, char **av, char **env)
{
    server_t *server_v = malloc(sizeof(server_t));
    int op;

    if ((ac > 1) && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
        printf("%s", HELP);
        return 0;
    }
    server_v->teams_name = malloc(sizeof(char *) * ac);
    while (1) {
        op = getopt(ac, av, "p:x:y:c:f:n:");
        if (op == -1)
            break;
        manage_op(op, optarg, server_v, env[0]);
    }
    if (create_map(server_v) == -1)
        return (84);
    server(server_v);
    return 0;
}
