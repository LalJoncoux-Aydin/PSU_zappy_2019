/*
** EPITECH PROJECT, 2019
** server
** File description:
** add_client.c
*/

#include "add_client.h"

client_t *add_first_client(server_t *serv)
{
    struct sockaddr_storage cli;
    socklen_t sockl = sizeof(struct sockaddr_storage);
    int new;
    client_t *client = NULL;

    if ((new = accept(serv->server_fd, (struct sockaddr *)&cli, &sockl)) == -1)
        error("accept failed that's unnacceptable");
    serv->nb_player += 1;
    client = create_client(new, serv);
    return client;
}

void add_client(server_t *serv, client_t *head)
{
    struct sockaddr_storage cli;
    socklen_t sockl = sizeof(struct sockaddr_storage);
    int new;
    client_t *client = NULL;
    client_t *cur = NULL;

    if ((new = accept(serv->server_fd, (struct sockaddr *)&cli, &sockl)) == -1)
        error("accept failed that's unnacceptable");
    serv->nb_player += 1;
    client = create_client(new, serv);
    if (head != NULL) {
        for (cur = head; cur->next != NULL; cur = cur->next);
        client->prev = cur;
        cur->next = client;
    }
}
