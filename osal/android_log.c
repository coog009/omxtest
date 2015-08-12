#include <utils/Log.h>
#include "osal_log.h"

void osal_log_with_level(OSALLogLevel log_level, char *ptag, char *msg, ...)
{
    va_list parg_list;
    va_start(parg_list, msg);

    switch (log_level) {
    case OSAL_LOG_WARNING:
        __android_log_vprint(ANDROID_LOG_WARNING, ptag, msg, parg_list);
        break;
    case OSAL_LOG_ERROR:
        __android_log_vprint(ANDROID_LOG_ERROR, ptag, msg, parg_list);
        break;
    case OSAL_LOG_DEBUG:
        __android_log_vprint(ANDROID_LOG_DEBUG, ptag, msg, parg_list);
        break;
    case OSAL_LOG_INFO:
    default:
        __android_log_vprint(ANDROID_LOG_INFO, ptag, msg, parg_list);
        break;
    }

    va_end(parg_list);
}
