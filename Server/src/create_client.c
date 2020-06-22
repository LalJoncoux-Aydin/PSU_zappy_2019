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

static client_t *init_client_ia(client_t *cli, server_t *server_v)
{
    static int nbr_player = 0;

    cli->ai = malloc(sizeof(ai_t));
    if (cli->ai == NULL)
        return NULL;
    cli->ai->invent = init_invent();
    cli->ai->next = NULL;
    cli->ai->x = get_rand_num(0, server_v->x, 100);
    cli->ai->y = get_rand_num(0, server_v->y, 100);
    if (cli->ai->y > server_v->y / 2)
        cli->ai->orientation = NORTH;
    else
        cli->ai->orientation = SOUTH;
    printf("orientation : %d\n", cli->ai->orientation);
    cli->ai->player_number = nbr_player++;
    cli->ai->level = 0;
    get_team_name(cli, server_v);
    return cli;
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
    serv->head = cli;
    return cli;
}

client_t *create_client(int new_fd, server_t *server_v)
{
    client_t *new_client = NULL;

    new_client = init_client(new_fd, server_v);
    if (new_client == NULL)
        return NULL;
    new_client = init_client_ia(new_client, server_v);
    return new_client;
}
