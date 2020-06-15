#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>



enum {
    NORTH = 1,
    ESAST,
    SOUTH,
    WEST
};

typedef struct ai_specific_s {
    int player_number;
    int x;
    int y;
    int orientation;
    int level;
    char *team;
} ai_s;

typedef struct client_s {
    int type;
    int fd;
    char *user_name;
    ai_s *ai;
    struct client_s *next;
    struct client_s *prev;
} client_t;

client_t *get_client_by_fd( client_t *head, int fd);

#endif /* CLIENT_H_ */