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

static void end_handler(int sig)
{
    printf("\n");
    exit(0);
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
    signal(SIGINT, end_handler);
    while (1) {
        printf("Enter main loop\n");
        read_fds = master;
        printf("print select\n");
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1) {
            printf("select fail");
            error("Error : select failed");
        }
        printf("Start event\n");
        manage_event(&master, server_v, fd_max, read_fds);
        printf("end manage event\n");
    }
    return 0;
}
