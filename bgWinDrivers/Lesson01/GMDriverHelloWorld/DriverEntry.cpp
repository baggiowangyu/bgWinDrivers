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
	KdPrint(("[GMDriverHelloWorld] Hello World !"));

	// �������������ж������
	// �����ڱ�ֹͣ��ʱ����ϵͳ�ں˵���ж������
	driver_object->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}

VOID DriverUnload(IN PDRIVER_OBJECT driver_object)
{

}