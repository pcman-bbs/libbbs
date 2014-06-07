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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bbs-private.h"
#include "uao_table.h"
#include "util.h"

struct Config {
    struct Big5_UTF8_Table *table;
    size_t table_len;
    int (*compare)(const void *a, const void *b);
    int (*copy_input)(const char *input, char input_buf[static 5]);
    const char *(*get_output)(const struct Big5_UTF8_Table *table);
};

const char UNKNOWN_CHAR[] = "?";

static int big5_to_utf8_compare(const void *x, const void *y)
{
    return strcmp(
        (char *) x,
        ((struct Big5_UTF8_Table *)y)->big5);
}

static int big5_to_utf8_copy_input(const char *input, char input_buf[static 3])
{
    assert(input);

    if (input[0] & 0x80) {
        if (input[1]) {
            memcpy(input_buf, input, 2);
            input_buf[2] = 0;
            return 2;
        } else {
            // Broken big5.
            input_buf[0] = UNKNOWN_CHAR[0];
            input_buf[1] = 0;
            return 1;
        }
    }

    input_buf[0] = input[0];
    input_buf[1] = 0;
    return 1;
}

static const char* big5_to_utf8_get_output(const struct Big5_UTF8_Table *table)
{
    return table->utf8;
}

const struct Config BIG5_TO_UTF8_CONFIG = {
    BIG5_TO_UTF8_TABLE,
    ARRAY_SIZE(BIG5_TO_UTF8_TABLE),
    big5_to_utf8_compare,
    big5_to_utf8_copy_input,
    big5_to_utf8_get_output,
};

static int utf8_to_big5_compare(const void *x, const void *y)
{
    return strcmp(
        (char *) x,
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

static const char* utf8_to_big5_get_output(const struct Big5_UTF8_Table *table)
{
    return table->big5;
}

const struct Config UTF8_TO_BIG5_CONFIG = {
    UTF8_TO_BIG5_TABLE,
    ARRAY_SIZE(UTF8_TO_BIG5_TABLE),
    utf8_to_big5_compare,
    utf8_to_big5_copy_input,
    utf8_to_big5_get_output,
};

#define UPDATE_OUTPUT(output, output_len, input) \
    do { \
        int len = strlen(input); \
        if (output_len > len) { \
            memcpy(output, input, len); \
            output_len -= len; \
            output += len; \
        } else if (output_len > 0) { \
            output[0] = 0; \
            output_len = 0; \
        } \
        final_len += len; \
    } while (0)

static int convert(const struct Config *config, const char *input, char *output, size_t output_len)
{
    assert(config);
    assert(input);

    if (!output) {
        output_len = 0;
    }

    int final_len = 0;
    char buf[5];

    while (input[0]) {
        int input_len = config->copy_input(input, buf);

        if (input_len == 1) {
            // ASCII
            UPDATE_OUTPUT(output, output_len, buf);
        } else {
            struct Big5_UTF8_Table *res = bsearch(buf, config->table, config->table_len, sizeof(config->table[0]), config->compare);

            if (res) {
                UPDATE_OUTPUT(output, output_len, config->get_output(res));
            } else {
                UPDATE_OUTPUT(output, output_len, UNKNOWN_CHAR);
            }
        }

        if (output_len > 0) {
            output[0] = 0;
        }

        input += input_len;
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
