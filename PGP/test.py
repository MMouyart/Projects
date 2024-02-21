#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jan  2 09:56:39 2023

@author: user
"""
from functions import *
import sys, getopt

def main(argv):
    filename = 'Réunion-avec-David-VIGILANT.docx'
    privkey, pubkey = ecies()
    content, key = encode(filename, loadforeignpubkey("pubkey"))
    plaintext, f = decode(content, loadkey("key"), loadprivkey("privkey"))
    f = "test" + f
    
            
if __name__=='__main__':
    main(sys.argv[1:])