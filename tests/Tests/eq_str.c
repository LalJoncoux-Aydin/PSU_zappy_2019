/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** eq_str
*/

#include <criterion/criterion.h>
#include "tools.h"
#include "server.h"

Test(eq_str, equal)
{
    cr_expect_eq(eq_str("Test String", "Test String"), 1);
    cr_expect_eq(eq_str("1", "1"), 1);
    cr_expect_eq(eq_str("ThIs OnE iS nOtHiNg SpEcIaL", "ThIs OnE iS nOtHiNg SpEcIaL"), 1);
}

Test(eq_str, not_equal)
{
    cr_expect_eq(eq_str("Test String", "tEST sTRING"), 0);
    cr_expect_eq(eq_str("Test string", "Test"), 0);
    cr_expect_eq(eq_str("Test string", "string"), 0);
    cr_expect_eq(eq_str("Test", "Test string"), 0);
    cr_expect_eq(eq_str("t", "u"), 0);
}

Test(eq_str, special)
{
    cr_expect_eq(eq_str("", "Test"), 0);
    cr_expect_eq(eq_str("Test string", ""), 0);
    cr_expect_eq(eq_str(NULL, "toto"), 0);
    cr_expect_eq(eq_str("foo", NULL), 0);
    cr_expect_eq(eq_str(NULL, NULL), 0);
}

// Include incomplet