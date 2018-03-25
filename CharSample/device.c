
#include "private.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, CharSample_EvtDeviceAdd)
#endif

NTSTATUS
CharSample_EvtDeviceAdd(
    IN WDFDRIVER       Driver,
    IN PWDFDEVICE_INIT DeviceInit
    )
{
    NTSTATUS			status;
    WDFDEVICE			device;
    WDF_IO_QUEUE_CONFIG	ioQueueConfig;

	//���̵��׾�PAGED_CODE����ʾ�����̵Ĵ���ռ�÷�ҳ�ڴ档
	//ֻ����PASSIVE_LEVEL�жϼ�����ø����̣������������
	//�粻˵������ռ��ϵͳ�ķǷ�ҳ�ڴ棬Ҫ��ϧʹ�á�
    PAGED_CODE();

	//�����豸��û�ж������Ժ��豸���󻷾������ṹ
    status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);
    if (!NT_SUCCESS(status)) {
        return status;
    }

	//��ʼ��ȱʡ�������ã�����I/O����ַ�����ʽΪ���С�
	//�����ʵ�����ԣ�ѡ���л��ж����ԣ�������ѡ�ֹ���
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&ioQueueConfig, WdfIoQueueDispatchSequential);

	//����EvtIoDeviceControl���̣�����Ӧ�ó����DeviceIoControl()��������
    ioQueueConfig.EvtIoDeviceControl  = CharSample_EvtIoDeviceControl;

	//��������
    status = WdfIoQueueCreate(device, &ioQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, NULL);
    if (!NT_SUCCESS(status)) {
        return status;
    }

	//�����豸GUID�ӿ�
    status = WdfDeviceCreateDeviceInterface(device, (LPGUID) &CharSample_DEVINTERFACE_GUID, NULL);
    if (!NT_SUCCESS(status)) {
    }

    return status;
}


