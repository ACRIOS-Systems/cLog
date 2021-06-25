/*
 * Copyright  2019 ACRIOS Systems
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "cLog.h"

char *s_cLogLevelToString[CLOG_VAL_LEN] = { "NONE", "CRITICAL", "ERROR", "WARNING", "INFO", "DEBUG", "TRACE" };

#ifdef CLOG_PRINT_DETAILS_ID
#    if CLOG_PRINT_DETAILS_ID == CLOG_PRINT_DETAILS_ID_DEFAULT
#        include <time.h>

void cLog_print_details(const CLogger_t *                                     logger,
                        CLogLevel_t logLevel CLOG_PRINT_DETAILS_FILENAME_TYPE CLOG_PRINT_DETAILS_LINENUMBER_TYPE)
{
    time_t     timer;
    struct tm *tm_info;
    time(&timer);
    tm_info = localtime(&timer);
#        if defined(CLOG_PRINT_DETAILS_FILENAME_TYPE) and defined(CLOG_PRINT_DETAILS_LINENUMBER_TYPE)
    CLOG_PRINT_FUNC("%04d.%02d.%02d  %02d:%02d:%02d>%s>%s>%s>%d:", tm_info->tm_year, tm_info->tm_mon, tm_info->tm_mday,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, s_cLogLevelToString[logLevel], fileName,
                    logger->logName, lineNumber);
#        elif defined(CLOG_PRINT_DETAILS_FILENAME_TYPE)
    CLOG_PRINT_FUNC("%04d.%02d.%02d  %02d:%02d:%02d>%s>%s>%s:", tm_info->tm_year, tm_info->tm_mon, tm_info->tm_mday,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, s_cLogLevelToString[logLevel], fileName,
                    logger->logName);
#        else
    CLOG_PRINT_FUNC("%04d.%02d.%02d  %02d:%02d:%02d>%s>%s>%d:", tm_info->tm_year, tm_info->tm_mon, tm_info->tm_mday,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, s_cLogLevelToString[logLevel], logger->logName,
                    lineNumber);
#        endif
}
#    endif
#endif