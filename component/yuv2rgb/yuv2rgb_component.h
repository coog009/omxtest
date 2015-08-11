#ifndef _YUV2RGB_COMPONENT_H__
#define _YUV2RGB_COMPONENT_H__

#include "OMX_Types.h"
#include "OMX_Core.h"

typedef struct _Yuv2rgbComponent {
    OMX_HANDLETYPE  pfather;

    OMX_BOOL        bprocess_exit_flag;
    OMX_HANDLETYPE  pinput_process_thread;
    OMX_HANDLETYPE  poutput_process_thread;
} Yuv2rgbComponent;

OMX_ERRORTYPE Yuv2rgbComponentConstruct(OMX_HANDLETYPE hComponent, OMX_STRING componentName)
{
}

OMX_ERRORTYPE Yuv2rgbComponentDeConstruct(OMX_HANDLETYPE hComponent);
OMX_ERRORTYPE Yuv2rgbInputBufferProcess(OMX_HANDLETYPE hComponent);
OMX_ERRORTYPE Yuv2rgbOutputBufferProcess(OMX_HANDLETYPE hComponent);

#endif
