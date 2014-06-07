#!/usr/bin/env python3
import os

CP950  = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', 'data', 'cp950', 'cp950-b2u.txt')
UAO241 = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', 'data', 'uao', 'uao241-b2u.txt')
UAO250 = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', 'data', 'uao', 'uao250-b2u.txt')

def main():
    b2u_common = {}
    b2u_uao241 = {}
    b2u_uao250 = {}

    with open(CP950) as f:
        for l in f:
            if l.startswith('#'):
                continue
            l = l.strip(' ')
            (big5, unicode_) = map(lambda x: int(x, 0), l.split(' '))

            b2u_common[big5] = unicode_

    with open(UAO241) as f:
        for l in f:
            if l.startswith('#'):
                continue
            l = l.strip(' ')
            (big5, unicode_) = map(lambda x: int(x, 0), l.split(' '))

            b2u_uao241[big5] = unicode_

    with open(UAO250) as f:
        for l in f:
            if l.startswith('#'):
                continue
            l = l.strip(' ')
            (big5, unicode_) = map(lambda x: int(x, 0), l.split(' '))

            if big5 in b2u_uao241 and b2u_uao241[big5] == unicode_:
                b2u_common[big5] = unicode_
                del b2u_uao241[big5]
            else:
                b2u_uao250[big5] = unicode_

if __name__ == '__main__':
    main()
