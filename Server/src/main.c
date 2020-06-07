#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>

//norm ou pas nom?
int manage_op(char op, char *opt_arg, server_t *server, char *limit)
{
    int i = 0;

    switch (op) {
        case 'n':
                for (char *buff_name = opt_arg; *buff_name != '-' &&
    (strcmp(limit, buff_name)); buff_name = buff_name + strlen(buff_name) + 1)
                    server->teams_name[i++] = strdup(buff_name);
                server->teams_name[i] = NULL;
                break;
        case 'x':
            server->x = atoi(opt_arg);
            break;
        case 'y':
            server->y = atoi(opt_arg);
            break;
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
    return 0;
}

int main(int ac, char **av, char **env)
{
    char *buf = NULL;
    server_t *server_v = malloc(sizeof(server_t));
    int op;

    if ((ac > 1) && (!strcmp(av[1], "-h")  || !strcmp(av[1], "-help"))) {
        printf("%s", HELP);
        return 0;
    }
    server_v->teams_name = malloc(sizeof(char *)* ac);
    while (1) {
        op = getopt(ac, av, "p:x:y:c:f:n:");
        if (op == -1)
            break;
        manage_op(op, optarg, server_v, env[0]);
    }
    server(server_v);
    return 0;
}
