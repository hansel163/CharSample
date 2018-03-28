
#include "private.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, CharSample_EvtIoDeviceControl)
#endif

VOID
CharSample_EvtIoDeviceControl(
	_In_ WDFQUEUE   Queue,
	_In_ WDFREQUEST Request,
	_In_ size_t     OutputBufferLength,
	_In_ size_t     InputBufferLength,
	_In_ ULONG      IoControlCode
    )
{
    NTSTATUS  status;
    PVOID	  buffer;
	CHAR	  n,c[]="abcdefghij";

	UNREFERENCED_PARAMETER(Queue);
    PAGED_CODE();

    switch(IoControlCode) {

    case CharSample_IOCTL_800:
		if (InputBufferLength  == 0 || OutputBufferLength < 1)
		{	//检查输入、输出参数有效性
			WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
		}
		else
		{
			//输入缓冲区地址可通过调用WdfRequestRetrieveInputBuffer函数获得
			//输出缓冲区地址可通过调用WdfRequestRetrieveOutputBuffer函数获得

			//获取输入缓冲区地址buffer
			//要求1字节空间
			status = WdfRequestRetrieveInputBuffer(Request, 1, &buffer, NULL);
			if (!NT_SUCCESS(status)) {
				WdfRequestComplete(Request, STATUS_UNSUCCESSFUL);
		        break;
			}

			//这里buffer表示输入缓冲区地址
			//输入n=应用程序传给驱动程序的数字ASCII码
			n = *(CHAR *)buffer;
			if ((n>='0') && (n<='9'))
			{	//若为数字，则处理
				n-='0';	//n=数字(0-9)

				//获取输出缓冲区地址buffer
				status = WdfRequestRetrieveOutputBuffer(Request, 1, &buffer, NULL);
				if (!NT_SUCCESS(status)) {
					WdfRequestComplete(Request, STATUS_UNSUCCESSFUL);
					break;
				}

				//这里buffer表示输出缓冲区地址
				//输出：从数组c[]中取出对应的数字的字母，拷贝到输出缓冲区
				strncpy((PCHAR)buffer,&c[n],1);

				//完成I/O请求，驱动程序传给应用程序的数据长度为1字节
				WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, 1);
			}
			else //否则返回无效参数
				WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
		}
        break;

    default :
        status = STATUS_INVALID_DEVICE_REQUEST;
		WdfRequestCompleteWithInformation(Request, status, 0);
        break;
    }

    return;
}

