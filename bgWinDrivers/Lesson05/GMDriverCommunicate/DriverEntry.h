#ifndef _DRIVER_ENTRY_H_
#define _DRIVER_ENTRY_H_

//////////////////////////////////////////////////////////////////////////
//
// �������Ƽ������������������ŵ�������  �ڶ��Σ�NT Driver
//
// ��Ʒ��λ����������-����з���
//
// ���ߣ�GM0666
//
// ���ڣ�2017-10-26
//
// ����Σ��ں�̬���û�̬ͨ��
//
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h>
#include <ntdef.h>

typedef struct _GM_DEVICE_EXTENSION_
{
	UNICODE_STRING device_symbolink_name;
} GM_DEVICE_EXTENSION, *PGM_DEVICE_EXTENSION;

// ����������ں���
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver_object, IN PUNICODE_STRING  registry_path);

// ��������ж�غ���
VOID DriverUnload(IN PDRIVER_OBJECT driver_object);

// IRP��ǲ����
NTSTATUS NtDriverDispatchFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp);

// ��Ϣ������
NTSTATUS NtDriverDeviceIoControlFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp);

#ifdef __cplusplus
};
#endif

#endif
