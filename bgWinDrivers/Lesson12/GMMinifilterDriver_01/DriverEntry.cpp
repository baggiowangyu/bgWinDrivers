#include "DriverEntry.h"

//
//  Constant FLT_REGISTRATION structure for our filter.  This
//  initializes the callback routines our filter wants to register
//  for.  This is only used to register with the filter manager
//

const FLT_OPERATION_REGISTRATION Callbacks[] = {

	{ IRP_MJ_CREATE,
	0,
	ScannerPreCreate,
	ScannerPostCreate},

	{ IRP_MJ_CLEANUP,
	0,
	ScannerPreCleanup,
	NULL},

	{ IRP_MJ_WRITE,
	0,
	ScannerPreWrite,
	NULL},

	{ IRP_MJ_OPERATION_END}
};

const FLT_CONTEXT_REGISTRATION ContextRegistration[] = {

	{ FLT_STREAMHANDLE_CONTEXT,
	0,
	NULL,
	sizeof(SCANNER_STREAM_HANDLE_CONTEXT),
	'chBS' },

	{ FLT_CONTEXT_END }
};

const FLT_REGISTRATION FilterRegistration = {

	sizeof( FLT_REGISTRATION ),         //  Size
	FLT_REGISTRATION_VERSION,           //  Version
	0,                                  //  Flags
	ContextRegistration,                //  Context Registration.
	Callbacks,                          //  Operation callbacks
	ScannerUnload,                      //  FilterUnload
	ScannerInstanceSetup,               //  InstanceSetup
	ScannerQueryTeardown,               //  InstanceQueryTeardown
	NULL,                               //  InstanceTeardownStart
	NULL,                               //  InstanceTeardownComplete
	NULL,                               //  GenerateFileName
	NULL,                               //  GenerateDestinationFileName
	NULL                                //  NormalizeNameComponent
};

NTSTATUS DriverEntry( __in PDRIVER_OBJECT DriverObject, __in PUNICODE_STRING RegistryPath )
{
	NTSTATUS status = FltRegisterFilter(DriverObject, &FilterRegistration, &ScannerData.Filter);
	if (!NT_SUCCESS(status))
	{
		return status;
	}

	// 创建通信端口
	UNICODE_STRING port_name;
	RtlInitUnicodeString(&port_name, L"\\GMPort");

	PSECURITY_DESCRIPTOR security_descriptor;
	status = FltBuildDefaultSecurityDescriptor(&security_descriptor, FLT_PORT_ALL_ACCESS);
	if (!NT_SUCCESS(status))
	{
		OBJECT_ATTRIBUTES object_attr;
		InitializeObjectAttributes(&object_attr, &ScannerData.ServerPort, &object_attr)
	}
}