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
        self.moveValue = ["forward", "backward", "left", "rigth"]
        self.moveTools = {
            "forward" : self.moveForward,
            "backward" : self.moveBackward,
            "left" : self.moveLeft,
            "rigth" : self.moveRight
        }

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
        tmp = self.rcvMsg()
        # print(tmp)
        print(tmp[2:-2])

    def moveRight(self):
        self.sendMsg("Right")
        self.foodStock -= 7
        tmp = self.rcvMsg()
        print("Right", tmp)

    def moveLeft(self):
        self.sendMsg("Left")
        self.foodStock -= 7
        tmp = self.rcvMsg()
        print("Left", tmp)

    def moveForward(self):
        self.sendMsg("Forward")
        self.foodStock -= 7
        tmp = self.rcvMsg()
        print("Forward",tmp)

    def moveBackward(self):
        self.sendMsg("Backward")
        self.foodStock -= 7
        tmp = self.rcvMsg()
        print("Backward", tmp)

    def letsGo(self, info, debug):
        if (debug == False):
            if (self.prepareShit(info) == 84):
                return (84)
        self.loadShit()
        print("ok")
        i = 0
        while (42):
            self.lookArround()
            self.moveTools[self.moveValue[i]]()
            if (self.foodStock < 0):
                break
            i += 1
            if i > 3 : i = 0
        return (0)

