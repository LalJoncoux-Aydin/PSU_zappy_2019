##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## player
##

from random import randint
from enum import Enum

from Client.src.network import Network

import json

class GameRunner:

    def __init__(self, team_name):
        self.socket = None
        self.team_name = team_name
        self.foodStock = 100
        self.elevationRules = []
        self.currentLvl = 0
        self.stoneName = []

    def connectClient(self, infos):
        self.socket = Network(infos["host"], int(infos["port"]))
        return (self.socket.connectClient())

    def sendMsg(self, msg):
        self.socket.sendMsg(msg)

    def rcvMsg(self):
        return (self.socket.rcvMsg())

    def loadShit(self):
        file = open("./rules/rules.json", "r")
        data = json.load(file)
        self.elevationRules = data["lvlUpRules"]
        self.stoneName = data["stoneName"]

    def prepareShit(self, info):
        try:
            if (self.connectClient(info) == -1):
                return (84)
            self.sendMsg(self.team_name)
            return (0)
        except Exception as e:
            print (e)
            return (84)

    def lookArround(self):
        self.sendMsg("Look")
        self.foodStock -= 7
        print("Look => ", self.rcvMsg())

    def letsGo(self, info, debug):
        if (debug == False):
            if (self.prepareShit(info) == 84):
                return (84)
        self.loadShit()
        print("ok")
        while (42):
            self.lookArround()
            if (self.foodStock < 50):
                break
        return (0)

