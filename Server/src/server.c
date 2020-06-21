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

static void end_handler(__attribute__((unused)))
{
    printf("\n");
    exit(0);
}

static int manage_event(int maxfd, fd_set *read_fds, client_t *head,
server_t *server_v)
{
    int res = 0;

    res = select(maxfd + 1, read_fds, NULL, NULL, NULL);
    if (res < 0)
        return 84;
    if (FD_ISSET(server_v->server_fd, read_fds)) {
        if (head == NULL) {
            head = add_first_client(server_v);
        } else
            add_client(server_v, head);
    }
    for (client_t *c = head; c; c = c->next) {
        if (FD_ISSET(c->fd, read_fds)) {
            manage_client(c, server_v);
        }
    }
    return 0;
}

static void update_maxfd(int fd, fd_set *read_fds)
{
    if (fd > 0)
        FD_SET(fd, read_fds);
}

int server(server_t *server_v, client_t *head)
{
    fd_set read_fds;
    int maxfd = 0;

    server_v->server_fd = get_socket(server_v->port);
    if (server_v->server_fd == -1)
        return 84;
    signal(SIGINT, end_handler);
    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server_v->server_fd, &read_fds);
        maxfd = server_v->server_fd;
        for (client_t *c = head; c; c = c->next) {
            update_maxfd(c->fd, &read_fds);
            maxfd = (c->fd > maxfd ? c->fd : maxfd);
        }
        if (manage_event(maxfd, &read_fds, head, server_v) == 84)
            return 84;
    }
    return 0;
}
