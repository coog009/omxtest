#ifndef _YUV2RGB_COMPONENT_H__
#define _YUV2RGB_COMPONENT_H__

#include "OMX_Types.h"
#include "OMX_Core.h"

#define DEFAULT_WIDTH			1920
#define DEFAULT_HEIGHT			1080

typedef struct _Yuv2rgbComponent {
    OMX_BOOL        bprocess_exit_flag;
    OMX_HANDLETYPE  pinput_process_thread;
    OMX_HANDLETYPE  poutput_process_thread;
	OMX_HANDLETYPE	port[PORT_NUM];
} Yuv2rgbComponent;

OMX_ERRORTYPE Yuv2rgbComponentConstruct(OMX_HANDLETYPE phandle, OMX_STRING scomponent_name)
{
	OMX_ERRORTYPE ret = OMX_ErrorNone;
	Yuv2rgbComponent *pyuv_component = NULL;
	OMX_COMPONENTTYPE *pcomponent = (OMX_COMPONENTTYPE *) phandle;
	BasePort *pbase_port = NULL;

	ret = BaseComponentConstructor(phandle);
	if (ret != OMX_ErrorNone) {
		goto YUV_COM_CONS_FAIL;
	}

	pyuv_component = (Yuv2rgbComponent *) osal_malloc(sizeof(Yuv2rgbComponent));
	if (pyuv_component == NULL) {
		ret = OMX_ErrorInsufficientResources;
		goto YUV_COM_CONS_FAIL;
	}
	
	pcomponent->pComponentPrivate = pyuv_component;
	
	/* input init */
	ret = BaseportConstruct(pyuv_component->port[0], PORT_INPUT, "yuv2rgb input port");
	if (ret != OMX_ErrorNone) {
		goto YUV_COM_CONS_FREE;
	}

	pbase_port = (BasePort *) pyuv_component->port[0];
	pbase_port->port_definition.color_type = YUV420;
	pbase_port->port_definition.iwidth = DEFAULT_WIDTH;
	pbase_port->port_definition.iheight = DEFAULT_HEIGHT;
	pbase_port->port_definition.ialign_width = DEFAULT_WIDTH;
	pbase_port->port_definition.ialign_height = DEFAULT_HEIGHT;
	
	/* output init */
	ret = BaseportConstruct(pyuv_component->port[1], PORT_OUTPUT, "yuv2rgb output port");
	if (ret != OMX_ErrorNone) {
		goto YUV_COM_CONS_FREE_INPUT;
	}
	
	pbase_port = (BasePort *) pyuv_component->port[1];
	pbase_port->port_definition.color_type = RGB;
	pbase_port->port_definition.iwidth = DEFAULT_WIDTH;
	pbase_port->port_definition.iheight = DEFAULT_HEIGHT;
	pbase_port->port_definition.ialign_width = DEFAULT_WIDTH;
	pbase_port->port_definition.ialign_height = DEFAULT_HEIGHT;

	ret = osal_thread_create(pyuv_component->pinput_process_thread, Yuv2rgbInputBufferProcessThread, hComponent);
	if (ret != OMX_ErrorNone) {
		goto YUV_COM_CONS_FREE_OUTPUT;
	}
	
	ret = osal_thread_create(pyuv_component->poutput_process_thread, Yuv2rgbOutputBufferProcessThread, hComponent);
	if (ret != OMX_ErrorNone) {
		goto YUV_COM_CONS_FREE_INPUT_THREAD;
	}

	return ret;

YUV_COM_CONS_FREE_INPUT_THREAD:
	pyuv_component->bprocess_exit_flag = OMX_TRUE;
	osal_thread_join(pyuv_component->pinput_process_thread);
	osal_thread_destroy(pyuv_component->pinput_process_thread);
YUV_COM_CONS_FREE_OUTPUT:
	BaseportDeConstruct(pyuv_component->port[1]);
YUV_COM_CONS_FREE_INPUT:
	BaseportDeConstruct(pyuv_component->port[0]);
YUV_COM_CONS_FREE:
	osal_free(pyuv_component);
YUV_COM_CONS_FAIL:
	return ret;
}

OMX_ERRORTYPE Yuv2rgbComponentDeConstruct(OMX_HANDLETYPE phandle)
{
	OMX_COMPONENTTYPE *pcomponent = (OMX_COMPONENTTYPE *) phandle;
	Yuv2rgbComponent *pyuv_component = (Yuv2rgbComponent *) pcomponent->pComponentPrivate;

	pyuv_component->bprocess_exit_flag = OMX_TRUE;
	osal_thread_join(pyuv_component->poutput_process_thread);
	osal_thread_join(pyuv_component->pinput_process_thread);

	BaseportDeConstruct(pyuv_component->port[0]);
	BaseportDeConstruct(pyuv_component->port[1]);

	osal_free(pyuv_component);

	pcomponent->pComponentPrivate = NULL;

	return OMX_ErrorNone;
}

OMX_ERRORTYPE Yuv2rgbInputBufferProcess(OMX_HANDLETYPE phandle)
{
	OMX_COMPONENTTYPE *pcomponent = (OMX_COMPONENTTYPE *) phandle;
	Yuv2rgbComponent *pyuv_component = (Yuv2rgbComponent *) pcomponent->pComponentPrivate;

	BasePort *pport = (BasePort *) pyuv_component->port[0];

	osal_mutex_lock(pport->port1_data_buffer.pmutex);
	
	while (osal_queue_get_curnum(pport->port1_data_buffer.buffer_queue) == 0) {
		osal_sem_wait(pport->port1_data_buffer.pempty_sem, pport->port1_data_buffer.pmutex);
	}

	DataBuffer *buffer = osal_queue_dequeue(pport->port1_data_buffer.buffer_queue);
	
	osal_mutex_unlock(pport->port1_data_buffer.pmutex);
}

OMX_ERRORTYPE Yuv2rgbInputBufferProcessThread(OMX_HANDLETYPE phandle)
{
	OMX_COMPONENTTYPE *pcomponent = (OMX_COMPONENTTYPE *) phandle;
	Yuv2rgbComponent *pyuv_component = (Yuv2rgbComponent *) pcomponent->pComponentPrivate;

	while (!pyuv_component->bprocess_exit_flag) {
	}
}

OMX_ERRORTYPE Yuv2rgbOutputBufferProcessThread(OMX_HANDLETYPE phandle);

#endif
