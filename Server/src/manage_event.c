/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_event.c
*/

#include "manage_event.h"

static void add_client(fd_set *master, server_t *serv, client_t **head, int *fd_max)
{
    struct sockaddr_storage cli;
    socklen_t sockl = sizeof(struct sockaddr_storage);
    int new;

    if ((new = accept(serv->server_fd, (struct sockaddr *)&cli, &sockl)) == -1)
        error("accept failed that's unnacceptable");
    FD_SET(new, master);
    *fd_max = new > *fd_max ? new : *fd_max;
    create_client(head, new, serv);
}

void manage_event(fd_set *master, server_t *server_v, int *fd_max, fd_set *read, client_t *head)
{
    for (int i = 0; i <= *fd_max; i++) {
        if (FD_ISSET(i, read)) {
            i == server_v->server_fd ? add_client(master, server_v, &head, fd_max) : manage_client(master, server_v, i, &head);
        }
    }
    return;
}
