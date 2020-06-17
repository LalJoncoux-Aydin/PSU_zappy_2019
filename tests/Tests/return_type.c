/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** return_type
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "tools.h"
#include "server.h"

void setup(void)
{
    cr_redirect_stdout(); // Btw, pourquoi ne pas Fprintf et mettre le log dans stderr ?
}

Test(return_type, errors, .init=setup)
{
    cr_expect_eq(return_type(""), -1);
    cr_expect_eq(return_type("untest"), -1);
    cr_expect_eq(return_type("ai"), -1);
}

Test(return_type, AI, .init=setup)
{
    cr_expect_eq(return_type("soloaai"), AI);
    cr_expect_eq(return_type("jesusaietc"), AI);
    cr_expect_eq(return_type("     ai     "), AI);
}

Test(return_type, GRAPHIC, .init=setup)
{
    cr_expect_eq(return_type("jeroulematetesurleclavier"), GRAPHIC);
    cr_expect_eq(return_type("cecinestpasuneia"), GRAPHIC);
    cr_expect_eq(return_type("1234567"), GRAPHIC);
}

// OK