#include <pthread.h>
#include "osal_sem.h"
#include "osal_memory.h"

OMX_ERRORTYPE osal_sem_create(OMX_HANDLETYPE *psem)
{
    pthread_cond_t *pcond = (pthread_cond_t *) osal_malloc(sizeof(pthread_cond_t));
    if (pcond == NULL) {
        return OMX_ErrorInsufficientResources;
    }

    pthread_cond_init(pcond, NULL);

    *psem = pcond;

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_sem_destroy(OMX_HANDLETYPE psem)
{
    pthread_cond_t *pcond = (pthread_cond_t *) psem;
    if (pcond == NULL) {
        return OMX_ErrorBadParameter;
    }

    pthread_cond_destroy(pcond);

    osal_free(pcond);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_sem_signal(OMX_HANDLETYPE psem)
{
    pthread_cond_t *pcond = (pthread_cond_t *) psem;
    if (pcond == NULL) {
        return OMX_ErrorBadParameter;
    }

    pthread_cond_signal(pcond);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_sem_broadcast(OMX_HANDLETYPE psem)
{
    pthread_cond_t *pcond = (pthread_cond_t *) psem;
    if (pcond == NULL) {
        return OMX_ErrorBadParameter;
    }

    pthread_cond_broadcast(pcond);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_sem_wait(OMX_HANDLETYPE psem, OMX_HANDLETYPE pmutex)
{
    pthread_cond_t *pcond = (pthread_cond_t *) psem;
    if (pcond == NULL) {
        return OMX_ErrorBadParameter;
    }

    pthread_mutex_t *ppmutex = (pthread_mutex_t *) pmutex;
    if (plocal_mutex == NULL) {
        return OMX_ErrorBadParameter;
    }

    pthread_cond_wait(psem, ppmutex);

    return OMX_ErrorNone;
}
