#ifndef SERVERSTRUCT_H_
#define SERVERSTRUCT_H_

#define DEBUG 1

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
} server_t;

#endif
