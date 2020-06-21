/*
** EPITECH PROJECT, 2019
** server
** File description:
** main.c
*/

#include <string.h>
#include "server.h"

static const char *flag[] = {"-h", "-p", "-x", "-y", "-n", "-c", "-f"};

static bool check_arg(int ac, char **av)
{
    bool checker = false;

    if (ac > 1) {
        if (strcmp(av[1], "-help") == 0) {
            printf("%s", HELP);
            exit(0);
        }
    }
    for (int i = 0; av[i]; i++) {
        if (av[i][0] != '-')
            continue;
        checker = false;
        for (int j = 0; checker == false && flag[j]; j++) {
            checker = (strncmp(flag[j], av[i], strlen(flag[j])) == 0) ?
        true : false;
        }
        if (checker == false)
            return (false);
    }
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
    if (manage_arg(ac, av, server_v, env) == false)
        return 84;
    if (check_value_server(server_v) == false)
        return 84;
    if (create_map(server_v) == false)
        return 84;
    printf("Starting server...\n");
    if (server(server_v) == 84)
        return 84;
    return 0;
}
