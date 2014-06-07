#!/usr/bin/env python3
import codecs
import os

PROJECT_BASE = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')
PROJECT_DATA = os.path.join(PROJECT_BASE, 'data')
PROJECT_SRC  = os.path.join(PROJECT_BASE, 'src')

CP950  = os.path.join(PROJECT_DATA, 'cp950', 'cp950-b2u.txt')
UAO241 = os.path.join(PROJECT_DATA, 'uao', 'uao241-b2u.txt')
UAO250 = os.path.join(PROJECT_DATA, 'uao', 'uao250-b2u.txt')

OUTPUT_HEADER = os.path.join(PROJECT_SRC, 'uao_table.h')
OUTPUT_SOURCE = os.path.join(PROJECT_SRC, 'uao_table.c')

def to_utf8_string(unicode_):
    return codecs.encode(chr(unicode_), 'UTF-8')

def to_big5_string(big5):
    if big5 // 0x100:
        return bytes([big5 // 0x100, big5 % 0x100])
    return bytes([big5])

def main():
    b2u_common = {}
    b2u_uao241 = {}
    b2u_uao250 = {}

    with open(CP950) as f:
        for l in f:
            if l.startswith('#'):
                continue
            (big5, unicode_) = map(lambda x: int(x, 0), l.split(' '))

            big5 = to_big5_string(big5)
            utf8 = to_utf8_string(unicode_)

            b2u_common[big5] = utf8

    with open(UAO241) as f:
        for l in f:
            if l.startswith('#'):
                continue
            (big5, unicode_) = map(lambda x: int(x, 0), l.split(' '))

            big5 = to_big5_string(big5)
            utf8 = to_utf8_string(unicode_)

            b2u_uao241[big5] = utf8

    with open(UAO250) as f:
        for l in f:
            if l.startswith('#'):
                continue
            (big5, unicode_) = map(lambda x: int(x, 0), l.split(' '))

            big5 = to_big5_string(big5)
            utf8 = to_utf8_string(unicode_)

            if big5 in b2u_uao241 and b2u_uao241[big5] == utf8:
                b2u_common[big5] = utf8
                del b2u_uao241[big5]
            else:
                b2u_uao250[big5] = utf8

if __name__ == '__main__':
    main()
