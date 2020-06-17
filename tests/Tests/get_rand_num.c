/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** get_rand_num
*/

#include <criterion/criterion.h>
#include "server.h"

Test(get_rand_num, error_cases)
{
    cr_expect_eq(get_rand_num(12, 10, 100), 12);
    
    int nb = get_rand_num(1, 100, 100);
    cr_expect(1 <= nb && nb <= 100);
}

// Faire tableau distri ? 