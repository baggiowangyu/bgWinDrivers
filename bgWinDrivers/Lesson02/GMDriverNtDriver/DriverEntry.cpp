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
         ���汣��       ����BUG
*/

#include "DriverEntry.h"

NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver_object, IN PUNICODE_STRING  registry_path)
{
	// ����һ��������ӡ������ֻ��Debug���ӡ��Release�Զ�������
	KdPrint(("[GMDriverNtDriver] Hello World !"));

	// �������������ж������
	// �����ڱ�ֹͣ��ʱ����ϵͳ�ں˵���ж������
	driver_object->DriverUnload = DriverUnload;
	
	// �����ɷ�����
	// ��������ֻ����4���ɷ�����
	driver_object->MajorFunction[IRP_MJ_CREATE] = NtDriverDispatchFunction;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = NtDriverDispatchFunction;
	driver_object->MajorFunction[IRP_MJ_WRITE] = NtDriverDispatchFunction;
	driver_object->MajorFunction[IRP_MJ_READ] = NtDriverDispatchFunction;

	// �����������������豸����
	UNICODE_STRING device_name;
	RtlInitUnicodeString(&device_name, L"\\Device\\GMDriverNtDriver");

	PDEVICE_OBJECT device_object = NULL;

	NTSTATUS statue = IoCreateDevice(driver_object, sizeof(GM_DEVICE_EXTENSION), &device_name, FILE_DEVICE_UNKNOWN, 0, TRUE, &device_object);
	if (!NT_SUCCESS(statue))
	{
		KdPrint(("[GMDriverNtDriver] Create device object failed, status : 0x%X", statue));
		return statue;
	}

	UNICODE_STRING symbolink_name;
	RtlInitUnicodeString(&symbolink_name, L"\\??\\GMDriverNtDriver");

	// �����豸����������Ϣ
	device_object->Flags |= DO_BUFFERED_IO;

	// �豸������չ���ڴ�ռ��ڴ����豸�����ʱ����Ѿ��ƶ��ˣ����ǿ���ֱ�ӽ�����ڴ�����תΪ�ṹ��
	PGM_DEVICE_EXTENSION device_extension = (PGM_DEVICE_EXTENSION)device_object->DeviceExtension;
	device_extension->device_symbolink_name = symbolink_name;

	// ������������
	statue = IoCreateSymbolicLink(&symbolink_name, &device_name);
	if (!NT_SUCCESS(statue))
	{
		KdPrint(("[GMDriverNtDriver] Create symbolink name failed, status : 0x%X", statue));
		return statue;
	}

	return STATUS_SUCCESS;
}

VOID DriverUnload(IN PDRIVER_OBJECT driver_object)
{
	// ����ö�ٳ��豸����
	// Ȼ��ɾ����Ӧ�豸����ķ�������
	// ���ɾ���豸����

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

		// ����һ�����������¿��Դ�������豸�����豸���󹹳���һ���豸ջ
		// ���Ｔ��ȡ����ǰ���豸����Ȼ���豸ջָ������ƶ�
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