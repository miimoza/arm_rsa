#!/usr/bin/python3

from Crypto.Cipher import PKCS1_v1_5
from Crypto.PublicKey import RSA
import urllib.parse
import base64
from os import path
import sys
from Crypto.PublicKey import RSA
from Crypto import Random
from Crypto.Cipher import AES, PKCS1_OAEP


def encrypt(message, key):
    key = RSA.importKey(key)
    rsa_object = PKCS1_v1_5.new(key)
    cipher_text = rsa_object.encrypt(message.encode())
    cipher_text = base64.b64encode(cipher_text)
    return cipher_text
