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
#include <assert.h>
#include <string.h>

#include <stdio.h>

#include "bbs-private.h"
#include "uao_table.h"
#include "util.h"

struct Config {
    struct Big5_UTF8_Table *table;
    size_t table_len;
    int (*compare)(void *a, void *b);
    int (*copy_input)(const char *input, char input_buf[static 5]);
    int (*get_output)(const struct Big5_UTF8_Table *table, char *output, size_t output_len);
};

static int big5_to_utf8_compare(void *x, void *y)
{
    return strcmp(
        ((struct Big5_UTF8_Table *)x)->big5,
        ((struct Big5_UTF8_Table *)y)->big5);
}

static int big5_to_utf8_copy_input(const char *input, char input_buf[static 3])
{
    assert(input);

    if ((input[0] & 0x80) && input[1]) {
        memcpy(input_buf, input, 2);
        input_buf[2] = 0;
        return 2;
    }

    // FIXME: How to handle first byte >= 0x80 but second byte is 0x00?

    input_buf[0] = input[0];
    input_buf[1] = 0;
    return 1;
}

static int big5_to_utf8_get_output(const struct Big5_UTF8_Table *table, char *output, size_t output_len)
{
    strncpy(output, output_len, table->utf8);
    return strlen(table->utf8);
}

const struct Config BIG5_TO_UTF8_CONFIG = {
    BIG5_TO_UTF8_COMMON,
    ARRAY_SIZE(BIG5_TO_UTF8_COMMON),
    big5_to_utf8_compare,
    big5_to_utf8_copy_input,
    big5_to_utf8_get_output,
};

static int utf8_to_big5_compare(void *x, void *y)
{
    return strcmp(
        ((struct Big5_UTF8_Table *)x)->utf8,
        ((struct Big5_UTF8_Table *)y)->utf8);
}

static int utf8_to_big5_copy_input(const char *input, char input_buf[static 3])
{
    assert(input);

    if (input[0] & 0x80) {
        // FIXME: copy single UTF8 character
        // FIXME: How to handle UTF8 encode error?
        return 0;
    }

    input_buf[0] = input[0];
    input_buf[1] = 0;
    return 1;
}

static int utf8_to_big5_get_output(const struct Big5_UTF8_Table *table, char *output, size_t output_len)
{
    strncpy(output, output_len, table->big5);
    return strlen(table->big5);
}

const struct Config UTF8_TO_BIG5_CONFIG = {
    UTF8_TO_BIG5_COMMON,
    ARRAY_SIZE(UTF8_TO_BIG5_COMMON),
    utf8_to_big5_compare,
    utf8_to_big5_copy_input,
    utf8_to_big5_get_output,
};

static int convert(const struct Config *config, const char *input, char *output, size_t output_len)
{
    assert(config);
    assert(input);

    if (!output) {
        output_len = 0;
    }

    int final_len = 0;
    char input_buf[5];

    while (input[0]) {
        int len = config->copy_input(input, input_buf);

        if (len == 1) {
            // ASCII

            if (output_len > len) {
                strncpy(output, input_buf, output_len);
                output += len;
                output_len -= len;
            } else {
                output_len = 0;
            }

        } else {
            // FIXME: convert input_buf
        }

        input += len;
        final_len += len;
    }

    return final_len;
}

int bbs_big5_to_utf8(struct BBSContext *ctx, const char *big5, char *utf8, size_t utf8_len)
{
    if (!ctx) {
        return BBS_ERROR;
    }

    LOG_VERBOSE("API call: " __FUNC__);

    return convert(&BIG5_TO_UTF8_CONFIG, big5, utf8, utf8_len);
}

int bbs_utf8_to_big5(struct BBSContext *ctx, const char *utf8, char *big5, size_t big5_len)
{
    if (!ctx) {
        return BBS_ERROR;
    }

    LOG_VERBOSE("API call: " __FUNC__);

    return convert(&UTF8_TO_BIG5_CONFIG, utf8, big5, big5_len);
}
