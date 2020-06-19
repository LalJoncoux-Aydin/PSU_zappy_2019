#include "client.h"
#include "command.h"
#include "tools.h"
//#include "server.h"

typedef struct {
    int x;
    int y;
} coor;

//x/y_mod -> NORTH ,EAST, SOUTH, WEST
// * 0,  1 2 3 ,   4 5 6 7 8 ,  9 10 11 12 13 14 15

int **x_y_available(coor act , int orientation, coor max)
{
    coor *available = malloc(sizeof(coor) * 16);
    int xmod[4] = {1, 0, -1, 0};
    int ymod[4] = {0, -1, 0, 1};
    int stepx[4] = {-1, 1, 1, -1};
    int stepy[4] = {-1, -1, 1, 1};

    available[0].x = act.x;
    available[0].y = act.y;
    available[1].x = act.x + stepx[orientation];
    available[1].y = act.y + stepy[orientation];
    for (int i = 2; i < 16; i++) {
        if (i == 9) {
            available[i].x = act.x + stepx[orientation] * 3;
            available[i].y = act.y + stepy[orientation] * 3;
            continue;
        }
        if (i == 4) {
            available[i].x = act.x + stepx[orientation] * 2;
            available[i].y = act.y + stepy[orientation] * 2;
            continue;
        }
        available[i].y = available[i].y + ymod[orientation];
        available[i].x = available[i].x + xmod[orientation];
    }
    for (int i = 2; i < 16; i++)
        if(available[i].y < 0 || available[i].y >= max.y)
            available[i].y = -1;
        else if (available[i].x < 0 || available[i].x >= max.x)
            available[i].x = -1;
    return available;
}

void look(int fd_cli, client_t *clis  __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    client_t *buff_cli;
    tile_t **map = server->map;

    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    buff_cli = get_ai_by_nb(server, nb);
    if (!buff_cli || !buff)
        return error_s(fd_cli);
    //buff_cli->ai->orientation; // int orientation;
    //buff_cli->ai->x / y ;// position du jouer
    //map[buff_cli->ai->y][buff_cli->ai->x].q0; // q0 a la tile a la possition du jouer
    //map[buff_cli->ai->y][buff_cli->ai->x + 1].q0; // q0 a la tile a l'ouest de la possition du jouer
}
