/*
 * Copyright  2019-2023 ACRIOS Systems
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CLOG_
#define _CLOG_

#include "cLog_config.h"
#include <stdarg.h>
#include <stdint.h>

/* Do not change code bellow */

#if defined(CLOG_PRINT_DETAILS_USE_FILENAME)
#    define CLOG_PRINT_DETAILS_FILENAME_TYPE , const char *fileName
#    define CLOG_PRINT_DETAILS_FILENAME      , fileName
#else
#    define CLOG_PRINT_DETAILS_FILENAME_TYPE
#    define CLOG_PRINT_DETAILS_FILENAME
#endif

#if defined(CLOG_PRINT_DETAILS_USE_LINENUMBER)
#    define CLOG_PRINT_DETAILS_LINENUMBER_TYPE , uint32_t lineNumber
#    define CLOG_PRINT_DETAILS_LINENUMBER      , lineNumber
#else
#    define CLOG_PRINT_DETAILS_LINENUMBER_TYPE
#    define CLOG_PRINT_DETAILS_LINENUMBER
#endif
#if defined(CLOG_PRINT_DETAILS_USE_FILENAME) && defined(CLOG_PRINT_DETAILS_USE_LINENUMBER)
#    define CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber, ...) \
        _cLog_print(logger, logLevel, fileName, lineNumber, __VA_ARGS__);

#elif defined(CLOG_PRINT_DETAILS_USE_FILENAME)
#    define CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber, ...) \
        _cLog_print(logger, logLevel, fileName, __VA_ARGS__);

#else
#    define CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber, ...) \
        _cLog_print(logger, logLevel, lineNumber, __VA_ARGS__);

#endif

#define CLOG_LOG(logger, logLevel, fileName, lineNumber, ...) \
    CLOG_PRINT_DETAILS(logger, logLevel, fileName, lineNumber, __VA_ARGS__);

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
    const char *logName;
    CLogLevel_t logLevel;
} CLogger_t;

extern const char *s_cLogLevelToString[CLOG_VAL_LEN];
extern const char *s_cLogLevelToColors[CLOG_VAL_LEN];

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

#define CLOG_CRITICAL(logger, ...) CLOG_LOG(logger, CLOG_VAL_CRITICAL, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__)

#define CLOG_CRITICAL_LOG_ONLY(logger, ...) _cLog_print_pure(logger, CLOG_VAL_CRITICAL, __VA_ARGS__);

#define CLOG_ERROR(logger, ...) CLOG_LOG(logger, CLOG_VAL_ERROR, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__)

#define CLOG_ERROR_LOG_ONLY(logger, ...) _cLog_print_pure(logger, CLOG_VAL_ERROR, __VA_ARGS__);

#define CLOG_WARNING(logger, ...) CLOG_LOG(logger, CLOG_VAL_WARNING, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__)

#define CLOG_WARNING_LOG_ONLY(logger, ...) _cLog_print_pure(logger, CLOG_VAL_WARNING, __VA_ARGS__);

#define CLOG_INFO(logger, ...) CLOG_LOG(logger, CLOG_VAL_INFO, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__)

#define CLOG_INFO_LOG_ONLY(logger, ...) _cLog_print_pure(logger, CLOG_VAL_INFO, __VA_ARGS__);

#define CLOG_DEBUG(logger, ...) CLOG_LOG(logger, CLOG_VAL_DEBUG, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__)

#define CLOG_DEBUG_LOG_ONLY(logger, ...) _cLog_print_pure(logger, CLOG_VAL_DEBUG, __VA_ARGS__);

#define CLOG_TRACE(logger, ...) CLOG_LOG(logger, CLOG_VAL_TRACE, __CUSTOM_FILENAME__, __LINE__, __VA_ARGS__)

#define CLOG_TRACE_LOG_ONLY(logger, ...) _cLog_print_pure(logger, CLOG_VAL_TRACE, __VA_ARGS__);

/* clog calls*/
void _cLog_print(const CLogger_t                                      *logger,
                 CLogLevel_t logLevel CLOG_PRINT_DETAILS_FILENAME_TYPE CLOG_PRINT_DETAILS_LINENUMBER_TYPE,
                 const char                                           *msg,
                 ...);

void _cLog_print_pure(const CLogger_t *logger, CLogLevel_t logLevel, const char *msg, ...);


/* user defined clog calls */
void cLog_print(const CLogger_t                                   *logger,
                const char                                        *colour,
                const char *level CLOG_PRINT_DETAILS_FILENAME_TYPE CLOG_PRINT_DETAILS_LINENUMBER_TYPE,
                const char                                        *msg,
                va_list                                            ap);

void cLog_print_pure(const char *msg, va_list ap);

#endif /* _CLOG_ */
