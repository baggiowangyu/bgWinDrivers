# 国迈科技驱动开发从入门到放弃 #

## 第一课：Hello World ##

### 1.如何搭建开发环境 ###
- 安装 Visual Studio 2008 SP1
- 安装 Windows WDK 7
	- 下载地址：[https://download.microsoft.com/download/4/A/2/4A25C7D5-EFBE-4182-B6A9-AE6850409A78/GRMWDK_EN_7600_1.ISO](https://download.microsoft.com/download/4/A/2/4A25C7D5-EFBE-4182-B6A9-AE6850409A78/GRMWDK_EN_7600_1.ISO "https://download.microsoft.com/download/4/A/2/4A25C7D5-EFBE-4182-B6A9-AE6850409A78/GRMWDK_EN_7600_1.ISO")；
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

### 3.如何安装驱动 ###
- 将我们编译好的驱动程序拷贝到**```C:\Windows\System32\drivers\```**目录下；
- 运行项目中的工具**```srvman.exe```**
- 点击**```Add service```**按钮，填写下面内容：
	- **```Internal service name```**：填写我们期望的名称；
	- **```User-visible name```**：填写我们期望的名称；
	- **```Binary file path (Win32)```**：点击**```...```**按钮，找到我们的驱动文件，选择；
	- **```Binary path (raw)```**：上面的字段选中后自动填写，这一段会写入注册表；
	- **```Service type```**：这是服务类型，有下面几个选项：
		- **```Filesystem driver```**：文件系统驱动；
		- **```Device driver```**：设备驱动，【我们选这个】；
		- **```Win32 own process```**：基本不用；
		- **```Win32 shared process```**：基本不用；
		- **```Win32 program as service via SrvMan```**：基本不用；
	- **```Start mode```**：这是启动类型，有下面几个选项：
		- **```Auto```**：自动模式，Service Control Manager模块启动的时候，驱动被加载并启动；
		- **```Boot```**：引导模式，当系统被引导加载的时候，驱动被加载并启动；
		- **```Manual```**：手动模式，当我们调用```StartService()```或使用```net start```命令时，驱动被加载并启动；
		- **```Disabled```**：驱动被禁用；
		- **```System```**：系统模式，当系统调用```IoInitSystem()```的时候，驱动被加载并启动；
	- **```Load order group```**：随便填；
- 服务被添加后，在服务列表找到该服务，点击```Start service```，驱动就会被加载启动了；

### 4.如何调试驱动 ###