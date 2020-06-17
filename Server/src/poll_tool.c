/*
** EPITECH PROJECT, 2019
** jo
** File description:
** poll_tool.c
*/
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include "client.h"

client_t *get_client_by_fd( client_t *head, int fd)
{
    if (head)
        for (; head != NULL; head = head->next) {
            if (head->fd == fd)
                return head;
        }
    //printf("cli null %d head null ? %d\n", fd, (head == NULL));
    return NULL;
}


void add_new_fd(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    if (*fd_count == *fd_size) {
        *fd_size *= 2;
        *pfds = realloc(*pfds, sizeof(struct pollfd **) * (*fd_size));
    }
    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN;
    (*fd_count)++;
}

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
//void del_cli(client_t **head, int fd)
//{
//    client_t *client = get_client_by_fd((*head),fd);
//
//    if (client->prev != NULL)
//        client->prev->next = client->next;
//    else
//        (*head) = (*head)->next;
//    free(client);
//}
//
//void del_from_pfds(struct pollfd pfds[], int i, int *fd_count, client_t **head)
//{
//
//    del_cli2(head, i);
//    close(pfds[i].fd);
//    pfds[i] = pfds[*fd_count - 1];
//    (*fd_count)--;
//}
