/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/

#include "DriverEntry.h"

PDEVICE_OBJECT global_device_object = NULL;

NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver_object, IN PUNICODE_STRING  registry_path)
{
	// 这是一个条件打印函数，只在Debug版打印，Release自动被屏蔽
	KdPrint(("[GMDriverIRPs] Hello World !"));

	// 设置驱动对象的卸载例程
	// 驱动在被停止的时候由系统内核调用卸载例程
	driver_object->DriverUnload = DriverUnload;
	
	// 设置派发函数
	for (int index = 0; index < IRP_MJ_MAXIMUM_FUNCTION; ++index)
	{
		driver_object->MajorFunction[index] = NtDriverDispatchFunction;
	}

	// 这里设置5个常用派发函数
	driver_object->MajorFunction[IRP_MJ_CREATE]		= NtDriverCreateFunction;
	driver_object->MajorFunction[IRP_MJ_CLEANUP]	= NtDriverCleanupFunction;
	driver_object->MajorFunction[IRP_MJ_CLOSE]		= NtDriverCloseFunction;
	driver_object->MajorFunction[IRP_MJ_WRITE]		= NtDriverWriteFunction;
	driver_object->MajorFunction[IRP_MJ_READ]		= NtDriverReadFunction;

	// 接下来创建驱动的设备对象
	UNICODE_STRING device_name;
	RtlInitUnicodeString(&device_name, L"\\Device\\GMDriverIRPs");

	NTSTATUS statue = IoCreateDevice(driver_object, sizeof(GM_DEVICE_EXTENSION), &device_name, FILE_DEVICE_UNKNOWN, 0, TRUE, &global_device_object);
	if (!NT_SUCCESS(statue))
	{
		KdPrint(("[GMDriverIRPs] Create device object failed, status : 0x%X", statue));
		return statue;
	}

	UNICODE_STRING symbolink_name;
	RtlInitUnicodeString(&symbolink_name, L"\\??\\GMDriverIRPs");

	// 设置设备对象的相关信息
	global_device_object->Flags |= DO_BUFFERED_IO;

	// 设备对象扩展的内存空间在创建设备对象的时候就已经制定了，我们可以直接将这个内存区域转为结构体
	PGM_DEVICE_EXTENSION device_extension = (PGM_DEVICE_EXTENSION)global_device_object->DeviceExtension;
	device_extension->device_symbolink_name = symbolink_name;

	// 创建符号链接
	statue = IoCreateSymbolicLink(&symbolink_name, &device_name);
	if (!NT_SUCCESS(statue))
	{
		KdPrint(("[GMDriverIRPs] Create symbolink name failed, status : 0x%X", statue));
		return statue;
	}

	return STATUS_SUCCESS;
}

VOID DriverUnload(IN PDRIVER_OBJECT driver_object)
{
	// 首先枚举出设备对象
	// 然后删除对应设备对象的符号链接
	// 最后删除设备对象

	PDEVICE_OBJECT device_object = driver_object->DeviceObject;

	do {
		
		if (device_object == NULL)
		{
			KdPrint(("[GMDriverNtDriver] DriverUnload device object pointer is NULL ..."));
			break;
		}

		PGM_DEVICE_EXTENSION device_extension = (PGM_DEVICE_EXTENSION)device_object->DeviceExtension;

		NTSTATUS status = IoDeleteSymbolicLink(&device_extension->device_symbolink_name);
		if (!NT_SUCCESS(status))
		{
			KdPrint(("[GMDriverNtDriver] DriverUnload delete symbolinke name %wZ", &device_extension->device_symbolink_name));
		}

		// 由于一个驱动对象下可以创建多个设备对象，设备对象构成了一个设备栈
		// 这里即是取出当前的设备对象，然后设备栈指针向后移动
		PDEVICE_OBJECT current_device_object = device_object;
		device_object = device_object->NextDevice;

		IoDeleteDevice(current_device_object);

	} while (TRUE);
}

NTSTATUS NtDriverDispatchFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
	KdPrint(("[GMDriverNtDriver] NtDriverDispatchFunction"));

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS NtDriverCreateFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
	KdPrint(("[GMDriverNtDriver] NtDriverCreateFunction"));
	if (device_object == global_device_object)
	{
		// 读写本设备对象
		PIO_STACK_LOCATION io_stack_location = IoGetCurrentIrpStackLocation(irp);
		if (io_stack_location == NULL)
		{
			irp->IoStatus.Status = STATUS_SUCCESS;
			irp->IoStatus.Information = 0;

			IoCompleteRequest(irp, IO_NO_INCREMENT);
			return STATUS_SUCCESS;
		}
	}
	else
	{
		irp->IoStatus.Status = STATUS_SUCCESS;
		irp->IoStatus.Information = 0;

		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	}
}

NTSTATUS NtDriverCleanupFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
	KdPrint(("[GMDriverNtDriver] NtDriverCleanupFunction"));

	if (device_object == global_device_object)
	{

	}
	else
	{
		irp->IoStatus.Status = STATUS_SUCCESS;
		irp->IoStatus.Information = 0;

		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	}
}

NTSTATUS NtDriverCloseFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
	KdPrint(("[GMDriverNtDriver] NtDriverCloseFunction"));

	if (device_object == global_device_object)
	{

	}
	else
	{
		irp->IoStatus.Status = STATUS_SUCCESS;
		irp->IoStatus.Information = 0;

		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	}
}

NTSTATUS NtDriverReadFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
	KdPrint(("[GMDriverNtDriver] NtDriverReadFunction"));

	if (device_object == global_device_object)
	{
		unsigned char *buffer = irp->AssociatedIrp.SystemBuffer;
	}
	else
	{
		irp->IoStatus.Status = STATUS_SUCCESS;
		irp->IoStatus.Information = 0;

		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	}
}

NTSTATUS NtDriverWriteFunction(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
	KdPrint(("[GMDriverNtDriver] NtDriverWriteFunction"));

	if (device_object == global_device_object)
	{
		unsigned char *buffer = irp->AssociatedIrp.SystemBuffer;
	}
	else
	{
		irp->IoStatus.Status = STATUS_SUCCESS;
		irp->IoStatus.Information = 0;

		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
	}
}