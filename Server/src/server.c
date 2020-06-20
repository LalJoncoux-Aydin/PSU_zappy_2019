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

static int nbr_player = 0;

/*
getaddrinfo();
socket();
bind();
listen();
accept()
*/

int eq_str(char *str1, char *str2)
{
    for (int i = 0; str1[i] && str2[i]; i++)
        if (str1[i] != str2[i])
            return 0;
    return 1;
}

int str_in_str(char *needle, char *haystackt)
{
    for (int i = 0; haystackt[i] ; i++) {
        for (int y = 0; needle[y] == haystackt[i]; y++) {
            if (needle[y + 1] == '\0')
                return 1;
            if (haystackt[i++] == '\0')
                return 0;
        }
    }
    return 0;
}

int return_type(char *str)
{
    if (DEBUG)
        printf("CLI of type %s connected (msg recv : %s\n",
        (!(strlen(str) < 7) && (str[5] == 'a' && str[6] == 'i'))? "AI" : "GRAPHIC", str);
    if (strlen(str) < 7)
        return -1;
    if (str[5] == 'a' && str[6] == 'i')
        return AI;
    return GRAPHIC;
}
inventory_t *init_invent()
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
    for (i = 0; server_v->teams_name[i] ; i++) {
        if (str_in_str(server_v->teams_name[i],team)){
            cli->ai->team = strdup(team);
            break;
        }
    }
    if (!server_v->teams_name[i]) {
        error_s(cli->fd);
        tna(cli->fd, cli, server_v, "error");
        memset(team, 0 , 50);
        //recv(cli->fd, team, 50, 0);
        add_cli_teams(cli, server_v);
    }
}

void add_cli_spe(client_t *cli, server_t *server_v)
{
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

void add_cli(client_t **head, int new_fd, server_t *server_v)
{
    client_t *buff = *head;
    client_t *buff_prev = NULL;
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
    for (; buff->next != NULL ; buff = buff->next );
    buff->next = malloc(sizeof(client_t));
    buff_prev = buff;
    buff = buff->next;
    buff->fd = new_fd;
    buff->type  = return_type(type);
    buff->next = NULL;
    buff->prev = buff_prev;
    free(type);
    return  add_cli_spe(buff, server_v);
}
// !! CHANGEMENT ICI -1
static void manage_message(char *msg, int *tri_force, client_t *clis, server_t *server)
{
    int sender_fd = tri_force[1];

    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (str_in_str(commands[i].command, msg)) {
            if (occurrences_of_char(' ', msg) != commands[i].nb_of_arg 
            && commands[i].nb_of_arg != -1 ) {
                send(clis->fd, "sbp\n", 4, 0);
                return;
            }
            else
                return commands[i].func(sender_fd, clis, server, msg);
        }
    }
    send(clis->fd, "suc\n", 4, 0);
}


static void manage_event(fd_set *master,server_t *server_v, int i, int *fd_max)
{
    struct sockaddr_storage cli_addr;
    socklen_t addrlen = sizeof(struct sockaddr_storage);
    int nbytes;
    static client_t *head = NULL;
    char buff[256 * 4];
    int new_fd;

    if (i == server_v->server_fd) {
        if ((new_fd = accept( server_v->server_fd, (struct sockaddr *)&cli_addr, &addrlen)) == -1)
            error("accept failed that's unnacceptable");
        FD_SET(new_fd, master);
        *fd_max = new_fd > *fd_max ? new_fd : *fd_max;
        add_cli(&head, new_fd, server_v);
        //printf("CLi %d added\n", head->fd);
    } else {
        if ((nbytes = recv(i, buff, sizeof(buff), 0)) <= 0) {
            del_cli(&head, i);
            close(i);
            FD_CLR(i, master);
            return;
        }
        buff[nbytes] = '\0';
        printf("msg ressive form %d  : %s\n",i , buff);
        manage_message(buff,
        tri_force(*fd_max, i, 0), head, server_v);
    }
}

int server(server_t *server_v)
{
    server_v->server_fd = prepare_server_socket(server_v->port);
    int fd_max;
    fd_set master;
    fd_set read_fds;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(server_v->server_fd , &master);
    fd_max = server_v->server_fd ;
    while (1) {
        read_fds = master;
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1)
            error("select");
        for (int i = 0; i <= fd_max; i++)
            if (FD_ISSET(i, &read_fds))
                manage_event(&master, server_v, i, &fd_max);
    }
}