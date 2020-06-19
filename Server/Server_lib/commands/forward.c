#include "command.h"

void forward(int fd_cli, client_t *clis  __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    ai_s *ai;

    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    ai = get_ai_by_nb(server, nb);
    if (!ai || !buff)
        return error_s(fd_cli);
    switch (ai->orientation) {
        case NORTH :
        if (ai->y > 0)
            ai->y -= 1;
        break;
        case SOUTH :
        if (ai->y < server->y)
            ai->y += 1;
        break;
        case EAST :
        if (ai->x < server->x)
            ai->x += 1;
        break;
        case WEST :
        if (ai->x > 0)
            ai->x -= 1;
        break;
    }
}
