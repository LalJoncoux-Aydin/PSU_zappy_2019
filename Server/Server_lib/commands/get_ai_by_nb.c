/*
** EPITECH PROJECT, 2019
** server command
** File description:
** get_ai_by_nb.c
*/

#include "command.h"

ai_t *get_ai_by_nb(server_t *server_v, int nb)
{
    for (client_t *buff = server_v->head; buff; buff = buff->next)
        if (nb == buff->ai->player_number)
            return buff->ai;
    return NULL;
}
