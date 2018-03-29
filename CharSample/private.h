
#pragma warning(disable:4200)  //
#pragma warning(disable:4201)  // nameless struct/union
#pragma warning(disable:4214)  // bit field types other than int

#include <ntddk.h>
#include <wdf.h>

#include "public.h"
#include "CharSample-ETW.h"  /* ETW header file */

EXTERN_C_START

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD CharSample_EvtDeviceAdd;
//DRIVER_UNLOAD MyUnload;
EVT_WDF_OBJECT_CONTEXT_CLEANUP CharSample_EvtDriverContextCleanup;


EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL CharSample_EvtIoDeviceControl;

EXTERN_C_END

