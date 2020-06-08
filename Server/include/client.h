#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>

typedef struct client_s {
    int type;
    int fd;
    char *user_name;
    struct client_s *next;
    struct client_s *prev;
} client_t;

client_t *get_client_by_fd( client_t *head, int fd);

#endif /* CLIENT_H_ */