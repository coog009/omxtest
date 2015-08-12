#ifndef __OSAL_MUTEX_H__
#define __OSAL_MUTEX_H__

#include <pthread.h>

#include "osal_memory.h"
#include "osal_mutex.h"
#include "osal_log.h"

OMX_ERRORTYPE osal_mutex_create(OMX_HANDLETYPE *pmutex)
{
    pthread_mutex_t *ppmutex = (pthread_mutex_t *) osal_malloc(sizeof(pthread_mutex_t));
    if (ppmutex == NULL) {
        return OMX_ErrorInsufficientResources;
    }

    if (pthread_mutex_init(ppmutex, NULL) != 0) {
        osal_free(ppmutex);
        return OMX_ErrorUndefined;
    }

    *pmutex = ppmutex;

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_mutex_destroy(OMX_HANDLETYPE pmutex)
{
    pthread_mutex_t *ppmutex = (pthread_mutex_t *) pmutex;
    if (ppmutex == NULL) {
        return OMX_ErrorBadParameter;
    }

    pthread_mutex_destroy(ppmutex);
    osal_free(ppmutex);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_mutex_lock(OMX_HANDLETYPE pmutex)
{
    pthread_mutex_t *ppmutex = (pthread_mutex_t *) pmutex;
    pthread_mutex_lock(ppmutex);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_mutex_unlock(OMX_HANDLETYPE pmutex)
{
    pthread_mutex_t *ppmutex = (pthread_mutex_t *) pmutex;
    pthread_mutex_unlock(ppmutex);

    return OMX_ErrorNone;
}

#endif
