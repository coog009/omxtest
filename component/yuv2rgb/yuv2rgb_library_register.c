#include "yuv2rgb_library_register.h"

OMX_S32 RegisterLibrary(OTRegisterComponentType *componentEnums)
{
    FunctionIn();

    if (componentEnums == NULL) {
        goto EXIT;
    }

    strcpy(componentEnums[0]->component_name, OT_OMX_COMPONENT_YUV2RGB);
    strcpy(componentEnums[0]->roles[0], OT_OMX_COMPONENT_YUV2RGB_ROLE);
    componentEnums[0]->total_role_num = OT_OMX_COMPONENT_MAX_NUM;

EXIT:
    FunctionOut();
    return OT_OMX_COMPONENT_MAX_NUM;
}
