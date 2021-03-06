#ifndef _DriverEntry_H_
#define _DriverEntry_H_

#include "ddk/fltKernel.h"
#include "ddk/ntddk.h"
#include "api/ntdef.h"


///////////////////////////////////////////////////////////////////////////
//
//  Global variables
//
///////////////////////////////////////////////////////////////////////////


typedef struct _SCANNER_DATA {

	//
	//  The object that identifies this driver.
	//

	PDRIVER_OBJECT DriverObject;

	//
	//  The filter handle that results from a call to
	//  FltRegisterFilter.
	//

	PFLT_FILTER Filter;

	//
	//  Listens for incoming connections
	//

	PFLT_PORT ServerPort;

	//
	//  User process that connected to the port
	//

	PEPROCESS UserProcess;

	//
	//  Client port for a connection to user-mode
	//

	PFLT_PORT ClientPort;

} SCANNER_DATA, *PSCANNER_DATA;

extern SCANNER_DATA ScannerData;

typedef struct _SCANNER_STREAM_HANDLE_CONTEXT {

	BOOLEAN RescanRequired;

} SCANNER_STREAM_HANDLE_CONTEXT, *PSCANNER_STREAM_HANDLE_CONTEXT;

#pragma warning(push)
#pragma warning(disable:4200) // disable warnings for structures with zero length arrays.

typedef struct _SCANNER_CREATE_PARAMS {

	WCHAR String[0];

} SCANNER_CREATE_PARAMS, *PSCANNER_CREATE_PARAMS;

#pragma warning(pop)


NTSTATUS
ScannerPortConnect
(
	__in PFLT_PORT ClientPort,
	__in_opt PVOID ServerPortCookie,
	__in_bcount_opt(SizeOfContext) PVOID ConnectionContext,
	__in ULONG SizeOfContext,
	__deref_out_opt PVOID *ConnectionCookie
);

VOID
ScannerPortDisconnect
(
	__in_opt PVOID ConnectionCookie
);

NTSTATUS
ScannerpScanFileInUserMode
(
	__in PFLT_INSTANCE Instance,
	__in PFILE_OBJECT FileObject,
	__out PBOOLEAN SafeToOpen
);

BOOLEAN
ScannerpCheckExtension
(
	__in PUNICODE_STRING Extension
);


DRIVER_INITIALIZE DriverEntry;
NTSTATUS
DriverEntry (
			 __in PDRIVER_OBJECT DriverObject,
			 __in PUNICODE_STRING RegistryPath
			 );

NTSTATUS
ScannerUnload (
			   __in FLT_FILTER_UNLOAD_FLAGS Flags
			   );

NTSTATUS
ScannerQueryTeardown (
					  __in PCFLT_RELATED_OBJECTS FltObjects,
					  __in FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
					  );

FLT_PREOP_CALLBACK_STATUS
ScannerPreCreate (
				  __inout PFLT_CALLBACK_DATA Data,
				  __in PCFLT_RELATED_OBJECTS FltObjects,
				  __deref_out_opt PVOID *CompletionContext
				  );

FLT_POSTOP_CALLBACK_STATUS
ScannerPostCreate (
				   __inout PFLT_CALLBACK_DATA Data,
				   __in PCFLT_RELATED_OBJECTS FltObjects,
				   __in_opt PVOID CompletionContext,
				   __in FLT_POST_OPERATION_FLAGS Flags
				   );

FLT_PREOP_CALLBACK_STATUS
ScannerPreCleanup (
				   __inout PFLT_CALLBACK_DATA Data,
				   __in PCFLT_RELATED_OBJECTS FltObjects,
				   __deref_out_opt PVOID *CompletionContext
				   );

FLT_PREOP_CALLBACK_STATUS
ScannerPreWrite (
				 __inout PFLT_CALLBACK_DATA Data,
				 __in PCFLT_RELATED_OBJECTS FltObjects,
				 __deref_out_opt PVOID *CompletionContext
				 );

NTSTATUS
ScannerInstanceSetup (
					  __in PCFLT_RELATED_OBJECTS FltObjects,
					  __in FLT_INSTANCE_SETUP_FLAGS Flags,
					  __in DEVICE_TYPE VolumeDeviceType,
					  __in FLT_FILESYSTEM_TYPE VolumeFilesystemType
					  );
#endif//_DriverEntry_H_
