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
#include "server.h"
#include "client.h"
#include "command.h"
#include "command_tab.h"

void del_cli(client_t **head, int fd)
{
    client_t *temp = *head;
    client_t *prev;

    if (temp != NULL && temp->fd == fd) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->fd != fd) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

static void manage_message(char *msg, int *tri_force, client_t *clis,
server_t *server)
{
    int sender_fd = tri_force[1];

    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (str_in_str(commands[i].command, msg)) {
            if (occurrences_of_char(' ', msg) != commands[i].nb_of_arg
            && commands[i].nb_of_arg != -1) {
                send(clis->fd, "sbp\n", 4, 0);
                return;
            }
            return commands[i].func(sender_fd, clis, server, msg);
        }
    }
    send(clis->fd, "suc\n", 4, 0);
}

static void create_client(fd_set *master, server_t *serv,
client_t **head, int *fd_max)
{
    struct sockaddr_storage cli;
    socklen_t sockl = sizeof(struct sockaddr_storage);
    int new;

    if ((new = accept(serv->server_fd,
        (struct sockaddr *)&cli, &sockl)) == -1)
        error("accept failed that's unnacceptable");
    FD_SET(new, master);
    *fd_max = new > *fd_max ? new : *fd_max;
    add_cli(head, new, serv);
}

/* if ((new_fd = accept(server_v->server_fd,
        (struct sockaddr *)&cli_addr, &addrlen)) == -1)
            error("accept failed that's unnacceptable");
        FD_SET(new_fd, master);
        *fd_max = new_fd > *fd_max ? new_fd : *fd_max;
        add_cli(&head, new_fd, server_v);*/
static void manage_event(fd_set *master, server_t *server_v, int i, int *fd_max)
{
    int nbytes;
    static client_t *head = NULL;
    char buff[256 * 4];

    if (i == server_v->server_fd) {
        create_client(master, server_v, &head, fd_max);
    } else if ((nbytes = recv(i, buff, sizeof(buff), 0)) <= 0) {
        del_cli(&head, i);
        close(i);
        FD_CLR(i, master);
        return;
    } else {
        buff[nbytes] = '\0';
        printf("msg ressive form %d  : %s\n", i , buff);
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
    fd_max = server_v->server_fd;
    while (1) {
        read_fds = master;
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1)
            error("select");
        for (int i = 0; i <= fd_max; i++)
            if (FD_ISSET(i, &read_fds))
                manage_event(&master, server_v, i, &fd_max);
    }
}