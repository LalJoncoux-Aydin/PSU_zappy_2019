/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** error
*/

#include "server.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_stdout(void)
{
    cr_redirect_stdout(); // Btw, pourquoi ne pas Fprintf et mettre le log dans stderr ?
}

Test(error, test1, .exit_code = 84, .init=redirect_all_stdout)
{
    error("Error occured\n");
    cr_assert_stdout_eq_str("Error occured\n");
}

Test(error, test2, .exit_code = 84, .init=redirect_all_stdout)
{
    error("Coucou\n");
    cr_assert_stdout_eq_str("Coucou\n");
}

Test(error, test3, .exit_code = 84, .init=redirect_all_stdout)
{
    error("");
    cr_assert_stdout_eq_str("");
}

// OK