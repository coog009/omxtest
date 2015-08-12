#ifndef __OSAL_QUEUE_H__
#define __OSAL_QUEUE_H__

#include "OMX_Types.h"
#include "OMX_Core.h"
#include "list.h"

typedef OMX_ERRORTYPE (*ElemClearCallback)(OMX_PTR elem);

typedef struct _OSALQueue {
    struct list_head        elem_head;
    OMX_S32                 imax_num;
    OMX_S32                 icur_num;
    ElemClearCallback       pelem_clear_cb;
} OSALQueue;

OMX_ERRORTYPE osal_queue_init(OSALQueue *pqueue, OMX_S32 imax_num, ElemClearCallback pelem_clear_cb);
OMX_ERRORTYPE osal_queue_deinit(OSALQueue *pqueue);
OMX_ERRORTYPE osal_queue_enqueue(OSALQueue *pqueue, OMX_PTR *pelem);
OMX_PTR osal_queue_dequeue(OSALQueue *pqueue);
OMX_S32 osal_queue_get_curnum(OSALQueue *pqueue);
OMX_S32 osal_queue_get_maxnum(OSALQueue *pqueue);
void osal_queue_set_maxnum(OSALQueue *pqueue, OMX_S32 imax_num);
OMX_ERRORTYPE osal_queue_reset(OSALQueue *pqueue);

#endif
