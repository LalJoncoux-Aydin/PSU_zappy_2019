#ifndef CLIENT_H_
#define CLIENT_H_

typedef struct client_s {
    int stade;
    char *id;
    char *id_teams;
    int fd;
    int file_fd;
    char *user_name;
    char **teams_name;
    struct client_s *next;
    struct client_s *prev;
} client_t;

#endif /* CLIENT_H_ */