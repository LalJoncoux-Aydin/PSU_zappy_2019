/*
** EPITECH PROJECT, 2019
** server
** File description:
** create_client.c
*/
#include "create_client.h"

static char *init_buffer(char *buff, int new_fd)
{
    buff = malloc(sizeof(char) * 50);
    if (buff == NULL)
        error("Malloc failed");
    memset(buff, 0 , 50);
    recv(new_fd, buff, 50, 0);
    return buff;
}

static inventory_t *init_invent(void)
{
    inventory_t *ret = NULL;

    ret = malloc(sizeof(inventory_t));
    if (ret == NULL)
        return NULL;
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
    int i = 0;
    char *team = NULL;
    static int nbr_player = 0;

    team = malloc((sizeof(char) * 50));
    if (team == NULL)
        error("Error : malloc failed");
    i = recv(cli->fd, team, 50, 0);
    team[i -1] = '\0';
    cli->ai = malloc(sizeof(client_t));
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
    TEAMS :
    for (i = 0; server_v->teams_name[i] ; i++) {
        if (str_in_str(server_v->teams_name[i],team)) {
            cli->ai->team = strdup(team);
            if (cli->ai->team == NULL)
                error("Error : malloc failed");
            break;
        }
    }
    cli->ai->level = 0;
    if (!server_v->teams_name[i]) {
        error_s(cli->fd);
        tna(cli->fd, cli, server_v, "error");
        memset(team, 0 , 50);
        recv(cli->fd, team, 50, 0);
        goto TEAMS;
    }
    pnw(cli);
    return true;
}

static bool create_fst_client(client_t **hd, int new, server_t *serv, char *tp)
{
    (*hd) = malloc(sizeof(client_t));
    if ((*hd) == NULL)
        return false;
    (*hd)->fd = new;
    (*hd)->prev = NULL;
    (*hd)->next = NULL;
    (*hd)->type = return_type(tp);
    serv->head = (*hd);
    free(tp);
    return true;
}

static bool create_new_client(client_t *cli, int new_fd, char *type)
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
    cli->type = return_type(type);
    return true;
}

void create_client(client_t **head, int new_fd, server_t *server_v)
{
    client_t *cli = NULL;
    char *type = NULL;

    type = init_buffer(type, new_fd);
    if (!(*head)) {
        if (create_fst_client(head, new_fd, server_v, type) == false)
            error("Error : Creation of the first client");
        return;
    }
    for (cli = *head; cli->next != NULL; cli = cli->next);
    if (create_new_client(cli, new_fd, type) == false)
        error("Error : Creation new client");
    if (cli->type == GRAPHIC) {
        cli->ai = NULL;
        free(type);
        return;
    }
    if (create_new_client_ia(cli, server_v) == false)
        error("Error : creation new client's IA");
    free(type);
}
