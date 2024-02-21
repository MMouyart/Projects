#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jan  2 17:48:49 2023

@author: user
"""

from ecies.utils import generate_eth_key
from ecies import encrypt, decrypt
from base64 import b64encode, b64decode
from Crypto.Cipher import ChaCha20
from Crypto.Random import get_random_bytes
import json
import hashlib
import sys

def xorencode(filename):
    try:
        file = open(filename, 'rb')
        content = file.read()
        h = hashlib.new('sha256')
        
        key = get_random_bytes(32)
        nonce_rfc7539 = get_random_bytes(12)
        cipher = ChaCha20.new(key=key, nonce=nonce_rfc7539)
        
        ciphertext = cipher.encrypt(content)
        h.update(ciphertext)
        h = h.hexdigest()
       # ciphertext = b64encode(ciphertext).decode('utf-8')
        nonce_rfc7539 = b64encode(cipher.nonce).decode('utf-8')
        key = b64encode(key).decode('utf-8')
        result = json.dumps({'nonce':nonce_rfc7539, 'key':key, 'filename':filename, 'hash':h})
    except:
        print("ERROR : an error has occured, maybe the file to encode does not exist, abort operation")
        sys.exit()
    return ciphertext, result

def xordecode(ciphertext, result):
    try:
        b64 = json.loads(result)
        nonce = b64decode(b64['nonce'])
        key = b64decode(b64['key'])
        filename = b64['filename']
        hashh = b64['hash']
        h = hashlib.new('sha256')
        h.update(ciphertext)
        h = h.hexdigest()
        if h == hashh:
            print("INFO : hash values identical the file has not been modified\n")
        elif h != hashh:
            print("ERROR : hash values are different, the file must have been modified, abort operation")
            sys.exit()
        cipher1 = ChaCha20.new(key=key, nonce=nonce)
        plaintext = cipher1.decrypt(ciphertext)
    except:
        print("ERROR : the key could not be correctly decoded, it must have been modified, ask your sender to send it again")
        sys.exit()
    return plaintext, filename

def ecies():
   try:
       privKey = generate_eth_key()
       privKeyHex = privKey.to_hex()
       pubKeyHex = privKey.public_key.to_hex()
       with open("privkey", "w") as f:
           f.write(privKeyHex)
       with open("pubkey", "w") as f:
           f.write(pubKeyHex)
   except: 
      print("ERROR : an error has occured during assymetric key creation, abort operation")
      sys.exit()

   return privKeyHex, pubKeyHex 

def encode(filename, pubKeyHex):
    content, key = xorencode(filename)
    key = key.encode()
    key = encrypt(pubKeyHex, key)
    with open("key", "wb") as f:
        f.write(key)
    with open("cipher", "wb") as f:
        f.write(content)
    return content, key
    
def decode(content, key, privkey):
    try: 
        key = decrypt(privkey, key)
    except:
        print("ERROR : the key could not be decrypted, maybe the private key or the public key have been modified")
        sys.exit()
    if content is None:
        print("ERROR : the file to decode is empty, maybe the given file is not the correct one, abort operation")
        sys.exit()
    plaintext, filename = xordecode(content, key)
    with open(filename, "wb") as binary_file:
            binary_file.write(plaintext)
    return plaintext, filename

def loadkey(filename):
    try:
        key = open(filename,"rb").read()
    except:
        print("ERROR : could not load assymetric key, maybe it does not exist, abort operation")
        sys.exit()
    return key

def loadprivkey(filename):
    try:
        key = open(filename,"r").read()
    except:
        print("ERROR : could not load private key, maybe it does not exist, abort operation")
        sys.exit()
    return key

def loadforeignpubkey(filename):
    try:
        key = open(filename,"r").read()
    except:
        print("ERROR : could not load public key, maybe it does not exist, abort operation")
        sys.exit()
    return key