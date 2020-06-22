/*
** EPITECH PROJECT, 2019
** server
** File description:
** create_client.c
*/

#include "create_client.h"

static inventory_t *init_invent(void)
{
    inventory_t *ret = NULL;

    ret = malloc(sizeof(inventory_t));
    if (ret == NULL)
        error("Error : malloc failed");
    ret->q0 = 0;
    ret->q1 = 0;
    ret->q2 = 0;
    ret->q3 = 0;
    ret->q4 = 0;
    ret->q5 = 0;
    ret->q6 = 0;
    return ret;
}

static client_t *init_client(int fd, server_t *serv)
{
    client_t *cli = NULL;

    cli = malloc(sizeof(client_t));
    if (cli == NULL)
        return NULL;
    cli->fd = fd;
    cli->prev = NULL;
    cli->next = NULL;
    cli->invent = init_invent();
    cli->x = get_rand_num(0, serv->x, 100);
    cli->y = get_rand_num(0, serv->y, 100);
    cli->orientation = NORTH;
    cli->id = serv->nb_player + 1;
    cli->level = 1;
    get_team_name(cli, serv);
    serv->head = cli;
    return cli;
}

client_t *create_client(int new_fd, server_t *server_v)
{
    client_t *new_client = NULL;

    new_client = init_client(new_fd, server_v);
    if (new_client == NULL)
        return NULL;
    return new_client;
}
