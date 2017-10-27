# 国迈科技驱动开发从入门到放弃 #

## 第一课：Hello World ##

### 1.如何搭建开发环境 ###
- 安装 Visual Studio 2008 SP1
- 安装 Windows WDK 7
	- 安装时全部安装，内置Windbg调试器
	- 例如：安装到D盘，WDK路径会变为```D:\WinDDK\7600.16385.1```
- 在系统中配置环境变量
	- 环境变量名称：```WDKROOT```
	- 环境变量值：```D:\WinDDK\7600.16385.1```
- 在 Visual Studio 2008 SP1 中配置路径：
	- 在Visual Studio 2008菜单的 **```工具```** -> **```选项```** 中找到 **```项目和解决方案```** -> **```VC++目录```** ;
	- 在 **```Win32```** 平台下，选择 **```包含文件```** ;
	- 添加三个路径：
		- **```$(WDKROOT)\inc\api```** ;
		- **```$(WDKROOT)\inc\ddk```** ;
		- **```$(WDKROOT)\inc\crt```** ;
	- 将上面三个路径的优先级调整到最前面；
	- 将 **```包含文件```** 修改为 **```库文件```**；
	- 添加四个路径：
		- **```$(WDKROOT)\lib\wxp\i386```** ;
		- **```$(WDKROOT)\lib\Crt\i386```** ;
		- **```$(WDKROOT)\lib\ATL\i386```** ;
		- **```$(WDKROOT)\lib\Mfc\i386```** ;
	- 将上面四个路径的优先级调整到最前面；
	
### 2.如何搭建调试环境 ###
- 安装VMWare Workstations 12
- 在VMware 12内创建虚拟机，并添加一个串口设备：
	- 串口设备参数如下：
		- 连接：使用命名的管道
		- 命名管道名称：**```\\.\pipe\com_1```**
		- 第一个下拉菜单：**```该端是服务器。```**
		- 第二个下拉菜单：**```另一端是应用程序。```**
	- 设备状态：
		- 勾选：**```启动时连接```**
- 在虚拟机内安装Windows XP SP3系统
- 修改Windows XP SP3的启动属性
	- 打开C盘下的boot.ini文件，将下面的文本加到最后一行：**```multi(0)disk(0)rdisk(0)partition(1)\WINDOWS="Microsoft Windows XP Professional" /noexecute=optin /fastdetect /debug /debugport=com1 /baudrate=115200```**
- 虚拟机启动时选择[启动调试环境]的选项即可进入Windows系统调试模式
- 在开发系统下，创建Windbg的桌面快捷方式
	- 在快捷方式的 **```属性```** 中，**```目标```** 栏内追加写入： **```-b -k com:port=\\.\pipe\\com_1,baud=115200,pipe```**
- 最后，设置Windbg的调试符号表（PDB文件）
	- Windows系统符号表：
		- 在微软官方网站下载各系统符号表
			- 网站地址：[https://developer.microsoft.com/en-us/windows/hardware/download-symbols](https://developer.microsoft.com/en-us/windows/hardware/download-symbols "https://developer.microsoft.com/en-us/windows/hardware/download-symbols")；
			- 下载好后进行符号安装；
			- 最后将安装路径填入Windbg的**```Symbo Search Path```**对话框中;
		- 在微软符号服务器自动下载调试过程中所需的符号表
			- 配置方法：**```SRV*E:\symbols\websymbo*http://msdl.microsoft.com/download/symbols;```**；
			- 配置说明：
				- **```SRV```**：前缀，表示我们要从符号服务器自动下载；
				- **```E:\symbols\websymbo```**：表示下载好的符号文件存放路径；
				- **```http://msdl.microsoft.com/download/symbols```**：表示微软符号服务器地址；
	- 我们自行开发的驱动符号表：
		- 将我们驱动匹配的PDB文件所在目录填入Windbg的**```Symbo Search Path```**对话框中;