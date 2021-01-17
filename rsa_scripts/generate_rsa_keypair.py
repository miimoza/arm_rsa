#!/usr/bin/python3

from Crypto.Cipher import PKCS1_v1_5
from Crypto.PublicKey import RSA
import urllib.parse
import base64
from os import path
from Crypto.PublicKey import RSA
from Crypto import Random
from Crypto.Cipher import AES, PKCS1_OAEP


def generate_keys(key_size):
    key_pair = RSA.generate(key_size)
    private_key = key_pair.exportKey('PEM')
    pubkey = key_pair.publickey().exportKey('PEM')
    return private_key, pubkey

key_size = 1024
key_pair = generate_keys(key_size)
privkey = key_pair[0]
pubkey = key_pair[1]

print(privkey, '\n', pubkey)
