/*
** EPITECH PROJECT, 2019
** server
** File description:
** get_socket.c
*/

#include "get_socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

static struct addrinfo *init_addrinfo(char *port)
{
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, port, &hints, &res))
        error("getaddinfo failed");
    return res;
}

static void error_check_prep_server(struct addrinfo *test, int sockfd, int op)
{
    if (test == NULL) {
        if (sockfd == -1)
            error("socket function failed");
        else if (op == -1)
            error("setsocktopt failed");
        else
            error("bind failed");
    }
}

int get_socket(char *port)
{
    struct addrinfo *res = NULL;
    struct addrinfo *cpy_head = NULL;
    int sockfd;
    int yes = 1;

    res = init_addrinfo(port);
    if (res == NULL)
        return -1;
    for (cpy_head = res; cpy_head != NULL; cpy_head = cpy_head->ai_next) {
        if ((sockfd = socket(cpy_head->ai_family, cpy_head->ai_socktype, cpy_head->ai_protocol)) == -1)
            continue;
        if ((yes = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
            continue;
        if (bind(sockfd, cpy_head->ai_addr, cpy_head->ai_addrlen) == -1)
            continue;
        break;
    }
    error_check_prep_server(cpy_head, sockfd, yes);
    freeaddrinfo(res);
    if (listen(sockfd, 10) == -1)
        error("listen failed");
    return sockfd;
}
