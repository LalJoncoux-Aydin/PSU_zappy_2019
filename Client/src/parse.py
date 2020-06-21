##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## parse
##

key = ["-p", "-n", "-h"]
matching_key = ["port", "name", "host"]

infos = {
    "host": "localhost",
    "name": "",
    "port": ""
}

def print_help(bin_name, code):
    print("USAGE: " + bin_name + " -p port -n name")
    print("\tport\t\tis the port number")
    print("\tname\t\tis the name of the team")
    print("\tmachine\t\tis the name of the machine; localhost by default")
    exit(code)

def parse(param):

    if (len(param) == 2 and param[1] == "-h") : print_help(param[0], 0)
    if (len(param) == 2 and param[1] == "-help") : print_help(param[0], 0)
    if (len(param) < 5) : print_help(param[0], 84)
    i = 1
    while (i < len(param)):
        check = 0
        while (check < len(key)):
            if (key[check].find(param[i]) != - 1):
                infos[matching_key[check]] = param[i + 1]
            check += 1
        i += 1
    if (infos["name"] == "" or infos["port"] == "") : return None
    return (infos)
