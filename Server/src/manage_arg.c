/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_arg.c
*/

#include "manage_arg.h"

static bool manage_other(char op, char *opt_arg, server_t *server, char *limit)
{
    int i = 0;
    char *buff_name = NULL;

    if (op == 'p') {
        server->port = strdup(opt_arg);
        if (server->port == NULL)
            return false;
    } else if (op == 'n') {
        buff_name = opt_arg;
        for (; *buff_name != '-' && (strcmp(limit, buff_name));
        buff_name += strlen(buff_name) + 1, i++) {
            server->teams_name[i] = strdup(buff_name);
        }
        server->teams_name[i] = NULL;
    }
    return true;
}

static void manage_nb(char op, char *opt_arg, server_t *server)
{
    switch (op) {
    case 'x':
        server->x = atoi(opt_arg);
        break;
    case 'y':
        server->y = atoi(opt_arg);
        break;
    case 'f':
        server->freq = atoi(opt_arg);
        break;
    case 'c':
        server->nbr_max_per_teams = atoi(opt_arg);
        break;
    }
}

bool manage_arg(int ac, char **av, server_t *server_v, char **env)
{
    int op = 0;

    while (op != -1) {
        op = getopt(ac, av, "p:x:y:c:f:n:");
        if (op == -1)
            break;
        if (manage_other(op, optarg, server_v, env[0]) == false)
            return false;
        manage_nb(op, optarg, server_v);
    }
    return true;
}
