/*
** EPITECH PROJECT, 2019
** server
** File description:
** create_client.c
*/

#include "create_client.h"

static void get_team_name(client_t *cli, server_t *server_v)
{
    char *team = NULL;
    int i = 0;

    team = malloc((sizeof(char) * 50));
    if (team == NULL)
        error("Error : malloc failed");
    recv(cli->fd, team, 50, 0);
    for (i = 0; server_v->teams_name[i] != NULL; i++) {
        if (str_in_str(server_v->teams_name[i], team)) {
            tna(cli->fd, cli, server_v, "error");
            get_team_name(cli, server_v);
            return;
        }
    }
    cli->ai->team = strdup(team);
    if (cli->ai->team == NULL)
        error("Error : malloc failed");
}

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

static bool create_new_client_ia(client_t *cli, server_t *server_v)
{
    static int nbr_player = 0;

    cli->ai = malloc(sizeof(ai_t));
    if (cli->ai == NULL)
        error("Error : malloc failed");
    cli->ai->invent = init_invent();
    cli->ai->next = NULL;
    cli->ai->x = get_rand_num(0, server_v->x, 100);
    cli->ai->y = get_rand_num(0, server_v->y, 100);
    if (cli->ai->y > server_v->y / 2)
        cli->ai->orientation = NORTH;
    else
        cli->ai->orientation = SOUTH;
    cli->ai->player_number = nbr_player++;
    cli->ai->level = 0;
    get_team_name(cli, server_v);
    return true;
}

static bool create_fst_client(client_t **hd, int new, server_t *serv)
{
    (*hd) = malloc(sizeof(client_t));
    if ((*hd) == NULL)
        return false;
    (*hd)->fd = new;
    (*hd)->prev = NULL;
    (*hd)->next = NULL;
    serv->head = (*hd);
    return true;
}

static bool create_new_client(client_t *cli, int new_fd)
{
    client_t *cli_prev = NULL;

    cli->next = malloc(sizeof(client_t));
    if (cli->next == NULL)
        return false;
    cli_prev = cli;
    cli = cli->next;
    cli->fd = new_fd;
    cli->next = NULL;
    cli->prev = cli_prev;
    return true;
}

void create_client(client_t **head, int new_fd, server_t *server_v)
{
    client_t *cli = NULL;

    if (!(*head)) {
        if (create_fst_client(head, new_fd, server_v) == false)
            error("Error : Creation of the first client");
        cli = *head;
    } else {
        for (cli = *head; cli->next != NULL; cli = cli->next);
        if (create_new_client(cli, new_fd) == false)
            error("Error : Creation new client");
    }
    if (create_new_client_ia(cli, server_v) == false)
        error("Error : creation new client's IA");
}
