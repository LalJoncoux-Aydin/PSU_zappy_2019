##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## player
##

from random import randint
from enum import Enum
import json

#---------------------------------------------------------- Remove

import time

#---------------------------------------------------------- Remove

from Client.src.network import Network

class GameRunner:

    def __init__(self, team_name):
        self.socket = []
        self.info = {}
        self.team_name = team_name
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

    def disconnectAll(self):
        try:
            for socs in self.socket:
                socs.disconnect()
        except Exception as e:
            print(e)
            exit(0)

    def connectClient(self, infos):
        try:
            self.socket.append(Network(infos["host"], int(infos["port"])))
            print("connection client 1 => ", self.socket[-1].connectClient())
            print("max_id + len socket", self.max_player_id, len(self.socket))
            self.max_player_id += 1
        except Exception as e:
            print(e)
            exit(0)

    def sendMsg(self, msg, minionsNb):
        try:
            self.socket[minionsNb].sendMsg(msg + "\n")
        except Exception as e:
            print(e)
            exit(0)

    def rcvMsg(self, minionsNb):
        try:
            return (self.socket[minionsNb].rcvMsg())
        except Exception as e:
            print(e)
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

    def prepare(self, minionsNb):
        self.sendMsg("type ai\n", minionsNb)
        # print(self.rcvMsg(minionsNb))
        self.sendMsg("team " + self.team_name, minionsNb)
        # print(self.rcvMsg(minionsNb))

    def prepareShit(self, info, minionsNb):
        try:
            if (self.connectClient(info) == -1):
                exit(0)
            self.prepare(minionsNb)
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
            self.sendMsg(self.buildMsg("Incantation", incant["minionsID"]), incant["minionsID"])
            self.inventory[incant["minionsID"]]["Food"] -= 300
            for name in self.stoneNames:
                self.inventory[incant["minionsID"]][name] -= self.elevationRules[incant["minionElev"]][name]

#--------------------------------------------------------------------------------------------- Elevation

#--------------------------------------------------------------------------------------------- Look

    def lookArround(self, minionsNb):
        self.sendMsg(self.buildMsg("Look", minionsNb), minionsNb)
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg(minionsNb)
        # print(tmp)
        self.sendMsg(self.buildMsg("Take object", minionsNb), minionsNb)
        print(tmp[2:-2])

#--------------------------------------------------------------------------------------------- Look

#--------------------------------------------------------------------------------------------- Fork

# """

# Need to remove comment prt and check

# """

    def fork(self, minionsNb):
        # self.max_player_id += 1
        # self.sendMsg(self.buildMsg("Connect_nbr", 0), minionsNb)
        # if (int(self.rcvMsg(minionsNb)) >= self.max_player_id):
            print("minions nb",minionsNb, "len socket", len(self.socket))
            self.sendMsg(self.buildMsg("Fork", 0), minionsNb)
            # print(self.rcvMsg(minionsNb))
            self.inventory[-1]["Food"] -= 42
            self.connectClient(self.info)
            self.prepare(minionsNb - 1)
            self.initInventory()

#--------------------------------------------------------------------------------------------- Fork

#--------------------------------------------------------------------------------------------- Movement basic

    def turnRight(self, minionsNb):
        self.sendMsg(self.buildMsg("Right", minionsNb), minionsNb)
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg(minionsNb)
        self.moveForward(minionsNb)
        print("Right", tmp)

    def turnLeft(self, minionsNb):
        self.sendMsg(self.buildMsg("Left", minionsNb), minionsNb)
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg(minionsNb)
        self.moveForward(minionsNb)
        print("Left", tmp)

    def moveForward(self, minionsNb):
        self.sendMsg(self.buildMsg("Forward", minionsNb), minionsNb)
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg(minionsNb)
        print("Forward",tmp)

    def moveBackward(self, minionsNb):
        self.sendMsg(self.buildMsg("Backward", minionsNb), minionsNb)
        self.inventory[minionsNb]["Food"] -= 7
        tmp = self.rcvMsg(minionsNb)
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
        self.sendMsg(self.buildMsg("Take object", minionsNb), minionsNb)
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
            self.sendMsg(self.buildMsg("Left", minionsNb), minionsNb)
            self.sendMsg(self.buildMsg("Look", minionsNb), minionsNb)
            self.goGetAtindex(12, minionsNb)
            i += 1
        self.inventory[minionsNb]["Food"] -= (7 * 2) * i

#--------------------------------------------------------------------------------------------- Ressources Focus

#--------------------------------------------------------------------------------------------- Entry

    def letsGo(self, info, debug):
        if (debug == False):
            self.info = info
            if (self.prepareShit(info, 0) == 84):
                return (84)
        self.loadShit()
        # print(self.rcvMsg(0))
        i = 0
        while (i < 10):
            print(i)
            self.fork(i)
            i += 1
            time.sleep(4)
            # self.checkAllArround(0)
            # if (self.inventory[0]["Food"] < 0): break
        return (0)

#--------------------------------------------------------------------------------------------- Entry