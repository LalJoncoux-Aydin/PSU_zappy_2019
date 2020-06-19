/*
** EPITECH PROJECT, 2019
** jo
** File description:
** server.c
*/

#include "server.h"

server_t *init_server(server_t *server_v)
{
    server_v = malloc(sizeof(server_t));
    if (server_v == NULL)
        return NULL;
    server_v->teams_name = malloc(sizeof(char *) * TEAMS_NB);
    if (server_v->teams_name == NULL)
        return NULL;
    return server_v;
}

int server(server_t *server_v)
{
    int fd_max;
    fd_set master;
    fd_set read_fds;

    server_v->server_fd = get_socket(server_v->port);
    if (server_v->server_fd == -1)
        return 84;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(server_v->server_fd , &master);
    fd_max = server_v->server_fd;
    while (1) {
        read_fds = master;
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1)
            error("Error : select failed");
        manage_event(&master, server_v, fd_max, read_fds);
    }
    return 0;
}
