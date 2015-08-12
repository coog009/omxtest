#ifndef __OSAL_MUTEX_H__
#define __OSAL_MUTEX_H__

#include "OMX_Types.h"
#include "OMX_Core.h"

OMX_ERRORTYPE osal_mutex_create(OMX_HANDLETYPE *pmutex);
OMX_ERRORTYPE osal_mutex_destroy(OMX_HANDLETYPE pmutex);
OMX_ERRORTYPE osal_mutex_lock(OMX_HANDLETYPE pmutex);
OMX_ERRORTYPE osal_mutex_unlock(OMX_HANDLETYPE pmutex);

#endif
