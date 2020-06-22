/*
** EPITECH PROJECT, 2019
** server
** File description:
** map.c
*/

#include "map.h"

bool create_map(server_t *server_v)
{
    server_v->map = malloc(sizeof(inventory_t *) * (server_v->y + 1));
    if (server_v->map == NULL)
        return false;
    for (int y = 0; y < server_v->y; y++) {
        server_v->map[y] = malloc(sizeof(inventory_t) * (server_v->x + 1));
        if (server_v->map[y] == NULL) {
            free(server_v->map);
            return false;
        }
        for (int x = 0; x < server_v->x; x++) {
            server_v->map[y][x].q0 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q1 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q2 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q3 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q4 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q5 = get_rand_num(0, 6, 50);
            server_v->map[y][x].q6 = get_rand_num(0, 6, 50);
        }
    }
    return true;
}
