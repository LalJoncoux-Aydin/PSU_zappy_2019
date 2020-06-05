#ifndef CLIENT_H_
#define CLIENT_H_

typedef struct client_s {
    int type;
    int fd;
    char *user_name;
    struct client_s *next;
} client_t;

#endif /* CLIENT_H_ */