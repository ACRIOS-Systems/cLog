/*
 * Copyright  2019 ACRIOS Systems
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "cLog.h"

const char *s_cLogLevelToString[CLOG_VAL_LEN] = { CLOG_STR_NONE,       CLOG_STRING_CRITICAL, CLOG_STRING_ERROR,
                                            CLOG_STRING_WARNING, CLOG_STRING_INFO,     CLOG_STRING_DEBUG,
                                            CLOG_STRING_TRACE };
const char *s_cLogLevelToColors[CLOG_VAL_LEN] = { CLOG_COLOR_DEFAULT, CLOG_COLOR_CRITICAL, CLOG_COLOR_ERROR,
                                            CLOG_COLOR_WARNING, CLOG_COLOR_INFO,     CLOG_COLOR_DEBUG,
                                            CLOG_COLOR_TRACE };

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
#        ifdef CLOG_PRINT_DETAILS_FILENAME_TYPE
    const char *fName = NULL;

#ifdef __FILENAME__
    fName = fileName;
#else
    if (fName == NULL)
    {
        fName = fileName;
    }
    else
    {
        fName = &(fName[1]);
    }
#endif
#        endif
#        if defined(CLOG_PRINT_DETAILS_FILENAME_TYPE) && defined(CLOG_PRINT_DETAILS_LINENUMBER_TYPE)
    CLOG_PRINT_FUNC("%04d.%02d.%02d %02d:%02d:%02d>%s%s%s>%s>%s>%d:", 1900+tm_info->tm_year, tm_info->tm_mon, tm_info->tm_mday,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, s_cLogLevelToColors[logLevel], s_cLogLevelToString[logLevel], s_cLogLevelToColors[CLOG_VAL_NONE],
                    logger->logName, fName, lineNumber);
#        elif defined(CLOG_PRINT_DETAILS_FILENAME_TYPE)
    CLOG_PRINT_FUNC("%04d.%02d.%02d %02d:%02d:%02d>%s%s%s>%s>%s:", 1900+tm_info->tm_year, tm_info->tm_mon, tm_info->tm_mday,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, s_cLogLevelToColors[logLevel], s_cLogLevelToString[logLevel], s_cLogLevelToColors[CLOG_VAL_NONE],
                    logger->logName, fName);
#        else
    CLOG_PRINT_FUNC("%04d.%02d.%02d %02d:%02d:%02d>%s%s%s>%s>%d:", 1900+tm_info->tm_year, tm_info->tm_mon, tm_info->tm_mday,
                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, s_cLogLevelToColors[logLevel], s_cLogLevelToString[logLevel], s_cLogLevelToColors[CLOG_VAL_NONE], logger->logName,
                    lineNumber);
#        endif
}
#    endif
#endif
