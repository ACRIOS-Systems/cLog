# cLog

Library to easily print log messages based on severity. Severity can be changed dynamically and independently for piece of code.

This library was created thanks to cooperation between [ACRIOS Systems s.r.o.](https://acrios.com) and [AELER Technologies SA](https://www.aeler.com/).

## Configs

In `cLog_config.h` are defined configuration which can be set. Commenting config macro result in not using that feature. By default default print message is used. The default print message may be overwritten using macro `#define CLOG_PRINT_DETAILS_ID CLOG_PRINT_DETAILS_ID_USER`.

`cLog_print_details` function declaration depends on which features are uncommented. If `CLOG_PRINT_DETAILS_ID_USER` is set then definition of that function is on user

## Usage

User need create logger structure with logger name (scope of name has to be same as scope of logger) and init logger level. Then he needs pass address of this structure to appropriate log type message with message to print.

Log levels are defined using `CLogLevel_t` enum type in [cLog.h](cLog.h) file.

`CLogger_t` logger structure type.

`CLOG_SET_LOGNAME(logger, name)` -> changing logger name.
`CLOG_SET_LOGLEVEL(logger, level)` -> changing logger logging level.

`CLOG_CRITICAL(logger, msg)` -> track critical messages.
`CLOG_CRITICAL_LOG_ONLY(logger, msg)` -> track critical messages without details like time, logger name, file name, line number...
`CLOG_ERROR(logger, msg)` -> track error messages.
`CLOG_ERROR_LOG_ONLY(logger, msg)` -> track error messages without details like time, logger name, file name, line number...
`CLOG_WARNING(logger, msg)` -> track warning messages.
`CLOG_WARNING_LOG_ONLY(logger, msg)` -> track warning messages without details like time, logger name, file name, line number...
`CLOG_INFO(logger, msg)` -> track info messages.
`CLOG_INFO_LOG_ONLY(logger, msg)` -> track info messages without details like time, logger name, file name, line number...
`CLOG_DEBUG(logger, msg)` -> track debug messages.
`CLOG_DEBUG_LOG_ONLY(logger, msg)` -> track debug messages without details like time, logger name, file name, line number...
`CLOG_TRACE(logger, msg)` -> track trace messages.
`CLOG_TRACE_LOG_ONLY(logger, msg)` -> track trace messages without details like time, logger name, file name, line number...

## example

C source file may looks like this:

```C
#include "cLog.h"
static CLogger_t  s_loggerGlobal     = { .logName = "f", .logLevel = CLOG_VAL_DEBUG };
static CLogger_t *s_loggerGlobal_ptr = &s_loggerGlobal;

int f1(void)
{
    CLOG_TRACE(s_loggerGlobal_ptr, "F1\r\n") /* this is ignored as log level is set to CLOG_VAL_DEBUG */
    return 1;
}

int f2(void)
{
    CLOG_DEBUG(s_loggerGlobal_ptr, "F2\r\n")
    return 2;
}

int f3(void)
{
    CLOG_INFO_LOG_ONLY(s_loggerGlobal_ptr, "F3\r\n") /* print only message without details */
    return 4;
}

int main(void)
{
    int retval = 0;
    static CLogger_t  s_loggerMain     = { .logName = "mMain", .logLevel = CLOG_VAL_INFO };
    static CLogger_t *s_loggerMain_ptr = &s_loggerMain;

    CLOG_INFO(s_loggerMain_ptr,"Starting with f1\r\n")

    retval |= f1();

    CLOG_INFO(s_loggerMain_ptr,"Continuing with f2\r\n")

    retval |= f2();

    CLOG_SET_LOGLEVEL(s_loggerMain_ptr, CLOG_VAL_WARNING)

    CLOG_INFO(s_loggerMain_ptr,"Continuing with f3\r\n") /* this is ignored as log level was changed */

    retval |= f3();

    CLOG_WARNING(s_loggerMain_ptr,"You are at end of app wit retval: %d\r\n", retval)

    return retval;
}
```

## tips

Define `__FILENAME__` flag for compilator. In this case less memory and runtime code is used. For example CMakeList may be updated similarly to:
`set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -D__FILENAME__='\"$(notdir $(abspath $<))\"'")`