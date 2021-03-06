
#include "private.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text (PAGE, CharSample_EvtDeviceAdd)
#pragma alloc_text (PAGE, CharSample_EvtDriverContextCleanup)
#endif

NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT  DriverObject,
	_In_ PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:
    DriverEntry initializes the driver and is the first routine called by the
    system after the driver is loaded.

Parameters Description:

    DriverObject - represents the instance of the function driver that is loaded
    into memory. DriverEntry must initialize members of DriverObject before it
    returns to the caller. DriverObject is allocated by the system before the
    driver is loaded, and it is released by the system after the system unloads
    the function driver from memory.

    RegistryPath - represents the driver specific path in the Registry.
    The function driver can use the path to store driver related data between
    reboots. The path does not store hardware instance specific data.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
    WDF_DRIVER_CONFIG  config;
    NTSTATUS		   status;
	WDF_OBJECT_ATTRIBUTES attributes;

    //
    // Initiialize driver config to control the attributes that
    // are global to the driver. Note that framework by default
    // provides a driver unload routine. If you create any resources
    // in the DriverEntry and want to be cleaned in driver unload,
    // you can override that by manually setting the EvtDriverUnload in the
    // config structure. In general xxx_CONFIG_INIT macros are provided to
    // initialize most commonly used members.
    //

	KdPrint(("CharSample: " __FUNCTION__ " Enter\n"));

    WDF_DRIVER_CONFIG_INIT(&config, CharSample_EvtDeviceAdd);

    // Register a cleanup callback so that we can call WPP_CLEANUP when
    // the framework driver object is deleted during driver unload.
    //
    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    attributes.EvtCleanupCallback = CharSample_EvtDriverContextCleanup;

    //
    // Create a framework driver object to represent our driver.
    //
    status = WdfDriverCreate(
        DriverObject,
        RegistryPath,
		&attributes,					// Driver Attributes
        &config,					// Driver Config Info
        WDF_NO_HANDLE				// hDriver
        );

	// Register ETW
	EventRegisterFunction_Entry_Exit_Provider();
	EventWriteFunctionEntry(NULL, __FUNCTION__ , 2);

	EventWriteFuntionExit(NULL, __FUNCTION__, 2);
	KdPrint(("CharSample: " __FUNCTION__ " Exit\n"));
    return status;
}

//_Use_decl_annotations_
//VOID
//MyUnload(
//	struct _DRIVER_OBJECT  *DriverObject
//)
//{
//	// Function body
//}


VOID
CharSample_EvtDriverContextCleanup(
	_In_ WDFOBJECT DriverObject
)
/*++
Routine Description:

Free all the resources allocated in DriverEntry.

Arguments:

DriverObject - handle to a WDF Driver object.

Return Value:

VOID.

--*/
{
	UNREFERENCED_PARAMETER(DriverObject);

	PAGED_CODE();

	// Unregister ETW
	EventUnregisterFunction_Entry_Exit_Provider();
}
