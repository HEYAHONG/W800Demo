# 说明

这是一个使用[W800](https://www.winnermicro.com/html/1/156/158/558.html)开发的Demo（仅供测试）。没有使用固件加密功能。
## 源代码下载

由于本源代码包含第三方源代码,故直接下载可能有部分源代码缺失，需要通过以下方法解决:

- 在进行git clone 使用--recurse-submodules参数。

- 若已通过git clone下载,则在源代码目录中执行以下命令下载子模块:

  ```bash
   git submodule update --init --recursive
  ```

# 编译

## 工具

- gcc:用于编译wm_tool,windows平台不需要。
- csky-elfabiv2-tools :工具链，C运行库为minilibc，需要到[平头哥开放社区下载](https://occ.t-head.cn/community/download) ，下载时需要根据系统情况下载800系列工具链，mingw为windows版本（x86与x86_64通用），下载完成后解压后再将对应bin目录添加至PATH变量即可完成安装。
- cmake :生成工程文件。
- make :执行编译，也可使用其它工具(如ninja)。


注意：[官方环境](https://www.winnermicro.com/upload/1/editor/1592032027265.rar)为windows下的环境，安装后即可使用官方的方式（直接使用make）在官方SDK中开发，只需要再安装cmake即可使用cmake生成各种工程（方便编辑）并开发。

## 步骤

在Windows下需要使用MSYS2的Mingw32/mingw64终端,在Linux下需要使用终端。

- 进入源代码目录，创建构建目录并进入。

```bash
mkdir build 
cd build
```

- 使用CMake生成工程文件。

```bash
cmake ../
```



- 根据上一步生成的工程文件使用对应工具（如make）执行编译。

```bash
#Linux下执行make
make
#MINGW32/MINGW64下执行mingw32-make
mingw32-make
```

编译完成即可在构建目录得到镜像文件。



## 烧录

如需使用烧录，需要在使用CMake生成工程文件前设置WM_PORT变量,该变量用于指示烧录的串口(在Windows下为COMn，在linux下通常为ttyUSBn，n为数字，具体值需要在连接好硬件后通过设备管理器(Windows)或者dmesg(Linux)确定)。在终端下可使用以下命令设置WM_PORT环境变量：

```bash
export WM_PORT=实际串口
```

如设置成功,则编译完成后可执行以下烧录命令(Linux下可能要使用sudo):

```bash
#Linux下执行make
make flash
#MINGW32/MINGW64下执行mingw32-make
mingw32-make flash
```

烧录过程中需要手动重启硬件两次，根据烧录程序的提示操作。

# 其他说明

wm_sdk_w800目录为官方公开的SDK，版本为[wm_sdk_w800_20210730](https://www.winnermicro.com/upload/1/editor/1628068843962.rar)

