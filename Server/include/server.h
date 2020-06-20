/*
** EPITECH PROJECT, 2019
** point h
** File description:
** HEADER
*/

#ifndef SERVER_H_
#define SERVER_H_

#define DEBUG 1
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
#include <stdio.h>
#include "client.h"
#include <time.h>
//Private include
//#include "command.h"
#include "tools.h"

enum {
    AI,
    GRAPHIC
};
typedef struct tile_s {
    int q0;
    int q1;
    int q2;
    int q3;
    int q4;
    int q5;
    int q6;
} tile_t;

typedef struct server_s {
    int server_fd;
    char *port;
    char **teams_name;
    int nbr_max_per_teams;
    int x;
    int y;
    tile_t **map;
    int freq;
    client_t *head;
} server_t;

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define HELP "USAGE: ./zappy_server -p port -x width -y \
height -n name1 name2 ... -c clientsNb -f freq\n\t\
port is the port number\n\t\
width is the width of the world\n\t\
height is the height of the world\n\t\
nameX is the name of the team X\n\t\
clientsNb is the number of authorized clients per team\n\t\
freq is the reciprocal of time unit for execution of actions\n"

void error(char *msg);
void error_s(int fd);
int *tri_force(int a, int b, int c);
int str_in_str(char *needle, char *haystackt);
int occurrences_of_char(char c, char *str);
char *str_concat(char *con, char *cat);

void add_end_file(char *str, char *str_name);

void add_new_fd(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count, client_t **head);
void del_cli(client_t **head, int fd);
int return_type(char *str);
int get_rand_num(int min, int max, int percent);
int occurrences_of_char(char c, char *str);
int server(server_t *port);
int prepare_server_socket(char *port);
char *tab_to_str(char **tab);
char *check_for_player(coor coords, server_t *server_v);
void add_cli(client_t **head, int new_fd, server_t *server_v);
#endif /* SERVER_H_ */
