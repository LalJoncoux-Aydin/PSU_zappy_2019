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
client_t *get_client_by_fd( client_t *head, int fd)
{
    for (; head != NULL; head = head->next) {
        if (head->fd == fd)
            return head;
    }
    printf("cli null %d head null ? %d\n", fd, (head == NULL));
    return NULL;
}


*/

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
        printf("CLI of type %s connected\n",
        (!(strlen(str) < 7) && (str[5] == 'a' && str[6] == 'i'))? "AI" : "GRAPHIC");
    if (strlen(str) < 7)
        return -1;
    if (str[5] == 'a' && str[6] == 'i')
        return AI;
    return GRAPHIC;
}
void add_cli_spe(client_t *cli, server_t *server_v, char *team)
{
    int i = 0;

    if (cli->type == GRAPHIC)
        return;
    cli->ai = malloc(sizeof(client_t));
    cli->ai->x = get_rand_num(0, server_v->x, 100);
    cli->ai->y = get_rand_num(0, server_v->y, 100);
    if (cli->ai->y > server_v->y / 2)
        cli->ai->orientation = NORTH;
    else
        cli->ai->orientation = SOUTH;
    cli->ai->player_number = nbr_player++;
    TEAMS :
    for (i = 0; server_v->teams_name[i] ; i++) {
        if (str_in_str(server_v->teams_name[i],team)){
            printf("<->%s<->%s<->\n",server_v->teams_name[i], team);
            printf("VICTOIRE\n");
            cli->ai->team = strdup(team);
            break;
        }
    }
    cli->ai->level = 0;
    if (!server_v->teams_name[i]) {
        printf("%s\n",team);
        printf("ai teams  : %s\n->not found error\n", team);
        error_s(cli->fd);
        tna(cli->fd, cli, server_v, "error");
        memset(team, 0 , 50);
        recv(cli->fd, team, 50, 0);
        goto TEAMS;
    }
    pnw(cli);
}

void add_cli(client_t **head, int new_fd, server_t *server_v)
{
    client_t *buff = *head;
    client_t *buff_prev = NULL;
    char *type = malloc(50);
    char *team = malloc(50);
    int size = 0;

    memset(type, 0 , 50);
    memset(team, 0 , 50);
    recv(new_fd, type, 50, 0);
    size = recv(new_fd, team, 50, 0);
    team[size -1] = '\0';
    if (!(*head)) {
        (*head) = malloc(sizeof(client_t));
        (*head)->fd = new_fd;
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->type = return_type(type);
        free(type);
        return add_cli_spe((*head),server_v, team);
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
    return  add_cli_spe(buff,server_v, team);
}

static void manage_message(char *msg, int *tri_force, client_t *clis, server_t *server)
{
    int sender_fd = tri_force[1];

    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (str_in_str(commands[i].command, msg))
            commands[i].func(sender_fd, clis, server, msg);
    }

    //int fd_count = tri_force[0];
    //
    //  SEND TO EVERY ONE
    //for (int j = 0; j < fd_count; j++)
    //    if (pfds[j].fd != sockfd && pfds[j].fd != sender_fd)
    //        if (send(pfds[j].fd, msg, strlen(msg), 0) == -1)
    //            perror("send");
}


 //
 //static void manage_event(struct pollfd *pfds, int *fd_count, server_t *server_v, int *fd_size)
 //{
 //    struct sockaddr_storage cli_addr;
 //    socklen_t addrlen = sizeof(struct sockaddr_storage);
 //    int nbytes;
 //    char buff[256 * 4];
 //    static client_t *head = NULL;
 //
 //    for (int i = 0; i < *fd_count;printf("fd_count , fds_ssize , i : %d %d %d\n",*fd_count , *fd_size, i),i++)
 //        if (pfds[i].revents & POLLIN) {
 //            if (pfds[i].fd == server_v->server_fd) {
 //                add_new_fd(&pfds, accept(server_v->server_fd, (struct sockaddr *)&cli_addr,
 //                &addrlen), fd_count, fd_size);
 //                add_cli(&head, pfds[(*fd_count) - 1].fd);
 //            }
 //            else {
 //                memset(buff, 0, sizeof(buff));
 //                nbytes = recv(pfds[i].fd, buff, sizeof(buff), 0);
 //                if (nbytes <= 0)
 //                    del_from_pfds(pfds, i, fd_count, &head);
 //                buff[nbytes] = '\0';
 //                printf("message ressu :%s|\n", buff);
 //                manage_message(buff,
 //                tri_force(*fd_count, pfds[i].fd, 0), head, server_v);
 //            }
 //        }
 //}
 //
 //int server(server_t *server_v)
 //{
 //    server_v->server_fd = prepare_server_socket(server_v->port);
 //    int fd_count = 1;
 //    int fd_size = 10;
 //    struct pollfd *pfds = malloc(sizeof(struct pollfd) * (fd_size  + 1));
 //
 //    pfds[0].fd = server_v->server_fd;
 //    pfds[0].events = POLLIN;
 //    while (1) {
 //        if (poll(pfds, fd_count, -1) == -1)
 //            error("poll failed");
 //        manage_event(pfds, &fd_count, server_v, &fd_size);
 //    }
 //}
 //


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
        }
        buff[nbytes] = '\0';
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