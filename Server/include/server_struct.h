/*
** EPITECH PROJECT, 2019
** server
** File description:
** server_struct.h
*/

#ifndef SERVERSTRUCT_H_
#define SERVERSTRUCT_H_

#define NBR_OF_COMMAND 12
#define MESSAGE_SIZE 128
#define NB_CLIENT 15

enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
};

typedef struct ivent_s {
    int q0;
    int q1;
    int q2;
    int q3;
    int q4;
    int q5;
    int q6;
} inventory_t;

typedef struct ai_s {
    int player_number;
    int x;
    int y;
    int orientation;
    int level;
    inventory_t *invent;
    char *team;
    struct ai_s *next;
} ai_t;

typedef struct client_s {
    int type;
    int fd;
    char *user_name;
    ai_t *ai;
    struct client_s *next;
    struct client_s *prev;
} client_t;

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

#endif /* SERVERSTRUCT_H_ */
