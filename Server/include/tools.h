#ifndef TOOLS_H_
#define TOOLS_H_

#define DEBUG 1

enum {
    AI,
    GRAPHIC
};

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>

#include "server_struct.h"

char *str_breaker(char *line, char delim, int part, int strict);
void error(char *msg);
void error_s(int fd);
int *tri_force(int a, int b, int c);
int str_in_str(char *needle, char *haystackt);
int occurrences_of_char(char c, char *str);
void add_end_file(char *str, char *str_name);
int get_rand_num(int min, int max, int percent);
int occurrences_of_char(char c, char *str);
void add_new_fd(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);
client_t *get_client_by_fd( client_t *head, int fd);
char *str_concat(char *con, char *cat);
int return_type(char *str);

#endif /* TOOLS_H_ */
