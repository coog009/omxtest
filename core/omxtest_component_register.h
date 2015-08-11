#ifndef __OMXTEST_COMPONENT_REGISTER_H__
#define __OMXTEST_COMPONENT_REGISTER_H__

#include "OMX_Types.h"
#include "OMX_Core.h"
#include "OMX_Component.h"

typedef struct _OTRegisterComponentType
{
    OMX_U8  component_name[MAX_OMX_COMPONENT_NAME_SIZE];
    OMX_U8  roles[MAX_OMX_COMPONENT_ROLE_NUM][MAX_OMX_COMPONENT_ROLE_SIZE];
    OMX_U32 total_role_num;
} OTRegisterComponentType;

typedef struct _OTCOMPONENTREGLIST
{
    RockchipRegisterComponentType component;
    OMX_U8  libName[MAX_OMX_COMPONENT_LIBNAME_SIZE];
} OTCOMPONENTREGLIST;

struct ROCKCHIP_OMX_COMPONENT;
typedef struct _ROCKCHIP_OMX_COMPONENT
{
    OMX_U8                          componentName[MAX_OMX_COMPONENT_NAME_SIZE];
    OMX_U8                          libName[MAX_OMX_COMPONENT_LIBNAME_SIZE];
    OMX_HANDLETYPE                  libHandle;
    OMX_STRING                      rkversion;
    OMX_COMPONENTTYPE               *pOMXComponent;
    struct _ROCKCHIP_OMX_COMPONENT  *nextOMXComp;
} ROCKCHIP_OMX_COMPONENT;

OMX_ERRORTYPE OTComponentRegister(ROCKCHIP_OMX_COMPONENT_REGLIST **compList, OMX_U32 *compNum);
OMX_ERRORTYPE OTComponentUnregister(ROCKCHIP_OMX_COMPONENT_REGLIST *componentList);
OMX_ERRORTYPE OTComponentLoad(ROCKCHIP_OMX_COMPONENT *rockchip_component);
OMX_ERRORTYPE OTComponentUnload(ROCKCHIP_OMX_COMPONENT *rockchip_component);

#endif
