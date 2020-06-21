/*
** EPITECH PROJECT, 2019
** server
** File description:
** create_client.c
*/

#include "create_client.h"

static void send_player_info(client_t *cli)
{
    char size_map[MESSAGE_SIZE];

    sprintf(size_map, "%d\n%d %d\n", NB_CLIENT, cli->ai->x, cli->ai->y);
    send(cli->fd, size_map, strlen(size_map), 0);
}

static void get_team_name(client_t *cli, server_t *server_v)
{
    char *team = NULL;

    team = malloc((sizeof(char) * 50));
    if (team == NULL)
        error("Error : malloc failed\n");
    send(cli->fd, "WELCOME\n", 8, 0);
    recv(cli->fd, team, 50, 0);
    for (int i = 0; server_v->teams_name[i] != NULL; i++) {
        if (strcmp(server_v->teams_name[i], team)) {
            cli->ai->team = strdup(team);
            if (cli->ai->team == NULL)
                error("Error : malloc failed\n");
        }
    }
    if (cli->ai->team == NULL)
        error("Wrong team name\n");
    send_player_info(cli);
    free(team);
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

static client_t *create_fst_client(int new, server_t *serv)
{
    client_t *head = NULL;

    head = malloc(sizeof(client_t));
    if (head == NULL)
        return NULL;
    head->fd = new;
    head->prev = NULL;
    head->next = NULL;
    serv->head = head;
    return head;
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
    client_t *tmp = *head;

    if (tmp == NULL) {
        tmp = create_fst_client(new_fd, server_v);
        if (tmp == NULL)
            error("Error : Creation of the first client");
    } else {
        for (; tmp->next != NULL; tmp = tmp->next);
        if (create_new_client(tmp, new_fd) == false)
            error("Error : Creation new client");
    }
    if (create_new_client_ia(tmp, server_v) == false)
        error("Error : creation new client's IA");
}
