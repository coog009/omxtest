#include "osal_thread.h"
#include "osal_memory.h"
#include "osal_log.h"

OMX_ERRORTYPE osal_thread_create(OMX_HANDLETYPE *pthread_id, OSALThreadEntry thread_entry, OMX_PTR pparams)
{
    pthread_t *ppid = (pthread_t *) osal_malloc(sizeof(pthread_t));
    if (ppid == NULL) {
        return OMX_ErrorInsufficientResources;
    }

    if (thread_entry == NULL) {
       osal_log_error("%s thread entry is NULL\n", __func__);
       return OMX_ErrorBadParameter;
    }

    pthread_create(ppid, NULL, thread_entry, pparams);

    *pthread_id = ppid;

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_thread_join(OMX_HANDLETYPE pthread_id)
{
    pthread_t *ppid = (pthread_t *) pthread_id;
    if (ppid == NULL) {
        osal_log_error("%s parameter invalid\n");
       return OMX_ErrorBadParameter;
    }

    pthread_join(ppid);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_thread_destroy(OMX_HANDLETYPE pthread_id)
{
    pthread_t *ppid = (pthread_t *) pthread_id;
    if (ppid == NULL) {
        osal_log_error("%s parameter invalid\n");
       return OMX_ErrorBadParameter;
    }

    osal_free(ppid);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_thread_attach(OMX_HANDLETYPE pthread_id)
{
    pthread_t *ppid = (pthread_t *) pthread_id;
    if (ppid == NULL) {
        osal_log_error("%s parameter invalid\n");
       return OMX_ErrorBadParameter;
    }

    pthread_attach(ppid);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_thread_detach(OMX_HANDLETYPE pthread_id)
{
    pthread_t *ppid = (pthread_t *) pthread_id;
    if (ppid == NULL) {
        osal_log_error("%s parameter invalid\n");
       return OMX_ErrorBadParameter;
    }

    pthread_detach(ppid);

    return OMX_ErrorNone;
}
