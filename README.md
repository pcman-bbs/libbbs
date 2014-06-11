# libbbs

[![Build Status](https://travis-ci.org/pcman-bbs/libbbs.svg?branch=master)](https://travis-ci.org/pcman-bbs/libbbs)
[![Coverage Status](https://coveralls.io/repos/pcman-bbs/libbbs/badge.png?branch=master)](https://coveralls.io/r/pcman-bbs/libbbs?branch=master)

A telnet Bulletin Board System (BBS) helper library. This library provides the following features for BBS:
*   Unicode-at-on (UAO)
*   ASCII art

# Development

The project depends on the following libraries:
*   check (optional)
*   cmake
*   pkg-config
*   valgrind (optional)

You can use the standard cmake way to build the project:

```
cmake .
make
make test
```

# PPA

The daily build of libbbs can be found in the following PPA.

*   <https://launchpad.net/~pcman-bbs/+archive/libbbs-daily>

# Feature Request & Issue

Please report feature request and/or issue in <https://github.com/pcman-bbs/libbbs/issues>.

# License

*   This project is licensed under [LGPL-2.1](https://github.com/pcman-bbs/libbbs/blob/master/COPYING).
*   `data/uao` is provided by [moztw](http://moztw.org/docs/big5/), and they are licensed under [CC BY-SA 3.0 TW](http://creativecommons.org/licenses/by-sa/3.0/tw/).
*   `data/cp950` is provided by [moztw](http://moztw.org/docs/big5/), and they are licensed under [CC BY-SA 3.0 TW](http://creativecommons.org/licenses/by-sa/3.0/tw/).
