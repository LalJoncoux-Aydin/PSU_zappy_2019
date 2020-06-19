#include "command.h"

void mct(int fd_cli, client_t *clis __attribute__((unused)), server_t *server ,char *command  __attribute__((unused)))
{
    char *buff = malloc(50);
    char *res = malloc(50);
    tile_t *tile;// = &(server->map[y][x]);

    memset(buff, 0, 50);
    memset(res, 0, 50);
    for (int y = 0; y < server->y; y++)
        for (int x = 0; x < server->x; x++) {
            tile = &(server->map[y][x]);
            sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n"
            , x, y,tile->q0, tile->q1, tile->q2, tile->q3, tile->q4, tile->q5, tile->q6);
            res = str_concat(res, buff);
        }
    if (DEBUG)
        printf("message send : %s",res);
    send(fd_cli, res, strlen(res), 0);
    free(res);
}
