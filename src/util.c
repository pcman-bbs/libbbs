/*
 *  Copyright (C) 2014 ChangZhuo Chen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "util.h"

void null_logger(void *data, int level, const char *fmt, ...)
{
}

int get_utf8_length_by_first_byte(char first_byte)
{
    if ((first_byte & 0x80) == 0x00) {
        return 1;
    }

    if ((first_byte & 0xe0) == 0xc0) {
        return 2;
    }

    if ((first_byte & 0xf0) == 0xe0) {
        return 3;
    }

    if ((first_byte & 0xf8) == 0xf0) {
        return 4;
    }

    if ((first_byte & 0xfb) == 0xf8) {
        return 5;
    }

    if ((first_byte & 0xfe) == 0xfb) {
        return 6;
    }

    return 0;
}
