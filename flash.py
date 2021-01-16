#!/usr/bin/python3

import signal
import sys
import struct
import os.path
from time import sleep

from serial import Serial, SerialException


flash_start = "#$FLASH_START"
flash_end = "#$FLASH_FINISH"
flash_erase = "#$ERASE_MEM"
flash_abort =  "#$FLASH_ABORT"

print(flash_start, flash_end, flash_erase, flash_abort)

with open(sys.argv[1], 'rb') as binary:
    try:
        s = Serial(port='/dev/ttyACM0', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=0, rtscts=0)
    except SerialException:
        print("Can't open serial")
        exit()

    print("Flashing...")
    s.write(flash_start.encode('ascii'))
    perm = s.readline()
    print("Flash Started")
    while (byte := binary.read(4)):
        s.write(byte)
    binary.seek(0)
    print("Flash OK")
    s.write(flash_end.encode('ascii'))
    exit()
