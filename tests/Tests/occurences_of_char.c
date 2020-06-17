/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** occurences_of_char
*/

#include <criterion/criterion.h>
#include "server.h"

Test(occurrences_of_char, char_exists)
{
    cr_expect_eq(occurrences_of_char('c', "ccccc"), 5);
    cr_expect_eq(occurrences_of_char('y', "Only one match here"), 1);
    cr_expect_eq(occurrences_of_char('1', "don't read this 8745783583052348952834597234959384529348595782395982395825391592475294572894582394597694858245789639597968596528345806204852"), 1);
    cr_expect_eq(occurrences_of_char('1', "don't read this 87457835830523489528345972349593845293485957823959823958253915924752945728945823945976948582457896395979685965283458062048521"), 2);
}

Test(occurrences_of_char, char_does_not_exist)
{
    cr_expect_eq(occurrences_of_char('y', "This is a test string!"), 0);
    cr_expect_eq(occurrences_of_char('Z', "This is a DUH test with a very long string not containing the seeked char"), 0);
}

Test(occurrences_of_char, special_cases)
{
    cr_expect_eq(occurrences_of_char('\0', "lol"), 0);
    cr_expect(occurrences_of_char('a', NULL) == 0, "ERROR: This probably has crashed");
    cr_expect_eq(occurrences_of_char('a', ""), 0);
}

// Split, string longue