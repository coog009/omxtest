#ifndef __OSAL_MEMORY_H__
#define __OSAL_MEMORY_H__

#include "OMX_Types.h"
#include "OMX_Core.h"

OMX_PTR osal_malloc(OMX_U32 size);
void osal_free(OMX_PTR addr);
OMX_PTR osal_memset(OMX_PTR addr, OMX_S32 v, OMX_S32 n);
OMX_PTR osal_memcpy(OMX_PTR dst, OMX_PTR src, OMX_S32 n);
OMX_PTR osal_memmove(OMX_PTR dst, OMX_PTR src, OMX_S32 n);

#endif
