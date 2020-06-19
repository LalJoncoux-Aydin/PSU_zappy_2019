#include "command.h"

ai_s *get_ai_by_nb(server_t *server_v, int nb)
{
    for (client_t *buff = server_v->head; buff; buff = buff->next)
        if ( buff->type == AI && nb == buff->ai->player_number)
                    return buff->ai;
    return NULL;
}
