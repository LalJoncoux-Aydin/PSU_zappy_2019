##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## master
##

from Client.src.parse import parse
from Client.src.network import Network
import sys

def master():

    param = parse(sys.argv)
    print(param)