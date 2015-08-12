#include "osal_queue.h"
#include "osal_memory.h"
#include "osal_log.h"

OMX_ERRORTYPE osal_queue_init(OSALQueue *pqueue, OMX_S32 imax_num, 
    ElemClearCallback pelem_clear_cb)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }

    INIT_LIST_HEAD(&pqueue->elem_head);
    pqueue->icur_num = 0;
    pqueue->imax_num = imax_num;

    pqueue->pelem_clear_cb = pelem_clear_cb;

    return OMX_ErrorNone;
}

OMX_ERRORTYPE osal_queue_deinit(OSALQueue *pqueue)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }

    /* clear the queue elem */
    osal_queue_reset(pqueue);

    pqueue->imax_num = pqueue->icur_num = 0;
}

OMX_ERRORTYPE osal_queue_enqueue(OSALQueue *pqueue, OMX_PTR *pelem)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }
    
    struct list_head *phead = (struct list_head *) pelem;
    list_add_tail(phead, &pqueue->elem_head);

    pqueue->icur_num++;

    return OMX_ErrorNone;
}

OMX_PTR osal_queue_dequeue(OSALQueue *pqueue)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }

    if (pqueue->icur_num > 0) {
       pqueue->icur_num--;
       struct list_head *pelem = pqueue->elem_head.next;
       list_del(pelem);

       return pelem;
    }

    return NULL;
}

OMX_S32 osal_queue_get_curnum(OSALQueue *pqueue)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }

    return pqueue->icur_num;
}

OMX_S32 osal_queue_get_maxnum(OSALQueue *pqueue)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }

    return pqueue->imax_num;
}

void osal_queue_set_maxnum(OSALQueue *pqueue, OMX_S32 imax_num)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }

    pqueue->imax_num = imax_num;
}

OMX_ERRORTYPE osal_queue_reset(OSALQueue *pqueue)
{
    if (pqueue == NULL) {
        osal_log_error("%s input parameter error\n", __func__);
        return OMX_ErrorBadParameter;
    }
        
    if (pqueue->pelem_clear_cb == NULL) {
        osal_log_error("%s elem clear cb is NULL\n", __func__);
        return OMX_ErrorBadParameter;
    }

    while (pqueue->icur_num > ) {
        OMX_PTR *pelem = osal_queue_dequeue(pqueue);
        pqueue->pelem_clear_cb(pelem);
    }

    pqueue->icur_num = 0;

    return OMX_ErrorNone;
}
