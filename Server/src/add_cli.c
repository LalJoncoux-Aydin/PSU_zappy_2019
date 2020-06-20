/*
** EPITECH PROJECT, 2019
** jo
** File description:
** server.c
*/

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include <unistd.h>
#include "server.h"
#include "client.h"
#include "command.h"

inventory_t *init_invent(void)
{
    inventory_t *ret = malloc(sizeof(inventory_t));

    ret->q0 = 0;
    ret->q1 = 0;
    ret->q2 = 0;
    ret->q3 = 0;
    ret->q4 = 0;
    ret->q5 = 0;
    ret->q6 = 0;
    return ret;
}

void add_cli_teams(client_t *cli, server_t *server_v)
{
    char *team = malloc(50);
    int i = 0;

    i = recv(cli->fd, team, 50, 0);
    team[i -1] = '\0';
    printf("%s\n", team);
    for (i = 0; server_v->teams_name[i]; i++) {
        if (str_in_str(server_v->teams_name[i], team)){
            cli->ai->team = strdup(team);
            break;
        }
        printf("->%s\n", server_v->teams_name[i]);
    }
    if (!server_v->teams_name[i]) {
        error_s(cli->fd);
        tna(cli->fd, cli, server_v, "error");
        memset(team, 0 , 50);
        add_cli_teams(cli, server_v);
    }
}

void add_cli_spe(client_t *cli, server_t *server_v)
{
    static int nbr_player = 0;

    if (cli->type == GRAPHIC) {
        cli->ai = NULL;
        return;
    }
    cli->ai = malloc(sizeof(client_t));
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
    add_cli_teams(cli, server_v);
    pnw(cli);
}

void add_cli_end(client_t **head, int new_fd, server_t *server_v, char *type)
{
    client_t *buff = *head;
    client_t *buff_prev = NULL;

    for (; buff->next != NULL; buff = buff->next);
    buff->next = malloc(sizeof(client_t));
    buff_prev = buff;
    buff = buff->next;
    buff->fd = new_fd;
    buff->type = return_type(type);
    buff->next = NULL;
    buff->prev = buff_prev;
    free(type);
    return add_cli_spe(buff, server_v);
}

void add_cli(client_t **head, int new_fd, server_t *server_v)
{
    char *type = malloc(50);

    memset(type, 0 , 50);
    recv(new_fd, type, 50, 0);
    printf("new_fd : %d ->", new_fd);
    if (!(*head)) {
        (*head) = malloc(sizeof(client_t));
        (*head)->fd = new_fd;
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->type = return_type(type);
        server_v->head = (*head);
        free(type);
        return add_cli_spe((*head), server_v);
    }
    add_cli_end(head, new_fd, server_v, type);
}
