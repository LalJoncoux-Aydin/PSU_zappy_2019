/*
** EPITECH PROJECT, 2019
** include
** File description:
** client.h
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>

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

typedef struct ai_specific_s {
    int player_number;
    int x;
    int y;
    int orientation;
    int level;
    inventory_t *invent;
    char *team;
    struct ai_specific_s *next;
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


typedef struct {
    int x;
    int y;
} coor;


#endif /* CLIENT_H_ */