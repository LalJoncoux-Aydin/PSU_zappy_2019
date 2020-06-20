#include "client.h"
//#include "command.h"
#include "tools.h"
#include "server.h"
#include <string.h>

typedef struct {
    int x;
    int y;
} coor;

coor *coord_init(int x, int y)
{
    coor *res = malloc(sizeof(coor));

    res->x = x;
    res->y = y;
    return res;
}

//x/y_mod -> NORTH ,EAST, SOUTH, WEST
//// * 0,  1 2 3 ,   4 5 6 7 8 ,  9 10 11 12 13 14 15
//
//int get_nbs_of_players(server_t *server_v)
//{
//    client_t *buff = server_v->head;
//    int i = 0;
//
//    for (; buff; buff = buff->next)
//        if (buff->type == AI)
//            i++;
//    return i;
//}
//
//coor *get_coor_of_players(server_t *server_v)
//{
//    coor *res = malloc(sizeof(coor) *(get_nbs_of_player(server_v)  + 1));
//    client_t *buff = server_v->head;
//    int i = 0;
//    int j = 0;
//
//    if (!res)
//        return NULL;
//    for (i; buff; buff = buff->next)
//        if (buff->type == AI) {
//            res[j++].x = buff->ai->x;
//            res[j++].y = buff->ai->y;
//    }
//    res[j].x = -84;
//    res[j].y = -84;
//    return res;
//}

char *tab_to_str(char **tab)
{
    char *res;
    int size = 0;
    int index = 0;

    for (int i = 0; tab[i] ; i++)
        size += strlen(tab[i]);
    res = malloc(size);
    for (int y = 0; tab[y] ; y++)
        for (int x = 0; tab[y][x] ; x++)
           res[index++] = tab[y][x];
    res[index] = '\0';
    return res;
}

char *check_for_player(coor coords, server_t *server_v)
{
    char *buff = malloc(32);

    for (client_t *clis = server_v->head; clis; clis = clis->next)
        if (clis->type == AI && clis->ai->x == coords.x && clis->ai->y == coords.y) {
            sprintf(buff, "Player %d here\n", clis->ai->player_number);
            return buff;
        }
    return NULL;
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
        ,coords[i].x ,coords[i].y, tile->q0, tile->q1, tile->q2, tile->q3,
        tile->q4, tile->q5, tile->q6
        , players_here ? players_here : "\n");
        printf("%s",buff[i]);
    }
    buff[16] = NULL;
    return tab_to_str(buff);
}

coor *x_y_available(coor *act , int orientation, coor *max)
{
    coor *available = malloc(sizeof(coor) * 16);
    int xmod[5] = {-42, 1, 0, -1, 0};
    int ymod[5] = {-42, 0, -1, 0, 1};
    int stepx[5] = {-42, -1, 1, 1, -1};
    int stepy[5] = {-42, -1, -1, 1, 1};

    if (orientation < NORTH || orientation > WEST)
        return NULL;
    available[0].x = act->x;
    available[0].y = act->y;
    available[1].x = act->x + stepx[orientation];
    available[1].y = act->y + stepy[orientation];
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
    for (int i = 2; i < 16; i++)
        if(available[i].y < 0 || available[i].y >= max->y - 1)
            available[i].y = -1;
        else if (available[i].x < 0 || available[i].x >= max->x -1)
            available[i].x = -1;
    return available;
}

void look(int fd_cli, client_t *clis , server_t *server_v, char *command)
{
    char *buff;

    coor *available = x_y_available(coord_init(clis->ai->x, clis->ai->y),
    clis->ai->orientation, coord_init(server_v->x, server_v->y));
    buff = parse_available(available, server_v);
    if (!buff)
        return;
    send(fd_cli, buff, strlen(buff), 0);
    //buff_cli->ai->orientation; // int orientation;
    //buff_cli->ai->x / y ;// position du jouer
    //map[buff_cli->ai->y][buff_cli->ai->x].q0; // q0 a la tile a la possition du jouer
    //map[buff_cli->ai->y][buff_cli->ai->x + 1].q0; // q0 a la tile a l'ouest de la possition du jouer
}

//int main(int ac, char **av)
//{
//    coor *act; // actual position of the player
//    act->x = 3;
//    act->y = 3;
//    coor *max; // max map
//    max->x = 50;
//    max->y = 50;
//
//    coor *avai =  x_y_available(act, NORTH, max);
//
//    for (int i = 0; i < 16; i++)
//        printf("avais[%d] x = %d , y %d\n", i, avai[i].x, avai[i].y);
//}