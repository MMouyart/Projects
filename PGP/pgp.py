#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan  3 13:21:41 2023

@author: user
"""
from functions import *
import argparse
import sys

def encoding(args):
     try:
         print("\nencoding '",args.f,"' with pubkey '",args.p,"'\n")
         encode(args.f, loadforeignpubkey(args.p))
         print("encoded file is named 'cipher' you can check its content by typing in the terminal :",
               "\ncat cipher")
     except:
         sys.exit()
 
def create(args):
     try:
         privkey, pubkey = ecies()
         print('\ncreated assymetric keys \n', 
               'Private key named "privkey"\n',
                '\n\nPublic key named "pubkey"\n')
         print('\n\n You can check both key values by typing in the terminal :\n',
               'cat privkey\n',
               'cat pubkey\n')
     except:
         sys.exit()
     

def decoding(args):
    print("decoding file",args.f,"with private key",args.p,"and assymetric key",args.x,"\n\n")
    try:
        content = open(args.f, "rb").read()
    except:
        print("ERROR : the file to decode is empty, maybe the given file is not the correct one, abort operation")
        sys.exit()
    try:
        plaintext, filename = decode(content, loadkey(args.x), loadprivkey(args.p))
        print("creating file '",filename,"' you can open it to verify its content")
    except:
        sys.exit()

parser = argparse.ArgumentParser()
subparsers = parser.add_subparsers(help='sub-command help')
#Add subcommand add

parser_a = subparsers.add_parser('encode', help='encode a file using a public key')
parser_a.add_argument('-p', type=str, help='public key')
parser_a.add_argument('-f', type=str, help='file to be encoded')
 #Set default function
parser_a.set_defaults(func=encoding)

 #Add subcommand sub
parser_s = subparsers.add_parser('create', help='Create two assymetric keys')
 #Set default function
parser_s.set_defaults(func=create)

#Add subcommand add

parser_a = subparsers.add_parser('decode', help='decoding a file using symmetric key and private key')
parser_a.add_argument('-p', type=str, help='private key')
parser_a.add_argument('-x', type=str, help='assymetric key')
parser_a.add_argument('-f', type=str, help='file to be decoded')
 #Set default function
parser_a.set_defaults(func=decoding)

args = parser.parse_args()
 #Executive function
args.func(args)