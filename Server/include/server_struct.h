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

#include <stdbool.h>

enum _orientation {
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3,
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

typedef struct client_s {
    bool type;
    int fd;
    char *team;
    int id;
    int x;
    int y;
    int look_x;
    int look_y;
    enum _orientation orientation;
    int level;
    inventory_t *invent;
    struct client_s *next;
    struct client_s *prev;
} client_t;

typedef struct server_s {
    int server_fd;
    char *port;
    char **teams_name;
    int nbr_max_per_teams;
    int nb_player;
    int x;
    int y;
    inventory_t **map;
    int freq;
    client_t *head;
} server_t;

#endif /* SERVERSTRUCT_H_ */
