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

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, IN PUNICODE_STRING  registry_path)
{
	// 这是一个条件打印函数，只在Debug版打印，Release自动被屏蔽
	KdPrint(("Hello World !"));

	// 设置驱动对象的卸载例程
	// 驱动在被停止的时候由系统内核调用卸载例程
	driver_object->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}

VOID DriverUnload(PDRIVER_OBJECT driver_object)
{

}