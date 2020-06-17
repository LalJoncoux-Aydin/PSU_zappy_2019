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
            "left" : self.turnLeft,
            "rigth" : self.turnRight
        }
        self.inventory = []

#--------------------------------------------------------------------------------------------- Network

    def disconnect(self):
        try:
            self.socket.disconnect()
        except:
            exit(0)

    def connectClient(self, infos):
        try:
            self.socket = Network(infos["host"], int(infos["port"]))
            return (self.socket.connectClient())
        except:
            exit(0)

    def sendMsg(self, msg):
        try:
            self.socket.sendMsg(msg)
        except:
            exit(0)

    def rcvMsg(self):
        try:
            return (self.socket.rcvMsg())
        except:
            exit(0)

#--------------------------------------------------------------------------------------------- Network

#--------------------------------------------------------------------------------------------- Tool

    def buildMsg(self, message, minionsNb):
        return str(str(minionsNb) + " " + message)

    def initInventory(self):
        tmp = {}
        for stone in self.stoneNames:
            tmp[stone] = 0
        tmp["Food"] = 1000
        tmp["lvl"] = 0
        self.inventory.append(tmp)

    def loadShit(self):
        file = open("./rules/rules.json", "r")
        data = json.load(file)
        self.elevationRules = data["lvlUpRules"]
        self.stoneNames = data["stoneName"]
        self.initInventory()

    def prepare(self):
        self.sendMsg("type ai\n")
        self.sendMsg("team " + self.team_name)

    def prepareShit(self, info):
        try:
            if (self.connectClient(info) == -1):
                return (84)
            self.prepare()
            return (0)
        except Exception as e:
            print (e)
            return (84)

#--------------------------------------------------------------------------------------------- Tool

#--------------------------------------------------------------------------------------------- Elevation

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

    def startIncantation(self, incantationPossibilites):
        if len(incantationPossibilites) == 0: return
        for incant in incantationPossibilites:
            if (self.inventory[incant["minionsID"]]["Food"] < 350): continue
            self.sendMsg(self.buildMsg("Incantation", incant["minionsID"]))
            self.inventory[incant["minionsID"]]["Food"] -= 300
            for name in self.stoneNames:
                self.inventory[incant["minionsID"]][name] -= self.elevationRules[incant["minionElev"]][name]

#--------------------------------------------------------------------------------------------- Elevation

#--------------------------------------------------------------------------------------------- Look

    def lookArround(self, minionsNb):
        self.sendMsg(self.buildMsg("Look", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        # print(tmp)
        self.sendMsg(self.buildMsg("Take object", minionsNb))
        print(tmp[2:-2])

#--------------------------------------------------------------------------------------------- Look

#--------------------------------------------------------------------------------------------- Fork

    def fork(self):
        self.sendMsg(self.buildMsg("Connect_nbr", 0))
        if (int(self.rcvMsg()) >= self.max_player_id):
            self.sendMsg(self.buildMsg("Fork", 0))

#--------------------------------------------------------------------------------------------- Fork

#--------------------------------------------------------------------------------------------- Movement basic

    def turnRight(self, minionsNb):
        self.sendMsg(self.buildMsg("Right", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        self.moveForward(minionsNb)
        print("Right", tmp)

    def turnLeft(self, minionsNb):
        self.sendMsg(self.buildMsg("Left", minionsNb))
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg()
        self.moveForward(minionsNb)
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

#--------------------------------------------------------------------------------------------- Movement basic

#--------------------------------------------------------------------------------------------- Movement

    def goGetAtindex(self, index, minionsNb):
        loopMax = 0
        tmp = 0
        tmp_save = 0
        i = 0

        if (index >= 1):
            loopMax = 1
            tmp_save = tmp = 2
        if (index >= 4):
            loopMax = 2
            tmp_save = tmp = 6
        if (index >= 9):
            loopMax = 3
            tmp_save = tmp = 12

        while (i < loopMax):
            self.moveForward(minionsNb)
            i += 1
        while (tmp <= index):
            self.turnRight(minionsNb)
            tmp += 1
        while (tmp >= index):
            self.turnLeft(minionsNb)
            tmp -= 1
        self.sendMsg(self.buildMsg("Take object", minionsNb))
        while (tmp <= tmp_save):
            self.turnRight(minionsNb)
            tmp += 1
        while (tmp >= tmp_save):
            self.turnLeft(minionsNb)
            tmp -= 1
        while (i >= 0):
            self.moveBackward(minionsNb)
            i -= 1

#--------------------------------------------------------------------------------------------- Movement

#--------------------------------------------------------------------------------------------- Ressources Focus

    def checkAllArround(self, minionsNb):
        i = 0
        while (i < 4):
            self.sendMsg(self.buildMsg("Left", minionsNb))
            self.sendMsg(self.buildMsg("Look", minionsNb))
            self.goGetAtindex(12, minionsNb)
            i += 1
        self.inventory[minionsNb]["Food"] -= (7 * 2) * i

#--------------------------------------------------------------------------------------------- Ressources Focus

#--------------------------------------------------------------------------------------------- Entry

    def letsGo(self, info, debug):
        if (debug == False):
            if (self.prepareShit(info) == 84):
                return (84)
        self.loadShit()
        print(self.rcvMsg())
        while (42):
            self.checkAllArround(0)
            if (self.inventory[0]["Food"] < 0): break
        return (0)

#--------------------------------------------------------------------------------------------- Entry