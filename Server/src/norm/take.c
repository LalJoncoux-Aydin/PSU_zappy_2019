#include "client.h"
#include "tools.h"
#include "server.h"
#include <string.h>

void take_modifier2(client_t *clis, tile_t **map, int i)
{
    int y =  clis->ai->y;
    int x =  clis->ai->x;

    switch (i) {
        case 4:
        clis->ai->invent->q4 += map[y][x].q4;
        map[y][x].q4 = 0;
        break; case 5:
        clis->ai->invent->q5 += map[y][x].q5;
        map[y][x].q5 = 0;
        break; case 6:
        clis->ai->invent->q6 += map[y][x].q6;
        map[y][x].q6 = 0;
        break;
    }
}

void take_modifier(client_t *clis, tile_t **map, int i)
{
    int y =  clis->ai->y;
    int x =  clis->ai->x;

    switch (i) {
        case 0:
        clis->ai->invent->q0 += map[y][x].q0;
        map[y][x].q0 = 0;
        break; case 1:
        clis->ai->invent->q1  += map[y][x].q1;
        map[y][x].q1 = 0;
        break; case 2:
        clis->ai->invent->q2 += map[y][x].q2;
        map[y][x].q2 = 0;
        break; case 3:
        clis->ai->invent->q3 += map[y][x].q3;
        map[y][x].q3 = 0;
        break;
    }
    if (i > 3)
        take_modifier2(clis, map, i);
}

void take(int fd_cli, client_t *clis, server_t *server_v, char *command)
{
    char *buff = malloc(70);
    char *obj = str_breaker(command, ' ', 2, 0);

    char *keys[7] = {"food" , "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame"};
    for (int i = 0; i < 7; i++)
        if (obj[0] == keys[i][0] && obj[1] == keys[i][1] &&
        obj[2] == keys[i][2] && obj[3] == keys[i][3])
            take_modifier(clis, server_v->map, i);
}

void inventory(int fd_cli, client_t *clis, server_t *server, char *command)
{
    char *buff = malloc(120);
    ai_s *ai = clis->ai;

    if (!ai || !buff)
        return error_s(fd_cli);
    sprintf(buff, "[food %d, linemate %d, deraumere %d, \
sibur %d, mendiane %d, phiras %d, thystame %d]"
    , ai->invent->q0, ai->invent->q1, ai->invent->q2,
    ai->invent->q3, ai->invent->q4, ai->invent->q5, ai->invent->q6);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s\n", buff);
    free(buff);
}

void brodcast(int fd_cli, client_t *clis, server_t *server, char *command)
{
    char *buff = malloc(120);
    client_t *cli = server->head;

    for (;*command && *command != ' '; command += 1);
    command += 1;
    sprintf(buff, "mesage %d %d, %s", clis->ai->x, clis->ai->y, command);
    for (;cli; cli = cli->next)
        if (cli->type == AI)
            send(cli->fd, buff, strlen(buff), 0);
}