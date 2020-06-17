#include "client.h"
#include "command.h"
#include "tools.h"

/*

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
*/