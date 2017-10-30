// GMDriverNtDriverInstaller.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <winsvc.h>
#include <windows.h>




int _tmain(int argc, _TCHAR* argv[])
{
	//if (argc < 3)
	//{
	//	std::cout<<"GMDriverNtDriverInstaller.exe [ServiceName] [SysPath]"<<std::endl;
	//	return 0;
	//}

	//TCHAR service_name[4096] = {0};
	//_tcscpy_s(service_name, 4096, argv[1]);

	//TCHAR sys_path[4096] = {0};
	//_tcscpy_s(sys_path, 4096, argv[2]);

	//// 
	//SC_HANDLE sc_handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	//if (sc_handle == NULL)
	//{
	//	int errCode = GetLastError();
	//	std::cout<<"OpenSCManager failed . errCode : "<<errCode<<std::endl;
	//	return errCode;
	//}

	//// 检查驱动服务是否存在
	//// 如果存在，就直接启动驱动
	//// 如果不存在，则创建服务后启动
	//SC_HANDLE service_handle = OpenService(sc_handle, service_name, SERVER_ALL_ACCESS);
	//if (service_handle == NULL)
	//{
	//	int errCode = GetLastError();
	//	if (errCode == ERROR_SERVICE_DOES_NOT_EXIST)
	//	{
	//		// 创建服务
	//		service_handle = CreateService(sc_handle, service_name, service_name, SERVER_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, sys_path, _T("load_group"), NULL, NULL, NULL, NULL);
	//		if (service_handle == NULL)
	//		{
	//			int errCode = GetLastError();
	//			std::cout<<"CreateService failed . errCode : "<<errCode<<std::endl;
	//			CloseServiceHandle(sc_handle);
	//			return errCode;
	//		}
	//	}
	//	else
	//	{
	//		std::cout<<"OpenService failed . errCode : "<<errCode<<std::endl;
	//		CloseServiceHandle(sc_handle);
	//		return errCode;
	//	}
	//}

	//BOOL b = StartService(service_handle, 0, NULL);
	//if (!b)
	//{
	//	int errCode = GetLastError();
	//	std::cout<<"StartService failed . errCode : "<<errCode<<std::endl;
	//	CloseServiceHandle(sc_handle);
	//	return errCode;
	//}

	return 0;
}

