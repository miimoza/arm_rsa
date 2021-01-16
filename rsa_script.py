#!/usr/bin/python3

import signal
import sys
import struct
import os.path
from time import sleep

from serial import Serial, SerialException

send_sha = "1"
init_pwd = "2"
askpubk = "3"
askpriv = "4"

reservedStrings = [ b'\r', b'\n']

def completePwd(pwd):
    lenght = len(pwd)
    if lenght == 10:
        return pwd
    elif lenght > 10:
        return pwd[:-(lenght - 10)]
    else:
        s = pwd
        cpt = 10 - lenght
        while cpt != 0:
            s += '\0'
            cpt -= 1
        return s


def myreadline(s):
    eol = b'\r'
    leneol = len(eol)
    line = bytearray()
    while True:
        c = s.read(1)
        if c:
            line += c
            if line[-leneol:] == eol:
                break
        else:
            break
    return bytes(line)

def sendSha256(s):
    s.write(send_sha.encode('ascii'))
    sleep(0.2)
    s.readline() #consume OK from uC
    print("Send sha256 to uC")
    s.write(shaa[:-1].encode('ascii'))
    print(s.readline().decode('ascii'))
    print(s.readline().decode('ascii'))

def initPwd(s):
    s.write(init_pwd.encode('ascii'))
    s.readline() #consume OK from uC
    val = s.readline() #consume OK from uC
    if val == b'KOO\n':
        print("Password already init")
        return
    print("Password init (10 caractères): ")
    val = sys.stdin.readline()
    while len(val[:-1]) != 10:
        print("You miss, pwd need 10 caractères")
        val = sys.stdin.readline()
    s.write(val[:-1].encode('ascii'))

    print(s.readline().decode('ascii'))
    print("RSA_Key generating and Melting KeyGen processing...")
    print(s.readline().decode('ascii'))

def askPwd(s, key):
    s.write(key.encode('ascii'))
    s.readline() #consume OK from uC

    print("Enter password: ")
    val = completePwd(sys.stdin.readline()[:-1])
    s.write(val.encode('ascii'))
    s.readline() #consume OK from uC
    return s.readline()[:-1]



with open(sys.argv[1], 'rb') as sha:
    shaa = sha.read().decode('ascii')
    try:
        s = Serial(port='/dev/ttyACM0', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=0, rtscts=0)
    except SerialException:
        print("Can't open serial")
        exit()

    sendSha256(s)
    sleep(0.5)
    #initPwd(s)
    #askPwd(s, "nice")


    print("exit")

    exit()
