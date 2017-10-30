# 国迈科技驱动开发从入门到放弃 #

## 第二课：NT式驱动程序 ##

### 什么是NT式驱动程序 ###
- NT式驱动是一种不支持热拔插技术的驱动程序
 
### NT式驱动的基本结构 ###
- 驱动入口例程
	- 驱动在启动的时候，此接口被操作系统内核调用；
	- 驱动入口例程定义如下：```typedef NTSTATUS (__stdcall * _DriverEntry)(IN PDRIVER_OBJECT driver_object, IN PUNICODE_STRING registry_path);```
		- driver_object：[输入参数] 由操作系统传入，驱动程序对象
		- registry_path：[输入参数] 由操作系统传入，驱动注册表路径
			- 一般内容为：**```\REGISTRY\MACHINE\SYSTEM\ControlSet\Service\[服务名]```**
	- 在驱动程序入口例程一般要进行下面几项工作：
		- 设置驱动卸载例程；
		- 设置驱动各IRP派遣例程，IRP是什么，在第四课详细讲解；
		- 创建设备驱动对象；
		- 创建驱动对象的符号链接；
- 驱动卸载例程
	- 驱动程序在卸载时被操作系统内核调用；
	- 驱动卸载例程定义如下：```VOID (__stdcall * _DriverUnload)(IN PDRIVER_OBJECT driver_object);```
		- driver_object：[输入参数] 由操作系统传入，驱动程序对象
	- 在驱动程序卸载例程一般要进行下面几项工作：
		- 停止内核线程工作；
		- 清理链表，释放内存；
		- 清理自行申请的各种对象、结构体的内存；
		- 遍历设备对象栈，删除符号链接，删除设备对象；
	- 如果驱动程序卸载例程中有没有清理干净的资源，会导致在系统重启之前，无法再次启动驱动程序；
- IRP派遣例程
	- 略；