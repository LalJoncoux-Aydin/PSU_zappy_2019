/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_event.c
*/

#include "manage_event.h"

static void add_client(client_t **head, server_t *serv, fd_set *master)
{
    struct sockaddr_storage cli;
    socklen_t sockl = sizeof(struct sockaddr_storage);
    int new;

    if ((new = accept(serv->server_fd, (struct sockaddr *)&cli, &sockl)) == -1)
        error("accept failed that's unnacceptable");
    FD_SET(new, master);
    serv->server_fd = new > serv->server_fd ? new : serv->server_fd;
    create_client(head, new, serv);
}

void manage_event(fd_set *master, server_t *server_v, fd_set *read_fds)
{
    static client_t *head = NULL;

    for (int i = 0; i <= server_v->server_fd; i++) {
        if (FD_ISSET(i, read_fds)) {
            i == server_v->server_fd ? add_client(&head, server_v, master) : manage_client(&head, server_v, i, master);
        }
    }
}
