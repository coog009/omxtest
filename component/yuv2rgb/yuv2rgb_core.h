#ifndef __YUV2RGB_CORE_H__
#define __YUV2RGB_CORE_H__

#include "OMX_Types.h"
#include "OMX_Core.h"

typedef struct _Yuv2rgbCore {
	OSALQueue queue;
    OMX_HANDLETYPE      pmutex;
    OMX_HANDLETYPE      pempty_sem;
    OMX_HANDLETYPE      pfull_sem;
} Yuv2rgbCore;

#endif
