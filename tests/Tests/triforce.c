/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** triforce
*/

#include "server.h"
#include <criterion/criterion.h>

Test(Triforce, test1)
{
    int *test_values = tri_force(1, 2, 3);

    cr_expect_eq(test_values[0], 1);
    cr_expect_eq(test_values[1], 2);
    cr_expect_eq(test_values[2], 3);
    // cr_expect_eq(test_values[2], 1);
}