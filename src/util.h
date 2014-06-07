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

#define LOG_VERBOSE(fmt, ...) \
    do { ctx->logger(ctx->logger_data, BBS_LOG_LEVEL_VERBOSE, "[%s:%d]" #fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define LOG_DEBUG(fmt, ...) \
    do { ctx->logger(ctx->logger_data, BBS_LOG_LEVEL_DEBUG, "[%s:%d]" #fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define LOG_INFO(fmt, ...) \
    do { ctx->logger(ctx->logger_data, BBS_LOG_LEVEL_INFO, "[%s:%d]" #fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define LOG_WARN(fmt, ...) \
    do { ctx->logger(ctx->logger_data, BBS_LOG_LEVEL_WARN, "[%s:%d]" #fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define LOG_ERROR(fmt, ...) \
    do { ctx->logger(ctx->logger_data, BBS_LOG_LEVEL_ERROR, "[%s:%d]" #fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)

void null_logger(void *data, int level, const char *fmt, ...);
