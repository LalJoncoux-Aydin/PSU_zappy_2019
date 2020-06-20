##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## master
##

from Client.src.parse import parse, print_help
from Client.src.GameRunner import GameRunner
import sys

def master():
    param = parse(sys.argv)

    if (param == None) : print_help(84)
    player = GameRunner(param["name"])
    player.letsGo(param, False)
    player.disconnectAll()
    return (0)