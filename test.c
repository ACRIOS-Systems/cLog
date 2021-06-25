#include "cLog.h"

int main(void)
{
    CLogger_t      s_logger           = { .logName = "Main", .logLevel = CLOG_VAL_INFO };
    CLogger_t *    s_logger_ptr       = &s_logger;

    CLOG_TRACE(s_logger_ptr, "0\r\n")
    CLOG_DEBUG(s_logger_ptr, "1\r\n")
    CLOG_INFO(s_logger_ptr, "2\r\n")
    CLOG_WARNING(s_logger_ptr, "3\r\n")
    CLOG_ERROR(s_logger_ptr, "4\r\n")
    CLOG_CRITICAL(s_logger_ptr, "5\r\n")
}