/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** str_in_str
*/

#include <criterion/criterion.h>
#include "server.h"

Test(str_in_str, matching)
{
    cr_expect_eq(str_in_str("test", "I'm a test string!"), 1);
    cr_expect_eq(str_in_str("t", "I'm a test string!"), 1);
    cr_expect_eq(str_in_str("'", "I'm a test string!"), 1);
    cr_expect_eq(str_in_str("I", "I'm a test string!"), 1);
    cr_expect_eq(str_in_str("!", "I'm a test string!"), 1);
    cr_expect_eq(str_in_str("i", "i'm a test string!"), 1); // multiple matchs
}

Test(str_in_str, not_matching)
{
    cr_expect_eq(str_in_str("not good", "I'm a test string!"), 0);
    cr_expect_eq(str_in_str("I'm a test string!", "test"), 0);
}

Test(str_in_str, special)
{
    cr_expect_eq(str_in_str("", "I'm a test string!"), 1);
    cr_expect_eq(str_in_str("", ""), 1);
    cr_expect_eq(str_in_str("m", ""), 0);
    cr_expect_eq(str_in_str("", "m"), 1);
    cr_expect_eq(str_in_str(NULL, NULL), 0);
    cr_expect_eq(str_in_str(NULL, "I'm a test string!"), 0);
    cr_expect_eq(str_in_str("test", NULL), 0);
}