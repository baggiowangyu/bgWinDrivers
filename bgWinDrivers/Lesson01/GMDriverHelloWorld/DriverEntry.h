#ifndef _DRIVER_ENTRY_H_
#define _DRIVER_ENTRY_H_

//////////////////////////////////////////////////////////////////////////
//
// �������Ƽ������������������ŵ�������  ��һ�Σ�Hello World
//
// ��Ʒ��λ����������-����з���
//
// ���ߣ�GM0666
//
// ���ڣ�2017-10-26
//
// ��һ����������ں����д�ӡHello World��ּ���˽���������������Ľṹ��
//
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h>
#include <ntdef.h>

// ����������ں���
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, IN PUNICODE_STRING  registry_path);

// ��������ж�غ���
VOID DriverUnload(PDRIVER_OBJECT driver_object);

#ifdef __cplusplus
};
#endif

#endif//_DRIVER_ENTRY_H_