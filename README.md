# NCHU Cockpit Panel - Boeing 737-800 / 727-200F 仪表模拟

波音 737-800 与 727-200F 驾驶舱仪表桌面模拟器。基于 EGE 图形库渲染，通过 UDP (XPlaneConnect) 从 X-Plane 飞行模拟器实时接收飞行数据，驱动全套驾驶舱仪表显示。

> 南昌航空大学 软件学院 232019班

## 功能特性

- **六机械仪表**：姿态仪 (AI)、空速表 (ASI)、高度表 (ALT)、航向罗盘、垂直速率表 (RCDI)、电磁指示仪 (RMI)
- **电子仪表**：PFD 主飞行显示器、ND 导航显示器、EICAS 发动机指示、备用仪表、计时器
- **FMC 飞行管理计算机**：9 个页面，支持航路输入与导航
- **MCP 控制板**：自动驾驶模式、速度/航向/高度旋钮、EFIS 控制、灯光控制
- **双向通信**：读取 X-Plane 飞行数据，回传操纵杆/油门/起落架/襟翼等控制指令
- **地图集成**：高德卫星地图 + 逆地理编码 + 实时天气信息
- **多进程架构**：PFD / ND / EICAS / FMC / Map 各自独立子进程，通过共享内存通信
<img width="600" alt="8102c980424630198eb11a0fa3cf7393" src="https://github.com/user-attachments/assets/bda5839e-9135-4ae8-83a8-8fd5ba52c2b9" />
<img width="600" alt="e818554c972833ea0750cb4877b4f646" src="https://github.com/user-attachments/assets/9dcf5bb0-4b5c-478b-90ed-d3c67940126d" />



## 项目结构

```
├── src/                        # 主程序源码
│   ├── core/                   # 入口 main.cpp、全局结构体、全局变量
│   ├── communication/          # X-Plane UDP 通信、地图 API、XPlaneConnect
│   ├── instruments/
│   │   ├── mechanical/         # 六大机械仪表
│   │   ├── pfd/                # 主飞行显示器
│   │   ├── nd/                 # 导航显示器
│   │   ├── eicas/              # 发动机指示
│   │   ├── fmc/                # 飞行管理计算机 (9 页面)
│   │   └── standby/            # 备用仪表与计时器
│   ├── panels/                 # MCP / EFIS / 灯光 / 背景面板
│   ├── display/                # 子进程管理 (共享内存 IPC)
│   ├── utility/                # 文件读取、键盘控制、窗口管理
│   └── external/               # 边框、螺丝、灯光效果
├── subprocess/                 # 独立子进程项目
│   ├── PFD/  ├── ND/  ├── MFD1/  ├── MFD2/  ├── FMC/  └── Map/
├── res/                        # PNG 贴图资源 (面板、旋钮、指示灯)
├── data/                       # 导航数据、飞行计划、配置文件
├── CMakeLists.txt              # CMake 构建配置
└── Makefile                    # MinGW Makefile (小熊猫 C++ 兼容)
```

## 构建

### 依赖

- **编译器**：MinGW-w64 GCC 8.1+ (64-bit)
- **EGE 图形库**：Easy Graphics Engine
- **cURL**：用于地图与天气 API 请求

### CMake

```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### Make (小熊猫 C++)

在小熊猫 C++ IDE 中打开 `Makefile` 或项目文件直接编译。

## 配置

编辑 `data/Panels simulation.ini`：

```ini
[UDP settings]
UDP transmission = 1        # 1 启用 X-Plane 数据，0 本地模拟
IP address = 10.83.8.12     # X-Plane 所在机器 IP
UDP port = 49001             # XPlaneConnect 监听端口
```

## 操作

| 按键 | 功能 |
|------|------|
| 回车 | 切换机械/电子仪表 |
| M / P / N / E / R / F | 地图 / PFD / ND / EICAS / EICAS2 / FMC 窗口 |
| Q | 起落架收放 |
| 数字键盘 +/-/* | 油门 / 襟翼 / 刹车 |
| 3 / 4 | 亮度调节 |
| 鼠标拖拽 | 移动仪表 |
| 双击 | 全屏单仪表 |
| Ctrl+滚轮 | 缩放 |

## 许可

XPlaneConnect 库 (xplaneConnect.c/h) 版权归 NASA 所有，按原许可分发。
