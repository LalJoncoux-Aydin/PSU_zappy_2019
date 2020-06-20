/*
** EPITECH PROJECT, 2019
** Server
** File description:
** norms.c
*/

#include "client.h"
#include "tools.h"
#include "server.h"
#include <string.h>

coor *coord_init(int x, int y)
{
    coor *res = malloc(sizeof(coor));

    res->x = x;
    res->y = y;
    return res;
}

char *parse_available(coor *coords, server_t *server_v)
{
    tile_t *tile;
    char **buff = malloc(sizeof(char *) * 17);
    char *players_here;

    for (int i = 0; i < 16; i++) {
        if (coords[i].x == -1 || coords[i].y == -1) {
            buff[i] = strdup("ko\n");
            continue;
        }
        buff[i] = malloc(100);
        tile = &(server_v->map[coords[i].y][coords[i].x]);
        players_here = check_for_player(coords[i], server_v);
        sprintf(buff[i], "bct %d %d %d %d %d %d %d %d %d %s"
        , coords[i].x, coords[i].y, tile->q0, tile->q1, tile->q2, tile->q3,
        tile->q4, tile->q5, tile->q6
        , players_here ? players_here : "\n");
        printf("%s", buff[i]);
    }
    buff[16] = NULL;
    return tab_to_str(buff);
}

void x_y_available2(coor *act, int orientation, coor *available)
{
    int xmod[5] = {-42, 1, 0, -1, 0};
    int ymod[5] = {-42, 0, -1, 0, 1};
    int stepx[5] = {-42, -1, 1, 1, -1};
    int stepy[5] = {-42, -1, -1, 1, 1};

    for (int i = 2; i < 16; i++) {
        if (i == 9) {
            available[i].x = act->x + stepx[orientation] * 3;
            available[i].y = act->y + stepy[orientation] * 3;
            continue;
        }
        if (i == 4) {
            available[i].x = act->x + stepx[orientation] * 2;
            available[i].y = act->y + stepy[orientation] * 2;
            continue;
        }
        available[i].y = available[i - 1].y + ymod[orientation];
        available[i].x = available[i - 1].x + xmod[orientation];
    }
}

coor *x_y_available(coor *act, int orientation, coor *max)
{
    coor *available = malloc(sizeof(coor) * 16);
    int stepx[5] = {-42, -1, 1, 1, -1};
    int stepy[5] = {-42, -1, -1, 1, 1};

    if (orientation < NORTH || orientation > WEST)
        return NULL;
    available[0].x = act->x;
    available[0].y = act->y;
    available[1].x = act->x + stepx[orientation];
    available[1].y = act->y + stepy[orientation];
    x_y_available2(act, orientation, available);
    for (int i = 2; i < 16; i++)
        if (available[i].y < 0 || available[i].y >= max->y - 1)
            available[i].y = -1;
        else if (available[i].x < 0 || available[i].x >= max->x -1)
            available[i].x = -1;
    return available;
}

void look(int fd_cli, client_t *clis, server_t *server_v,
char *command  __attribute__((unused)))
{
    char *buff;

    coor *available = x_y_available(coord_init(clis->ai->x, clis->ai->y),
    clis->ai->orientation, coord_init(server_v->x, server_v->y));
    buff = parse_available(available, server_v);
    if (!buff)
        return;
    send(fd_cli, buff, strlen(buff), 0);
}
