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
#include "bbs-private.h"
#include "uao_table.h"
#include "util.h"

int bbs_big5_to_utf8(struct BBSContext *ctx, const char *big5, char *utf8, size_t utf8_len)
{
    if (!ctx) {
        return BBS_ERROR;
    }

    LOG_VERBOSE("API call: " __FUNC__);

    return 0; // FIXME: shall return length of output buffer
}

int bbs_utf8_to_big5(struct BBSContext *ctx, const char *utf8, char *big5, size_t big5_len)
{
    if (!ctx) {
        return BBS_ERROR;
    }

    LOG_VERBOSE("API call: " __FUNC__);

    return 0; // FIXME: shall return length of output buffer
}
