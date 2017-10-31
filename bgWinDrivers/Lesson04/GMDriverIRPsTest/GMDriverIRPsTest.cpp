// GMDriverIRPsTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 2)
	{
		printf("GMDriverIRPs.exe [object_symbolink_name]\n");
		return 0;
	}

	TCHAR symbolink_name[4096] = {0};
	_tcscpy_s(symbolink_name, 4096, argv[1]);

	HANDLE object_handle = CreateFile(symbolink_name, GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_DEVICE, NULL);
	if (object_handle == INVALID_HANDLE_VALUE)
	{
		int errCode = GetLastError();
		printf("create device object failed. errCode : %d\n", errCode);
		return errCode;
	}

	printf("create device object success!\n");

	const char *data = "GoldMsg Driver Lesson 04 !";
	DWORD bytes = 0;
	BOOL result = WriteFile(object_handle, data, strlen(data), &bytes, NULL);
	if (!result)
	{
		int errCode = GetLastError();
		printf("write device object failed. errCode : %d\n", errCode);
		CloseHandle(object_handle);
		return errCode;
	}

	printf("write device object success!\n");

	char read_buffer[4096] = {0};
	result = ReadFile(object_handle, read_buffer, strlen(data), &bytes, NULL);
	if (!result)
	{
		int errCode = GetLastError();
		printf("read device object failed. errCode : %d\n", errCode);
		CloseHandle(object_handle);
		return errCode;
	}

	printf("read device object success!\n");

	CloseHandle(object_handle);

	return 0;
}

