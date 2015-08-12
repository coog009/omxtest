#ifndef __OSAL_LOG_H__
#define __OSAL_LOG_H__

#define ROCKCHIP_LOG_TAG "osal default tag"

#define osal_log_info(...)      osal_log_with_level(OSAL_LOG_INFO, ROCKCHIP_LOG_TAG, __VA_ARGS__)
#define osal_log_warn(...)      osal_log_with_level(OSAL_LOG_WARNING, ROCKCHIP_LOG_TAG, __VA_ARGS__)
#define osal_log_error(...)     osal_log_with_level(OSAL_LOG_ERROR, ROCKCHIP_LOG_TAG, __VA_ARGS__)
#define osal_log_debug(...)     osal_log_with_level(OSAL_LOG_DEBUG, ROCKCHIP_LOG_TAG, __VA_ARGS__)

typedef enum _OSALLogLevel {
    OSAL_LOG_INFO,
    OSAL_LOG_WARNING,
    OSAL_LOG_ERROR,
    OSAL_LOG_DEBUG
} OSALLogLevel;

void osal_log_with_level(OSALLogLevel log_level, char *ptag, char *msg, ...);

#endif
