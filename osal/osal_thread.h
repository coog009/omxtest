#ifndef __OSAL_THREAD_H__
#define __OSAL_THREAD_H__

#include "OMX_Types.h"
#include "OMX_Core.h"

typedef void (*OSALThreadEntry)(OMX_PTR pdata);

OMX_ERRORTYPE osal_thread_create(OMX_HANDLETYPE *pthread_id, OSALThreadEntry thread_entry, OMX_PTR pparams);
void osal_thread_join(OMX_HANDLETYPE pthread_id);
OMX_ERRORTYPE osal_thread_destroy(OMX_HANDLETYPE pthread_id);
void osal_thread_attach(OMX_HANDLETYPE pthread_id);
void osal_thread_detach(OMX_HANDLETYPE pthread_id);

#endif
