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
#include <poll.h>
//#include <unistd.h>
#include "server.h"

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
void add_cli(client_t **head, int new_fd)
{
    client_t *buff = *head;
    char *type = malloc(50);

    memset(type,0 , 50);
    read(new_fd, type, 50);
    if (!(*head)) {
        *head = malloc(sizeof(client_t));
        (*head)->fd = new_fd;
        (*head)->next = NULL;
        (*head)->type = strcmp(type, "type ai") ? GRAPHIC : AI;
        free(type);
        return;
    }
    for (; buff->next != NULL ; buff = buff->next );
    buff->next = malloc(sizeof(client_t));
    buff = buff->next;
    buff->fd = new_fd;
    buff->type = strcmp(type, "type ai") ? GRAPHIC : AI;
    buff->next = NULL;
    free(type);
    return;
}
static void manage_message(struct pollfd *pfds, char *msg, int *tri_force)
{
    int fd_count = tri_force[0];
    int sockfd = tri_force[1];
    int sender_fd = tri_force[2];

    for (int j = 0; j < fd_count; j++)
        if (pfds[j].fd != sockfd && pfds[j].fd != sender_fd)
            if (send(pfds[j].fd, msg, strlen(msg), 0) == -1)
                perror("send");
}

static void manage_event(struct pollfd *pfds, int *fd_count, int sockfd, int *fd_size)
{
    struct sockaddr_storage cli_addr;
    socklen_t addrlen = sizeof(struct sockaddr_storage);
    int nbytes;
    char buff[256 * 4];

    for (int i = 0; i < *fd_count; i++)
        if (pfds[i].revents & POLLIN) {
            if (pfds[i].fd == sockfd)
                add_new_fd(&pfds, accept(sockfd, (struct sockaddr *)&cli_addr,
                &addrlen), fd_count, fd_size);
            else {
                nbytes = recv(pfds[i].fd, buff, sizeof(buff), 0);
                if (nbytes <= 0)
                    del_from_pfds(pfds, i, fd_count);
                buff[nbytes] = '\0';
                //manage_message(pfds, buff,
                //tri_force(*fd_count, sockfd, pfds[i].fd));
            }
        }
}

int server(server_t *server_v)
{
    int sockfd = prepare_server_socket(server_v->port);
    int fd_count = 1;
    int fd_size = 5;
    struct pollfd *pfds = malloc(sizeof(struct pollfd) * fd_size);

    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;
    while (1) {
        if (poll(pfds, fd_count, -1) == -1)
            error("poll failed");
        manage_event(pfds, &fd_count, sockfd, &fd_size);
    }
}