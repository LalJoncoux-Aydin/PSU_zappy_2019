##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## player
##

from random import randint
from enum import Enum
import json

import time

#---------------------------------------------------------- Remove
import inspect
from types import FrameType
from typing import cast

DEBUG = False

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
        self.possibleElem = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"]
        self.stoneNames = []
        self.inventory = []

#--------------------------------------------------------------------------------------------- Network

    def disconnectAll(self):
        try:
            for socs in self.socket:
                socs.disconnectClient()
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
        if (DEBUG == True) : print(cast(FrameType, cast(FrameType, inspect.currentframe()).f_back).f_code.co_name)
        try:
            return (self.socket[minionsNb].rcvMsg())
        except Exception as e:
            print(e)
            exit(0)

#--------------------------------------------------------------------------------------------- Network

#--------------------------------------------------------------------------------------------- Tool

    def removeDuplicate(self, listOfDict):
        seen = set()
        new_l = []
        for d in listOfDict:
            t = tuple(d.items())
            if t not in seen:
                seen.add(t)
                new_l.append(d)
        return (new_l)

    def buildMsg(self, message, minionsNb):
        return str(message + "\n")

    def initInventory(self):
        tmp = {}
        for stone in self.stoneNames:
            tmp[stone] = 0
        tmp["food"] = 1000
        tmp["lvl"] = 0
        self.inventory.append(tmp)

    def loadShit(self):
        try:
            file = open("./rules/rules.json", "r")
            data = json.load(file)
            self.elevationRules = data["lvlUpRules"]
            self.stoneNames = data["stoneName"]
            self.initInventory()
        except:
            exit(84)

    def prepare(self, minionsNb):
        print(self.rcvMsg(minionsNb))
        self.sendMsg(self.team_name, minionsNb)
        print(self.rcvMsg(minionsNb))


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
        while i < len(self.inventory):
            lvlup = 0
            for lvl in self.elevationRules:
                points = 0
                try:
                    for name in self.stoneNames:
                        if (self.inventory[i][name] >= lvl[name]) : points += 1
                    if points == len(self.stoneNames):
                        listLvlUp.append({"minionsID" : i, "minionsElev" : lvl})
                except:
                    pass
                lvlup += 1
                self.inventory[i]
            i += 1
        print(listLvlUp)
        return (listLvlUp)

    def startIncantation(self, incantationPossibilites):
        if len(incantationPossibilites) == 0: return
        try:
            for incant in incantationPossibilites:
                if (self.inventory[incant["minionsID"]]["food"] < 350): continue
                self.sendMsg(self.buildMsg("Incantation", incant["minionsID"]), incant["minionsID"])
                self.inventory[incant["minionsID"]]["food"] -= 300
                for name in self.stoneNames:
                    self.inventory[incant["minionsID"]][name] -= self.elevationRules[incant["minionElev"]][name]
        except:
            pass
#--------------------------------------------------------------------------------------------- Elevation

#--------------------------------------------------------------------------------------------- Look

    def lookArround(self, minionsNb):
        self.sendMsg(self.buildMsg("Look", minionsNb), minionsNb)
        time.sleep(2)
        return (self.rcvMsg(minionsNb))

#--------------------------------------------------------------------------------------------- Look

#--------------------------------------------------------------------------------------------- Take

    def TakeElem(self, elem, nbElem, minionsNb):
        elem = elem.replace(",", "")
        print("Take \"" + elem + "\"")
        time.sleep(1)
        self.sendMsg(self.buildMsg("Take " + elem, minionsNb), minionsNb)
        self.inventory[minionsNb][elem] += nbElem
        return (self.rcvMsg(minionsNb))

#--------------------------------------------------------------------------------------------- Take

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
            self.inventory[-1]["food"] -= 42
            self.connectClient(self.info)
            self.prepare(minionsNb - 2)
            self.initInventory()

#--------------------------------------------------------------------------------------------- Fork

#--------------------------------------------------------------------------------------------- Movement basic

    def turnRight(self, minionsNb):
        self.sendMsg(self.buildMsg("Right", minionsNb), minionsNb)
        self.inventory[minionsNb]["food"] -= 7
        self.rcvMsg(minionsNb)
        self.moveForward(minionsNb)

    def turnLeft(self, minionsNb):
        self.sendMsg(self.buildMsg("Left", minionsNb), minionsNb)
        self.inventory[minionsNb]["food"] -= 7
        self.rcvMsg(minionsNb)
        self.moveForward(minionsNb)

    def moveForward(self, minionsNb):
        self.sendMsg(self.buildMsg("Forward", minionsNb), minionsNb)
        self.inventory[minionsNb]["food"] -= 7
        self.rcvMsg(minionsNb)

    def moveBackward(self, minionsNb):
        self.turnLeft(minionsNb)
        self.turnLeft(minionsNb)
        self.moveForward(minionsNb)

#--------------------------------------------------------------------------------------------- Movement basic

#--------------------------------------------------------------------------------------------- Movement

    def goGetAtindex(self, index, minionsNb, elem_list):
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

        for elem in self.possibleElem:
            print("try to take => ", elem)
            self.sendMsg(self.buildMsg("take " + elem, minionsNb), minionsNb)
            time.sleep(2)
            print(self.rcvMsg(minionsNb))

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

#--------------------------------------------------------------------------------------------- Find Need

    def whatDoIneed(self, lookResult, minionsNb):
        lookResult = lookResult.replace("[", "")
        lookResult = lookResult.replace("]", "")
        lookResult = lookResult.split(", ")[0].split(" ")
        try:
            lookResult.remove("")
        except:
            pass
        try:
            lookResult.remove("player")
        except:
            pass
        index = []

        if (self.inventory[minionsNb]["food"] < 400 and lookResult.count("food") > 0):
            index.append({"elem" : "food", "nbEleme" : lookResult.count("food")})
            lookResult.remove("food")
        if len(lookResult) > 0:
            for elem in lookResult:
                index.append({"elem" : elem, "nbElem" : lookResult.count(elem)})
        return (self.removeDuplicate(index))

#--------------------------------------------------------------------------------------------- Find Need

#--------------------------------------------------------------------------------------------- Ressources Focus

    def checkAllArround(self, minionsNb):
        i = 0
        while (i < 4):
            self.turnLeft(minionsNb)
            lookResult = self.lookArround(minionsNb)
            print("Look => ", lookResult)
            index_list = self.whatDoIneed(lookResult, minionsNb)
            print("need => ", index_list)

            for index in index_list:
                try:
                    print("take Elem => " + self.TakeElem(index["elem"], index["nbElem"], minionsNb))
                except:
                    pass
            self.turnRight(minionsNb)
            i += 1

#--------------------------------------------------------------------------------------------- Ressources Focus

#--------------------------------------------------------------------------------------------- Entry

    def letsGo(self, info, debug):
        if (debug == False):
            self.info = info
            if (self.prepareShit(info, 0) == 84):
                return (84)
        self.loadShit()

        while (42):
            self.checkAllArround(0)
            # self.startIncantation(self.checkElevation())
        return (0)

#--------------------------------------------------------------------------------------------- Entry