##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## network
##

import socket

class Network:

    def __init__(self, host, port):
        self.socket = None
        self.hostname = host
        self.port = port

    def connectClient(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.hostname, self.port))
            return (0)
        except Exception as e:
            print(e)
            print("\n\nUseless BOY\n\n")
            exit(0)

    def disconnectClient(self):
        try:
            self.socket.close()
            return (0)
        except Exception as e:
            print (e)
            return (-1)

    def rcvMsg(self):
        try:
            msg = self.socket.recv(2048)
            msg = msg.decode()
            return (msg)
        except Exception as e:
            print (e)
            print("\n\nDEAD BOY\n\n")
            exit(0)

    def sendMsg(self, msg):
        try:
            msg = str.encode(msg + "\n")
            self.socket.send(msg)
            return (0)
        except Exception as e:
            print (e)
            print("\n\nDEAD BOY\n\n")
            exit(0)