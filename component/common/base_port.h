#ifndef __BASE_PORT_H__
#define __BASE_PORT_H__

#include "OMX_Types.h"
#include "OMX_Core.h"
#include "base_def.h"
#include "base_component.h"
#include "osal_thread.h"
#include "osal_mutex.h"
#include "osal_sem.h"

#define QUEUE_DEFAULT_MAX_NUM           10

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
    PORT_OUTPUT =       0x01,
    PORT_NUM =			0x02
} PortType;

typedef enum _FormatColorType {
	YUV420 =			0x00,
	RGB	=				0x01
} FormatColorType;

typedef struct _DataBuffer {
    struct list_head    head;
    BufferStatus        ibuffer_status;
    OMX_S32             ibuffer_size;
    OMX_PTR             pbuffer;
} DataBuffer;

typedef struct _Way1PortDataBuffer {
    BufferProcessType   buffer_process_type;
    OSALQueue           buffer_queue;
    OMX_HANDLETYPE      pmutex;
    OMX_HANDLETYPE      pempty_sem;
    OMX_HANDLETYPE      pfull_sem;
} Way1PortDataBuffer;

typedef struct _PortDefinition {
	FormatColorType color_type;
	OMX_S32 iwidth;
	OMX_S32 iheight;
	OMX_S32 ialign_width;
	OMX_S32 ialign_height;
} PortDefinition;

typedef struct _BasePort {
    OMX_STRING          sport_name;
    OMX_VERSIONTYPE     version;
    OMX_HANDLETYPE      pprivate;
    PortType            port_type;
    PortStatus          port_status;
    Way1PortDataBuffer  port1_data_buffer;
	PortDefinition		port_definition;
} BasePort;

OMX_ERRORTYPE DataBufferConstruct(DataBuffer **ppdata_buffer, OMX_S32 ibuffer_size)
{
    DataBuffer *pdata_buffer = (DataBuffer *) osal_malloc(sizeof(DataBuffer));
    if (pdata_buffer == NULL) {
        osal_log_error("%s data buffer malloc failed\n", __func__);
        return OMX_ErrorInsufficientResources;
    }

    INIT_LIST_HEAD(&pdata_buffer->head);

    if (ibuffer_size > 0) {
        pdata_buffer->pbuffer = osal_malloc(ibuffer_size);
        if (pdata_buffer->pbuffer) {
            osal_log_error("%s pbuffer malloc failed\n", __func__);
            return OMX_ErrorInsufficientResources;
        }

        osal_memset(pdata_buffer->pbuffer, 0, ibuffer_size);

        pdata_buffer->ibuffer_size = ibuffer_size;
    } else {
        osal_log_error("%s buffer size can not less than 1", __func__);
        osal_free(pdata_buffer);

        return OMX_ErrorBadParameter;
    }

    return OMX_ErrorNone;
}

void DataBufferDeConstruct(OMX_PTR pdata)
{
    DataBuffer *pdata_buffer = (DataBuffer *) pdata;
    osal_free(pdata_buffer->pbuffer);
    osal_free(pdata_buffer);
}

OMX_BOOL BaseportCheckVersion(OMX_HANDLETYPE pport)
{
	BasePort *pbase_port = (BasePort *) pport;

	if (pbase_port->version.s.nVersionMajor > PORT_MAJOR_VERSION ||
		(pbase_port->version.s.nVersionMajor == PORT_MAJOR_VERSION && 
			pbase_port->version.s.nVersionMinor > PORT_MINOR_VERSION)) {
			
		return OMX_FALSE;
	}

	return OMX_TRUE;
}

