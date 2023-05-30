/*
 * Copyright  2019-2023 ACRIOS Systems
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "cLog.h"
#include <stdio.h>

const char *s_cLogLevelToString[CLOG_VAL_LEN] = { CLOG_STR_NONE,       CLOG_STRING_CRITICAL, CLOG_STRING_ERROR,
                                                  CLOG_STRING_WARNING, CLOG_STRING_INFO,     CLOG_STRING_DEBUG,
                                                  CLOG_STRING_TRACE };
const char *s_cLogLevelToColors[CLOG_VAL_LEN] = { CLOG_COLOR_DEFAULT, CLOG_COLOR_CRITICAL, CLOG_COLOR_ERROR,
                                                  CLOG_COLOR_WARNING, CLOG_COLOR_INFO,     CLOG_COLOR_DEBUG,
                                                  CLOG_COLOR_TRACE };

void _cLog_print(const CLogger_t                                      *logger,
                 CLogLevel_t logLevel CLOG_PRINT_DETAILS_FILENAME_TYPE CLOG_PRINT_DETAILS_LINENUMBER_TYPE,
                 const char                                           *msg,
                 ...)
{
    if (logger->logLevel >= logLevel)
    {
        va_list ap;
        va_start(ap, msg);
        cLog_print(logger, s_cLogLevelToColors[logLevel],
                   s_cLogLevelToString[logLevel] CLOG_PRINT_DETAILS_FILENAME CLOG_PRINT_DETAILS_LINENUMBER, msg, ap);
        va_end(ap);
    }
}

void _cLog_print_pure(const CLogger_t *logger, CLogLevel_t logLevel, const char *msg, ...)
{
    if (logger->logLevel >= logLevel)
    {
        va_list ap;
        va_start(ap, msg);
        cLog_print_pure(msg, ap);
        va_end(ap);
    }
}

#ifdef CLOG_PRINT_DETAILS_ID
#    if CLOG_PRINT_DETAILS_ID == CLOG_PRINT_DETAILS_ID_DEFAULT
#        include <time.h>

void cLog_print(const CLogger_t *logger,
                const char      *colour,
                const char      *level,
                const char      *fileName,
                uint32_t         lineNumber,
                const char      *msg,
                va_list          ap)
{
    time_t     timer;
    struct tm *tm_info;
    time(&timer);
    tm_info = localtime(&timer);
#        ifdef CLOG_PRINT_DETAILS_FILENAME_TYPE
#        endif
#        if defined(CLOG_PRINT_DETAILS_FILENAME_TYPE) && defined(CLOG_PRINT_DETAILS_LINENUMBER_TYPE)
    printf("\r\n%04d.%02d.%02d %02d:%02d:%02d>%s%s%s>%s>%s>%d:", (1900 + tm_info->tm_year), (tm_info->tm_mon + 1),
           tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, colour, level,
           s_cLogLevelToColors[CLOG_VAL_NONE], logger->logName, fileName, lineNumber);
#        elif defined(CLOG_PRINT_DETAILS_FILENAME_TYPE)
    printf("\r\n%04d.%02d.%02d %02d:%02d:%02d>%s%s%s>%s>%s:", (1900 + tm_info->tm_year), (tm_info->tm_mon + 1),
           tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, colour, level,
           s_cLogLevelToColors[CLOG_VAL_NONE], logger->logName, fileName);
#        else
    printf("\r\n%04d.%02d.%02d %02d:%02d:%02d>%s%s%s>%s>%d:", (1900 + tm_info->tm_year), (tm_info->tm_mon + 1),
           tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, colour, level,
           s_cLogLevelToColors[CLOG_VAL_NONE], logger->logName, lineNumber);
#        endif
    cLog_print_pure(msg, ap);
}

void cLog_print_pure(const char *msg, va_list ap)
{
    vprintf(msg, ap);
}
#    endif
#endif
