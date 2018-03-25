
#pragma warning(disable:4200)  //
#pragma warning(disable:4201)  // nameless struct/union
#pragma warning(disable:4214)  // bit field types other than int

#include <ntddk.h>
#include <wdf.h>

#include "public.h"

EXTERN_C_START

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD CharSample_EvtDeviceAdd;

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL CharSample_EvtIoDeviceControl;

EXTERN_C_END

