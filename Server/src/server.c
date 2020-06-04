/*
** EPITECH PROJECT, 2019
** jo
** File description:
** server.c
*/

#include "server.h"

command_manager_t command_manger[NBR_OF_COMMAND] =
    {{"002", cli_logout},
    {"005", my_send}
    };

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

static void manage_message(fd_set *master, char *msg, int *tri_force, client_t *head)
{
    //int fd_max = tri_force[0];
    //int sockfd = tri_force[1];
    int fd_cli = tri_force[2];
    char *buff = NULL;

    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (msg != NULL && *msg != '\0')
            buff = str_breaker(msg,' ',1, 0);
        if (!buff)
            return;
        else if (!strcmp(buff, command_manger[i].command)){
            command_manger[i].func(get_client_by_fd(head, fd_cli), msg);
            break;
        }
    }
}*/

void add_cli(client_t **head, int new_fd)
{
    client_t *buff = *head;
    client_t *buff2;

    if (!(*head)) {
        *head = malloc(sizeof(client_t));
        (*head)->fd = new_fd;
        (*head)->next = NULL;
        (*head)->teams_name = NULL;
        (*head)->prev = NULL;
        return;
    }
    for (; buff->next != NULL ; buff = buff->next );
    buff->next = malloc(sizeof(client_t));
    buff2 = buff;
    buff = buff->next;
    buff->prev = buff2;
    buff->fd = new_fd;
    buff->teams_name = NULL;
    buff->next = NULL;
    return;
}

static void manage_event(fd_set *master, int sockfd, int i, int *fd_max)
{
    struct sockaddr_storage cli_addr;
    socklen_t addrlen = sizeof(struct sockaddr_storage);
    int nbytes;
    static client_t *head = NULL;
    char buff[256 * 4];
    int new_fd;

    if (i == sockfd) {
        if ((new_fd = accept(sockfd, (struct sockaddr *)&cli_addr, &addrlen)) == -1)
            error("accept failed that's unnacceptable");
        FD_SET(new_fd, master);
        *fd_max = new_fd > *fd_max ? new_fd : *fd_max;
        add_cli(&head, new_fd);
    } else {
        if ((nbytes = recv(i, buff, sizeof(buff), 0)) <= 0) {
            close(i);
            FD_CLR(i, master);
        }
        buff[nbytes] = '\0';
        //manage_message(master, buff,tri_force(*fd_max, sockfd, i), head);
    }
}

int server(char *port)
{
    int sockfd = get_server_socket(port);
    int fd_max;
    fd_set master;
    fd_set read_fds;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &master);
    fd_max = sockfd;
    while (1) {
        read_fds = master;
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1)
            error("select");
        for (int i = 0; i <= fd_max; i++)
            if (FD_ISSET(i, &read_fds))
                manage_event(&master, sockfd, i, &fd_max);
    }
}