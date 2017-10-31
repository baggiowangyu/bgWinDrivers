// GMDriverNtDriverInstaller.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <windows.h>
#include <winsvc.h>
//#include <iostream>




int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3)
	{
		printf("GMDriverNtDriverInstaller.exe [ServiceName] [SysPath]\n");
		return 0;
	}

	TCHAR service_name[4096] = {0};
	_tcscpy_s(service_name, 4096, argv[1]);

	TCHAR sys_path[4096] = {0};
	_tcscpy_s(sys_path, 4096, argv[2]);

	// 
	SC_HANDLE sc_handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (sc_handle == NULL)
	{
		int errCode = GetLastError();
		printf("OpenSCManager failed . errCode : %d\n", errCode);
		return errCode;
	}

	// ������������Ƿ����
	// ������ڣ���ֱ����������
	// ��������ڣ��򴴽����������
	SC_HANDLE service_handle = OpenService(sc_handle, service_name, SERVER_ALL_ACCESS);
	if (service_handle == NULL)
	{
		int errCode = GetLastError();
		if (errCode == ERROR_SERVICE_DOES_NOT_EXIST)
		{
			// ��������
			service_handle = CreateService(sc_handle, service_name, service_name, SERVER_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, sys_path, _T("load_group"), NULL, NULL, NULL, NULL);
			if (service_handle == NULL)
			{
				int errCode = GetLastError();
				printf("CreateService failed . errCode : %d\n" ,errCode);
				CloseServiceHandle(sc_handle);
				return errCode;
			}
		}
		else
		{
			printf("OpenService failed . errCode : %d\n", errCode);
			CloseServiceHandle(sc_handle);
			return errCode;
		}
	}

	BOOL b = StartService(service_handle, 0, NULL);
	if (!b)
	{
		int errCode = GetLastError();
		printf("StartService failed . errCode : %d\n", errCode);
		CloseServiceHandle(sc_handle);
		return errCode;
	}

	return 0;
}

