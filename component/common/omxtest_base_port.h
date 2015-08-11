#ifndef __OMXTEST_BASEPORT_H__
#define __OMXTEST_BASEPORT_H__

#include "OMX_Types.h"
#include "OMX_Core.h"
#include "omxtest_base_component.h"

typedef enum _BufferStatus {
    BUFFER_IDLE =       0x00,
    BUFFER_PROCESSING = 0x01,
    BUFFER_ERROR =      0x02
} BufferStatus;

typedef enum _PortStatus {
    PORT_IDLE =         0x00,
    PORT_PROCESSING =   0x01,
    PORT_ERROR =        0x02
} PortStatus;

typedef enum _BufferProcessType {
    BUFFER_DEFAULT =    0x00,
    BUFFER_SHARE =      0x00,
    BUFFER_COPY =       0x01
} BufferProcessType;

typedef enum _PortType {
    PORT_INPUT =        0x00,
    PORT_OUTPUT =       0x01
} PortType;

typedef struct _DataBuffer {
    BufferStatus        ibuffer_status;
    OMX_S32             ibuffer_size;
    OMX_PTR             pbuffer;
} DataBuffer;

typedef struct _Way1PortDataBuffer {
    BufferProcessType   buffer_process_type;
    OMX_HANDLETYPE      pdata_buffer_mutex;
    DataBuffer          data_buffer;
} Way1PortDataBuffer;

typedef struct _BasePort {
    OMX_STRING          sport_name;
    OMX_VERSIONTYPE     version;
    OMX_HANDLETYPE      pprivate;
    PortType            port_type;
    PortStatus          port_status;
    Way1PortDataBuffer  port1_data_buffer;
} BasePort;

OMX_ERRORTYPE BaseportConstruct(OMX_HANDLETYPE pcomponent)
{ 
}
OMX_ERRORTYPE BaseportDeConstruct(OMX_HANDLETYPE pcomponent);

#endif
