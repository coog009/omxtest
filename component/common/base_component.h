#ifndef __OMXTEST_BASECOMPONENT_H__
#define __OMXTEST_BASECOMPONENT_H__

#include "OMX_Types.h"
#include "OMX_Core.h"
#include "omxtest_baseport.h"

typedef struct _BaseComponent {
    OMX_STRING      scomponent_name;
    OMX_VERSIONTYPE version;
    OMX_HANDLETYPE  pprivate;
} BaseComponent;

OMX_ERRORTYPE BaseComponentConstructor(OMX_IN OMX_HANDLETYPE hComponent)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE        *pOMXComponent;

    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;


}

#endif