OMX_ERRORTYPE BaseportConstruct(OMX_HANDLETYPE *pport, PortType port_type, OMX_STRAING sport_name)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    BasePort *pbase_port = (BasePort *) osal_malloc(sizeof(BasePort));
    if (pbase_port == NULL) {
        osal_log_error("%s port malloc failed\n", __func__);
        ret = OMX_ErrorInsufficientResources;
        goto PORT_CONS_ERROR_EXIT;
    }

    osal_memset(pbase_port, 0, sizeof(BasePort));

    if (sport_name != NULL) {
        OMX_S32 iport_name_len = strlen(sport_name);
        pbase_port->sport_name = (OMX_STRING) osal_malloc(iport_name_len + 1);
        if (pbase_port->sport_name == NULL) {
            osal_log_error("%s port_name malloc failed\n", __func__);
            ret = OMX_ErrorInsufficientResources;
            goto PORT_CONS_FREE;
        }
        osal_memset(pbase_port->sport_name, 0, iport_name_len + 1);
        strcpy(pbase_port->sport_name, sport_name);
    }

    pbase_port->version.s.nVersionMajor = PORT_MAJOR_VERSION;
    pbase_port->version.s.nVersionMinor = PORT_MINOR_VERSION;
    pbase_port->version.s.nRevision = PORT_REVISION;
    pbase_port->version.s.nStep = PORT_STEP;

    pbase_port->port_type = port_type;
    pbase_port->port_status = PORT_IDLE;

    pbase_port->port1_data_buffer.buffer_process_type = BUFFER_IDLE;

    ret = osal_mutex_create(&pbase_port->port1_data_buffer.pmutex);
    if (ret != OMX_ErrorNone) {
        osal_log_error("%s mutex create failed", __func__);
        goto PORT_CONS_FREE;
    }

    ret = osal_sem_create(&pbase_port->port1_data_buffer.pempty_sem);
    if (ret != OMX_ErrorNone) {
        osal_log_error("%s empty sem create failed", __func__);
        goto PORT_CONS_MUTEX_FREE;
    }

    ret = osal_sem_create(&pbase_port->port1_data_buffer.pfull_sem);
    if (ret != OMX_ErrorNone) {
        osal_log_error("%s full sem create failed", __func__);
        goto PORT_CONS_EMPTY_SEM_FREE;
    }

    ret = osal_queue_init(&pbase_port->port1_data_buffer.buffer_queue, QUEUE_DEFAULT_MAX_NUM, DataBufferDeConstruct);
    if (ret != OMX_ErrorNone) {
        osal_log_error("%s queue init failed", __func__);
        goto PORT_CONS_FULL_SEM_FREE;
    }

    *pport = pbase_port;

    return OMX_ErrorNone;

PORT_CONS_FULL_SEM_FREE:
    osal_sem_destroy(&pbase_port->port1_data_buffer.pfull_sem);
PORT_CONS_EMPTY_SEM_FREE:
    osal_sem_destroy(&pbase_port->port1_data_buffer.pempty_sem);
PORT_CONS_MUTEX_FREE:
    osal_mutex_destroy(&pbase_port->port1_data_buffer.pmutex);
PORT_CONS_FREE:
    osal_free(pbase_port);
PORT_CONS_ERROR_EXIT:
	
    return ret;
}

OMX_ERRORTYPE BaseportDeConstruct(OMX_HANDLETYPE pport)
{
	OMX_ERRORTYPE ret = OMX_ErrorNone;
	BasePort *pbase_port = (BasePort *) pport;

	if (!BaseportCheckVersion(pport)) {
		osal_log_error("invalidate version\n");

		return OMX_ErrorBadParameter;
	}

	ret = osal_sem_destroy(&pbase_port->port1_data_buffer.pfull_sem);
	if (ret != OMX_ErrorNone) {
		osal_log_error("full sem destroy failed\n");
		goto PORT_DECONS_ERROR_EXIT;
	}
	
	ret = osal_sem_destroy(&pbase_port->port1_data_buffer.pempty_sem);
	if (ret != OMX_ErrorNone) {
		osal_log_error("empty sem destroy failed\n");
		goto PORT_DECONS_ERROR_EXIT;
	}
	
	ret = osal_mutex_destroy(&pbase_port->port1_data_buffer.pmutex);
	if (ret != OMX_ErrorNone) {
		osal_log_error("databuffer mutex destroy failed\n");
		goto PORT_DECONS_ERROR_EXIT;
	}

	ret = osal_queue_deinit(pbase_port->port1_data_buffer.buffer_queue);
	if (ret != OMX_ErrorNone) {
		osal_log_error("queue destroy failed\n");
		goto PORT_DECONS_ERROR_EXIT;
	}

	if (pbase_port->sport_name != NULL)
		osal_free(pbase_port->sport_name);
	
	osal_free(pbase_port);

	return ret;

PORT_DECONS_ERROR_EXIT:
	return ret;
}

OMX_ERRORTYPE BasePortFillThisBuffer(
    OMX_IN OMX_HANDLETYPE        hComponent,
    OMX_IN OMX_BUFFERHEADERTYPE *pBuffer)
{
}

#endif
