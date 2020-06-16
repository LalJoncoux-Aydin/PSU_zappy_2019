##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## player
##

from random import randint
from enum import Enum
import json

from Client.src.network import Network

class GameRunner:

    def __init__(self, team_name):
        self.socket = None
        self.team_name = team_name
        self.team_id = 0
        self.max_player_id = 0
        self.elevationRules = []
        self.currentLvl = 0
        self.stoneNames = []
        self.moveValue = ["forward", "backward", "left", "rigth"]
        self.moveTools = {
            "forward" : self.moveForward,
            "backward" : self.moveBackward,
            "left" : self.moveLeft,
            "rigth" : self.moveRight
        }
        self.inventory = []

    def disconnect(self):
        self.socket.disconnect()

    def connectClient(self, infos):
        self.socket = Network(infos["host"], int(infos["port"]))
        return (self.socket.connectClient())

    def sendMsg(self, msg):
        self.socket.sendMsg(msg)

    def rcvMsg(self):
        return (self.socket.rcvMsg())

    def buildMsg(self, message, minionsNb):
        return str(self.team_id) + "-" + str(minionsNb) + " " + message

    def initInventory(self):
        tmp = {}
        for stone in self.stoneNames:
            tmp[stone] = 0
        tmp["Food"] = 1000
        self.inventory.append(tmp)

    def loadShit(self):
        file = open("./rules/rules.json", "r")
        data = json.load(file)
        self.elevationRules = data["lvlUpRules"]
        self.stoneNames = data["stoneName"]
        self.initInventory()

    def prepare(self):
        self.sendMsg("\"type ai\n")
        self.rcvMsg()
        self.sendMsg("\"team " + self.team_name + "\"")
        self.team_id = int(self.rcvMsg())

    def checkElevation(self):
        listLvlUp = []
        i = 0
        while i <= self.max_player_id:
            lvl = 0
            for lvl in self.elevationRules:
                points = 0
                try:
                    for name in self.stoneNames:
                        if (self.inventory[i][name] >= lvl[name]) : points += 1
                    if points == len(self.stoneNames):
                        listLvlUp.append({"minionsID" : i, "minionsElev" : lvl})
                except:
                    pass
                lvl += 1
                self.inventory[i]
            i += 1
        return (listLvlUp)

    def prepareShit(self, info):
        try:
            if (self.connectClient(info) == -1):
                return (84)
            self.prepare()
            return (0)
        except Exception as e:
            print (e)
            return (84)

    def lookArround(self, minionsNb):
        self.sendMsg(self.buildMsg("Look", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        # print(tmp)
        self.sendMsg(self.buildMsg("Take object", minionsNb))
        print(tmp[2:-2])

    def fork(self):
        self.sendMsg(self.buildMsg("Connect_nbr", 0))
        if (int(self.rcvMsg()) >= self.max_player_id):
            self.sendMsg(self.buildMsg("Fork", 0))

    def startIncantation(self, minionsNb):
        if (self.inventory[minionsNb]["Food"] < 350): return
        self.sendMsg(self.buildMsg("Incantation", minionsNb))
        self.inventory[minionsNb]["Food"] -= 300

    def moveRight(self, minionsNb):
        self.sendMsg(self.buildMsg("Right", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        print("Right", tmp)

    def moveLeft(self, minionsNb):
        self.sendMsg(self.buildMsg("Left", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        print("Left", tmp)

    def moveForward(self, minionsNb):
        self.sendMsg(self.buildMsg("Forward", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        print("Forward",tmp)

    def moveBackward(self, minionsNb):
        self.sendMsg(self.buildMsg("Backward", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        print("Backward", tmp)

    def letsGo(self, info, debug):
        if (debug == False):
            if (self.prepareShit(info) == 84):
                return (84)
        self.loadShit()
        i = 0
        while (42):
            self.lookArround(0)
            self.moveTools[self.moveValue[i]]()
            if (self.inventory[0]["Food"] < 0): break
            i += 1
            if i > 3 : i = 0
        return (0)
