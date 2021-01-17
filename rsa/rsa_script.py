#!/usr/bin/env python3

import hashlib
import getpass
from serial import Serial, SerialException

def readline(file):
    line = ""
    while 1:
        char = file.read(1)
        if char == b'\n':
            break
        line += char.decode("utf-8")
    return line

def sendpassword(s, upass):
    s.write(str.encode(upass))
    s.write(str.encode("\x00" * (64 - len(upass))))

def main():
    sha256 = hashlib.sha256("ahah".encode('utf-8')).digest()

    try:
        s = Serial(port='/dev/ttyACM0', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=0, rtscts=0)
    except SerialException:
        print("can't open serial port")
        exit()

    s.write(sha256)
    passphrase = getpass.getpass("passphrase: ")
    sendpassword(s, passphrase)

    status = readline(s)
    print(status)

    if (status == "CORRECT PASSPHRASE"):
        print("Encrypted sha256:", s.readline())

    s.close()

if __name__ == "__main__":
    main()
