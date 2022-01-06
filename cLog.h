/*
 * Copyright  2019 ACRIOS Systems
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CLOG_
#define _CLOG_

#include "cLog_config.h"
#include <stdint.h>

/* Do not change code bellow */

#if defined(CLOG_PRINT_DETAILS_ID)
#    if defined(CLOG_PRINT_DETAILS_USE_FILENAME)
#        define CLOG_PRINT_DETAILS_FILENAME_TYPE , const char *fileName
#    else
#        define CLOG_PRINT_DETAILS_FILENAME_TYPE
#    endif

#    if defined(CLOG_PRINT_DETAILS_USE_LINENUMBER)
#        define CLOG_PRINT_DETAILS_LINENUMBER_TYPE , uint32_t lineNumber
#    else
#        define CLOG_PRINT_DETAILS_LINENUMBER_TYPE
#    endif
#    if defined(CLOG_PRINT_DETAILS_USE_FILENAME) && defined(CLOG_PRINT_DETAILS_USE_LINENUMBER)
#        define CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber) \
            cLog_print_details(logger, logLevel, fileName, lineNumber)

#    elif defined(CLOG_PRINT_DETAILS_USE_FILENAME)
#        define CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber) \
            cLog_print_details(logger, logLevel, fileName)

#    else
#        define CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber) \
            cLog_print_details(logger, logLevel, lineNumber)

#    endif

#else
#    define CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber)
#endif

#if CLOG_PRINT_FUNC_ID == CLOG_PRINT_FUNC_ID_STDLIB
#    define CLOG_PRINT_FUNC(...) (void)printf(__VA_ARGS__)
#    include <stdio.h>
#elif CLOG_PRINT_FUNC_ID == CLOG_PRINT_FUNC_ID_NXP
#    define CLOG_PRINT_FUNC(...) (void)PRINTF(__VA_ARGS__)
#    include <fsl_debug_console.h>
#else
#    define CLOG_PRINT_FUNC(...)
#endif

#define CLOG_LOG(logger, logLevel, fileName, lineNumber, ...)   \
    CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber); \
    CLOG_PRINT_FUNC(__VA_ARGS__);

/* cLog declarations bellow */
typedef enum
{
    CLOG_VAL_NONE     = 0,
    CLOG_VAL_CRITICAL = 1,
    CLOG_VAL_ERROR    = 2,
    CLOG_VAL_WARNING  = 3,
    CLOG_VAL_INFO     = 4,
    CLOG_VAL_DEBUG    = 5,
    CLOG_VAL_TRACE    = 6,
    CLOG_VAL_LEN
} CLogLevel_t;

typedef struct
{
    char *      logName;
    CLogLevel_t logLevel;
} CLogger_t;

extern char *s_cLogLevelToString[CLOG_VAL_LEN];
extern char *s_cLogLevelToColors[CLOG_VAL_LEN];

#define CLOG_SET_LOGNAME(logger, name)   (logger)->logName = (name);
#define CLOG_SET_LOGLEVEL(logger, level) (logger)->logLevel = (level);

#ifdef __FILENAME__
#    define __CUSTOM_FILENAME__ __FILENAME__
#elif defined(__FILE_NAME__)
#    define __CUSTOM_FILENAME__ __FILE_NAME__
#elif defined(__BASE_FILE__)
#    define __CUSTOM_FILENAME__ __BASE_FILE__
#else
#    define __CUSTOM_FILENAME__ __FILE__
#endif

#define CLOG_CRITICAL(logger, ...)                                                      \
    if (logger->logLevel >= CLOG_VAL_CRITICAL)                                          \
    {                                                                                   \
        CLOG_LOG(logger, CLOG_VAL_CRITICAL, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__) \
    }

#define CLOG_CRITICAL_LOG_ONLY(logger, ...)    \
    if (logger->logLevel >= CLOG_VAL_CRITICAL) \
    {                                          \
        CLOG_PRINT_FUNC(__VA_ARGS__);          \
    }

#define CLOG_ERROR(logger, ...)                                                      \
    if (logger->logLevel >= CLOG_VAL_ERROR)                                          \
    {                                                                                \
        CLOG_LOG(logger, CLOG_VAL_ERROR, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__) \
    }

#define CLOG_ERROR_LOG_ONLY(logger, ...)    \
    if (logger->logLevel >= CLOG_VAL_ERROR) \
    {                                       \
        CLOG_PRINT_FUNC(__VA_ARGS__);       \
    }

#define CLOG_WARNING(logger, ...)                                                      \
    if (logger->logLevel >= CLOG_VAL_WARNING)                                          \
    {                                                                                  \
        CLOG_LOG(logger, CLOG_VAL_WARNING, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__) \
    }

#define CLOG_WARNING_LOG_ONLY(logger, ...)    \
    if (logger->logLevel >= CLOG_VAL_WARNING) \
    {                                         \
        CLOG_PRINT_FUNC(__VA_ARGS__);         \
    }

#define CLOG_INFO(logger, ...)                                                      \
    if (logger->logLevel >= CLOG_VAL_INFO)                                          \
    {                                                                               \
        CLOG_LOG(logger, CLOG_VAL_INFO, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__) \
    }

#define CLOG_INFO_LOG_ONLY(logger, ...)    \
    if (logger->logLevel >= CLOG_VAL_INFO) \
    {                                      \
        CLOG_PRINT_FUNC(__VA_ARGS__);      \
    }

#define CLOG_DEBUG(logger, ...)                                                      \
    if (logger->logLevel >= CLOG_VAL_DEBUG)                                          \
    {                                                                                \
        CLOG_LOG(logger, CLOG_VAL_DEBUG, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__) \
    }

#define CLOG_DEBUG_LOG_ONLY(logger, ...)    \
    if (logger->logLevel >= CLOG_VAL_DEBUG) \
    {                                       \
        CLOG_PRINT_FUNC(__VA_ARGS__);       \
    }

#define CLOG_TRACE(logger, ...)                                                      \
    if (logger->logLevel >= CLOG_VAL_TRACE)                                          \
    {                                                                                \
        CLOG_LOG(logger, CLOG_VAL_TRACE, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__) \
    }

#define CLOG_TRACE_LOG_ONLY(logger, ...)    \
    if (logger->logLevel >= CLOG_VAL_TRACE) \
    {                                       \
        CLOG_PRINT_FUNC(__VA_ARGS__);       \
    }

#if defined(CLOG_PRINT_DETAILS_ID)
void cLog_print_details(const CLogger_t *                                     logger,
                        CLogLevel_t logLevel CLOG_PRINT_DETAILS_FILENAME_TYPE CLOG_PRINT_DETAILS_LINENUMBER_TYPE);
#endif

#endif /* _CLOG_ */
