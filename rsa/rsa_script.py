#!/usr/bin/env python3

import sys
import hashlib
import getpass
from serial import Serial, SerialException

def main(argv):
    if (len(argv) <= 1 or (argv[1] != "sign" and argv[1] != "public")):
        print("usage: ./script.py sign [FILE_PATH]")
        print("usage: ./script.py public")
        exit()

    try:
        s = Serial(port='/dev/ttyACM0', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=0, rtscts=0)
    except SerialException:
        print("Can't open serial port")
        exit()


    if (argv[1] == "sign"):
        s.write("SIG".encode())

        sha256 = hashlib.sha256("ahah".encode('utf-8')).digest()

        s.write(sha256)
        passphrase = getpass.getpass("Passphrase: ")
        sendpassword(s, passphrase)

        status = readline(s)
        print(status.title())

        if (status == "CORRECT PASSPHRASE"):
            print("Encrypted sha256:", readline_hex(s))

    if (argv[1] == "public"):
        s.write("PUB".encode())

        print(readline(s))

    s.close()

def readline(file):
    line = ""
    while 1:
        char = file.read(1)
        if char == b'\x00':
            break
        line += char.decode("utf-8")
    return line

def readline_hex(file):
    line = b''
    while 1:
        char = file.read(1)
        if char == b'\x00':
            break
        line += char
    return line.hex()

def sendpassword(s, upass):
    s.write(str.encode(upass))
    s.write(str.encode("\x00" * (64 - len(upass))))

if __name__ == "__main__":
    main(sys.argv)
