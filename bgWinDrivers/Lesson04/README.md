# 国迈科技驱动开发从入门到放弃 #

## 第四课：驱动程序中的IRP ##

### 1. 什么是IRP ###
- IRP（I/O Request Package），即输入输出请求包；
- 它是与输入输出相关的重要数据结构；
- IRP的定义在wdm.h文件中；
- IRP中有两个基本属性，**```MajorFunction```** 和 **```MinorFunction```**
	- MajorFunction：定义IO操作是哪种主类型，将其派发到对应的派遣函数中进行处理；
	- MinorFunction：定义IO操作是哪种子类型，派发函数内部根据子类型可以做进一步处理；

### 2. IRP类型 ###
|IRP类型|说明|
|------|----|
|IRP_MJ_CREATE|创建，CreateFile、NtCreateFile、ZwCreateFile调用时会产生这种IRP|
|IRP_MJ_CLEANUP|清理，CloseHandle、NtClose、ZwClose调用时会产生这种IRP|
|IRP_MJ_CLOSE|关闭，CloseHandle、NtClose、ZwClose调用，关掉该对象的最后一个引用的时候，会产生这种IRP|
|IRP_MJ_DEVICE_CONTROL|设备控制，DeviceIoControl被调用的时候会产生这种IRP|
|IRP_MJ_POWER|操作系统处理电源消息时产生这种IRP|
|IRP_MJ_PNP|即插即用，NT式驱动不支持，WDM驱动可以支持|
|IRP_MJ_QUERY_INFORMATION|查询信息，调用GetFileSize等类似的API时会产生这种IRP|
|IRP_MJ_READ|读，ReadFile、NtReadFile、ZwReadFile调用时产生这种IRP|
|IRP_MJ_WRITE|写，WriteFile、NtWriteFile、ZwWriteFile调用时产生此种IRP|
|IRP_MJ_SET_INFORMATION|设置信息，设置文件信息，或删除文件时会产生这种IRP|
|IRP_MJ_SHUTDOWN|系统关机前产生此消息|

