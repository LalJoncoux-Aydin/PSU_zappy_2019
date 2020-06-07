/*
** EPITECH PROJECT, 2019
** point h
** File description:
** HEADER
*/

#ifndef SERVER_H_
#define SERVER_H_

//Standard include
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
//Private include
#include "command.h"
#include "tools.h"

enum {
    AI,
    GRAPHIC
};

typedef struct server_s {
    char *port;
    char **teams_name;
    int nbr_max_per_teams;
    int x;
    int y;
    int freq;
} server_t;

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define HELP "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n\t\
port is the port number\n\t\
width is the width of the world\n\t\
height is the height of the world\n\t\
nameX is the name of the team X\n\t\
clientsNb is the number of authorized clients per team\n\t\
freq is the reciprocal of time unit for execution of actions\n"

void error(char *msg);
int *tri_force(int a, int b, int c);

void add_end_file(char *str, char *str_name);

void add_new_fd(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count);

int occurrences_of_char(char c, char *str);
int server(server_t *port);
int prepare_server_socket(char *port);

#endif /* SERVER_H_ */
