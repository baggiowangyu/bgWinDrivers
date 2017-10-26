#ifndef _DRIVER_ENTRY_H_
#define _DRIVER_ENTRY_H_

//////////////////////////////////////////////////////////////////////////
//
// 《国迈科技驱动开发——从入门到放弃》  第一课：Hello World
//
// 出品单位：技术中心-软件研发部
//
// 作者：GM0666
//
// 日期：2017-10-26
//
// 第一课在驱动入口函数中打印Hello World，旨在了解驱动程序最基本的结构。
//
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h>
#include <ntdef.h>

// 驱动程序入口函数
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, IN PUNICODE_STRING  registry_path);

// 驱动程序卸载函数
VOID DriverUnload(PDRIVER_OBJECT driver_object);

#ifdef __cplusplus
};
#endif

#endif//_DRIVER_ENTRY_H_