#ifndef _DRIVER_ENTRY_H_
#define _DRIVER_ENTRY_H_

//////////////////////////////////////////////////////////////////////////
//
// 《国迈科技驱动开发——从入门到放弃》  第二课：NT Driver
//
// 出品单位：技术中心-软件研发部
//
// 作者：GM0666
//
// 日期：2017-10-26
//
// 第五课：内核态与用户态通信
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

// 驱动程序入口函数
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver_object, IN PUNICODE_STRING  registry_path);

// 驱动程序卸载函数
VOID DriverUnload(IN PDRIVER_OBJECT driver_object);

// IRP派遣函数
NTSTATUS NtDriverDispatchFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp);

// 消息处理函数
NTSTATUS NtDriverDeviceIoControlFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp);

#ifdef __cplusplus
};
#endif

#endif
