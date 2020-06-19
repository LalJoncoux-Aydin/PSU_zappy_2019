/*
** EPITECH PROJECT, 2019
** server
** File description:
** main.c
*/
#include "server.h"

static bool check_arg(int ac, char **av)
{
    if (ac > 1) {
        if (strcmp(av[1], "-help") == 0) {
            printf("%s", HELP);
            exit(0);
        }
    }
    if (ac != 14)
        return false;
    // CHECK DES OPTIONS POSSIBLES
    return true;
}

static bool check_value_server(server_t *server_v)
{
    if (server_v->port == 0)
        return false;
    if (server_v->y == 0 || server_v->y == 0)
        return false;
    if (server_v->nbr_max_per_teams == 0)
        return false;
    if (server_v->freq == 0)
        return false;
    return true;
}

int main(int ac, char **av, char **env)
{
    server_t *server_v = NULL;

    if (check_arg(ac, av) == false)
        return 84;
    server_v = init_server(server_v);
    if (server_v == NULL)
        return 84;
    manage_arg(ac, av, server_v, env);
    if (check_value_server(server_v) == false)
        return 84;
    if (create_map(server_v) == false)
        return 84;
    if (server(server_v) == 84)
        return 84;
    free(server_v);
    return 0;
}
