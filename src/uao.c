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
#include <string.h>

#include <stdio.h>

#include "bbs-private.h"
#include "uao_table.h"
#include "util.h"

#define UPDATE_OUTPUT(len, output_ptr, output_len, input_ptr, input_len) \
    do { \
        if (output_len >= input_len) { \
            memcpy(output_ptr, input_ptr, input_len); \
            output_len -= input_len; \
            output_ptr += input_len; \
        } \
        len += input_len; \
    } while (0)

int bbs_big5_to_utf8(struct BBSContext *ctx, const char *big5, char *utf8, size_t utf8_len)
{
    if (!ctx) {
        return BBS_ERROR;
    }

    LOG_VERBOSE("API call: " __FUNC__);

    if (!utf8) {
        utf8_len = 0;
    }

    int len = 0;

    while(big5[0] != 0) {
        if (!(big5[0] & 0x80)) {
            // ASCII
            UPDATE_OUTPUT(len, utf8, utf8_len, big5, 1);
            ++big5;
            continue;
        }

        // FIXME: convert big5 into utf8
    }

    return len;
}

int bbs_utf8_to_big5(struct BBSContext *ctx, const char *utf8, char *big5, size_t big5_len)
{
    if (!ctx) {
        return BBS_ERROR;
    }

    LOG_VERBOSE("API call: " __FUNC__);

    if (!big5) {
        big5_len = 0;
    }

    int len = 0;

    while(utf8[0] != 0) {
        if (!(utf8[0] & 0x80)) {
            // ASCII
            UPDATE_OUTPUT(len, big5, big5_len, utf8, 1);
            ++utf8;
            continue;
        }

        // FIXME: convert big5 into utf8
    }

    return len;
}
