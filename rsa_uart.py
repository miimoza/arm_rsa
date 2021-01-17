#!/usr/bin/env python3

import sys
import hashlib
import getpass
import base64
from serial import Serial, SerialException
from Crypto.Cipher import PKCS1_v1_5
from Crypto.PublicKey import RSA

def main(argv):
    if (len(argv) <= 1 or (argv[1] != "sign" and argv[1] != "public")):
        print("usage: ./script.py sign [FILE_PATH]")
        print("usage: ./script.py public")
        exit()

    try:
        s = Serial(port='/dev/ttyACM0', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=0, rtscts=0)
    except SerialException:
        print("Cannot open serial port")
        exit()


    if (argv[1] == "sign"):
        if (len(argv) <= 2):
            print("usage: ./script.py sign [FILE_PATH]")
            exit()

        try:
            file = open(argv[2])
        except IOError:
            print("Cannot open file")
            exit()

        s.write("SIG".encode())

        sha256 = hashlib.sha256(file.read().encode('utf-8')).digest()
        file.close()

        s.write(sha256)
        passphrase = getpass.getpass("Passphrase: ")
        sendpassword(s, passphrase)

        status = readline(s)
        print(status.title())

        if (status == "CORRECT PASSPHRASE"):
            private_key = readline(s)
            print("Encrypted SHA-256:", encrypt(sha256, private_key).decode('utf-8'))

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

def encrypt(message, key):
    key = RSA.importKey(key)
    rsa_object = PKCS1_v1_5.new(key)
    cipher_text = rsa_object.encrypt(message)
    cipher_text = base64.b64encode(cipher_text)
    return cipher_text

if __name__ == "__main__":
    main(sys.argv)
