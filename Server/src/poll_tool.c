/*
** EPITECH PROJECT, 2019
** jo
** File description:
** poll_tool.c
*/

#include <stdlib.h>
#include <poll.h>

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

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    close(pfds[i].fd);
    pfds[i] = pfds[*fd_count - 1];
    (*fd_count)--;
}
