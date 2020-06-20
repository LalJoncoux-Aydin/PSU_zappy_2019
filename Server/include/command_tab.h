/*
** EPITECH PROJECT, 2019
** include
** File description:
** command_tab.h
*/

#ifndef cmd_TAB_H_
#define cmd_TAB_H_

#include "command.h"

static command_manager_t commands[NBR_OF_COMMAND] = {
    {"msz", msz, 0},
    {"bct", bct, 2},
    {"mct", mct, 0},
    {"tna", tna, 0},
    {"ppo", ppo_plv_pin, 1},
    {"plv", ppo_plv_pin, 1},
    {"pin", ppo_plv_pin, 1},
    {"Forward", forward, 0},
    {"Right", turn, 0},
    {"Left", turn, 0},
    {"Look", look, 0},
    {"Take", take, 1},
    {"Inventory", inventory, 0},
    {"Broadcast", brodcast, -1}
};

#endif