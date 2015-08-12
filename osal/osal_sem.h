#ifndef __OSAL_SEM_H__
#define __OSAL_SEM_H__

#include "OMX_Types.h"
#include "OMX_Core.h"

OMX_ERRORTYPE osal_sem_create(OMX_HANDLETYPE *psem);
OMX_ERRORTYPE osal_sem_destroy(OMX_HANDLETYPE psem);
OMX_ERRORTYPE osal_sem_signal(OMX_HANDLETYPE psem);
OMX_ERRORTYPE osal_sem_broadcast(OMX_HANDLETYPE psem);
OMX_ERRORTYPE osal_sem_wait(OMX_HANDLETYPE psem, OMX_HANDLETYPE pmutex);

#endif
