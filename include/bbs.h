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
#pragma once

#include <string.h>

struct BBSContext;

enum {
    BBS_LOG_LEVEL_VERBOSE  = 1,
    BBS_LOG_LEVEL_DEBUG    = 2,
    BBS_LOG_LEVEL_INFO     = 3,
    BBS_LOG_LEVEL_WARN     = 4,
    BBS_LOG_LEVEL_ERROR    = 5,
};

enum {
    BBS_ERROR = -1,
};

typedef void (*BBSLogger)(void *data, int level, const char *fmt, ...);

struct BBSContext *bbs_new(BBSLogger logger, void *logger_data);
void bbs_delete(struct BBSContext **ctx);

int bbs_big5_to_utf8(const char *big5, char *utf8, size_t utf8_len);
int bbs_utf8_to_big5(const char *utf8, char *big5, size_t big5_len);
