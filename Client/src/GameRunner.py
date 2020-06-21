##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## player
##

from random import randint
from enum import Enum
import json
import os
import time

#---------------------------------------------------------- Remove
import inspect
from types import FrameType
from typing import cast

DEBUG = True

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

#--------------------------------------------------------------------------------------------- Network Tool

    def buildMsg(self, message, minionsNb):
        return str(message + "\n")

    def prepare(self, minionsNb):
        print(self.rcvMsg(minionsNb))
        self.sendMsg(self.team_name, minionsNb)
        self.max = int (self.rcvMsg(minionsNb).split("\n")[0])

#--------------------------------------------------------------------------------------------- Network Tool

#--------------------------------------------------------------------------------------------- Network

    def disconnectAll(self):
        try:
            for socs in self.socket:
                try: socs.disconnectClient()
                except:continue
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
            if (self.inventory[minionsNb]["isDead"] == True):
                return
        except: pass
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

    def loadShit(self):
        try:
            file = open("./rules/rules.json", "r")
            data = json.load(file)
            self.elevationRules = data["lvlUpRules"]
            self.stoneNames = data["stoneName"]
            self.initInventory()
        except:
            exit(84)

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

#--------------------------------------------------------------------------------------------- Inventory Tool

    def initInventory(self):
        tmp = {}
        for stone in self.stoneNames:
            tmp[stone] = 0
        tmp["food"] = 1000
        tmp["lvl"] = -1
        tmp["isDead"] = False
        self.inventory.append(tmp)

#--------------------------------------------------------------------------------------------- Inventory Tool

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
                    if points == len(self.stoneNames) and self.inventory[i]["lvl"] < lvl["lvl"]:
                        listLvlUp.append({"minionsID" : i, "minionsElev" : lvl})
                except:
                    pass
                lvlup += 1
                self.inventory[i]
            i += 1
        return (listLvlUp)

    def startIncantation(self, incantationPossibilites):
        if len(incantationPossibilites) == 0: return
        try:
            for incant in incantationPossibilites:
                if (self.inventory[incant["minionsID"]]["food"] < 350): continue
                self.sendMsg(self.buildMsg("Incantation", incant["minionsID"]), incant["minionsID"])
                status = self.rcvMsg(incant["minionsID"])
                print("Incantation satus => ", status)
                print("incant => ", incant)

                if (status == "ok" or status.find("Elevation underway") != -1) :
                    print("\nUPPPPPP\n")
                    self.inventory[incant["minionsID"]]["lvl"] += 1
                    self.inventory[incant["minionsID"]]["food"] -= 300
                    for name in self.stoneNames:
                        self.inventory[incant["minionsID"]][name] -= self.elevationRules[incant["minionElev"]][name]
        except:
            pass

#--------------------------------------------------------------------------------------------- Elevation

#--------------------------------------------------------------------------------------------- Look

    def cleanUpLook(self, lookResult):
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
        return (lookResult)

    def lookArround(self, minionsNb):
        self.sendMsg(self.buildMsg("Look", minionsNb), minionsNb)
        time.sleep(1)
        return (self.rcvMsg(minionsNb))

#--------------------------------------------------------------------------------------------- Look

#--------------------------------------------------------------------------------------------- Take

    def TakeElem(self, elem, nbElem, minionsNb):
        elem = elem.replace(",", "")
        elem = elem.replace(",", "")
        time.sleep(1)
        self.sendMsg(self.buildMsg("Take " + elem, minionsNb), minionsNb)
        self.inventory[minionsNb][elem] += nbElem
        return (self.rcvMsg(minionsNb))

#--------------------------------------------------------------------------------------------- Take

#--------------------------------------------------------------------------------------------- Fork

    def fork(self, minionsNb):
        self.sendMsg(self.buildMsg("Fork", minionsNb), minionsNb)
        status = self.rcvMsg(minionsNb)

        print("fork satus => " + status)
        if (status.find("ok") > -1):
            childpid = os.fork()
            if childpid == 0:
                self.connectClient(self.info)
                self.prepare(minionsNb + 1)
                self.initInventory()
            else:
                pass

#--------------------------------------------------------------------------------------------- Fork

#--------------------------------------------------------------------------------------------- Movement basic

    def turnRight(self, minionsNb):
        print("call for => ", minionsNb)
        self.sendMsg(self.buildMsg("Right", minionsNb), minionsNb)
        self.inventory[minionsNb]["food"] -= 7
        self.rcvMsg(minionsNb)
        self.moveForward(minionsNb)

    def turnLeft(self, minionsNb):
        print("call for => ", minionsNb)
        self.sendMsg(self.buildMsg("Left", minionsNb), minionsNb)
        self.inventory[minionsNb]["food"] -= 7
        self.rcvMsg(minionsNb)
        self.moveForward(minionsNb)

    def moveForward(self, minionsNb):
        print("call for => ", minionsNb)
        self.sendMsg(self.buildMsg("Forward", minionsNb), minionsNb)
        self.inventory[minionsNb]["food"] -= 7
        self.rcvMsg(minionsNb)

    def moveBackward(self, minionsNb):
        self.turnLeft(minionsNb)
        self.turnLeft(minionsNb)
        self.moveForward(minionsNb)

#--------------------------------------------------------------------------------------------- Movement basic

#--------------------------------------------------------------------------------------------- Find Need

    def whatDoIneed(self, lookResult, minionsNb):
        lookResult = self.cleanUpLook(lookResult)
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
        print("call for => ", minionsNb)
        i = 0
        while (i < 5):
            if (self.turnLeft(minionsNb) == "ko"):
                self.turnRight(minionsNb)
                self.turnRight(minionsNb)
            lookResult = self.lookArround(minionsNb)
            print("Look => ", lookResult)
            index_list = self.whatDoIneed(lookResult, minionsNb)

            for index in index_list:
                try:
                    print("take " + index["elem"] + "=> " + self.TakeElem(index["elem"], index["nbElem"], minionsNb))
                except:
                    pass
            self.turnRight(minionsNb)

            time.sleep(1)
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

            i = len(self.inventory) - 1

            self.checkAllArround(i)
            self.startIncantation(self.checkElevation())
            self.moveForward(i)
            self.moveForward(i)
            try:
                print("i =>", i, "len inventory =>", len(self.inventory), "len max =>", self.max)
                if ((i == 0 or i == 1) and len(self.inventory) < self.max):
                    self.fork(i)
            except:
                pass
        return (0)

#--------------------------------------------------------------------------------------------- Entry
