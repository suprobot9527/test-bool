# 嵌入式项目 / Embedded Project

> **test-bool** — 一个面向嵌入式系统的轻量级 C 参考项目。  
> A lightweight embedded-systems reference project written in C.

---

## 目录结构 / Project structure

```
test-bool/
├── CMakeLists.txt        # CMake 构建脚本 / CMake build script
├── include/
│   ├── config.h          # 全局配置与错误码 / Global config & error codes
│   └── gpio.h            # GPIO HAL 头文件 / GPIO HAL header
├── src/
│   ├── main.c            # 主程序入口 / Main entry point
│   └── gpio.c            # GPIO HAL 实现 / GPIO HAL implementation
├── drivers/              # 可扩展驱动目录 / Extensible driver directory
└── tests/
    └── test_gpio.c       # GPIO 单元测试 / GPIO unit tests
```

---

## 快速开始 / Quick start

### 依赖 / Prerequisites

| 工具 | 最低版本 |
|------|---------|
| CMake | 3.16 |
| GCC / Clang | 任意 C11 编译器 |

### 主机构建与测试 / Build & test on host

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cd build && ctest --output-on-failure
```

### 嵌入式目标交叉编译 / Cross-compile for embedded target

将工具链文件传递给 CMake，例如针对 ARM Cortex-M：

```bash
cmake -B build \
      -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-none-eabi.cmake \
      -DCMAKE_BUILD_TYPE=MinSizeRel \
      -DEMBEDDED_TARGET=1
cmake --build build
```

> 在真实硬件平台上，请将 `src/gpio.c` 中的模拟实现替换为对应的  
> 寄存器操作或 HAL 库调用。  
> On real hardware, replace the stub in `src/gpio.c` with the  
> appropriate register-level or HAL library calls.

---

## 模块说明 / Module overview

### `include/config.h`
项目全局宏定义：系统时钟、波特率、引脚编号、错误码枚举。

### `include/gpio.h` / `src/gpio.c`
与平台无关的 GPIO 抽象层，提供：
- `gpio_init` — 初始化引脚方向与上下拉  
- `gpio_write` — 设置输出电平  
- `gpio_read` — 读取输入/输出电平  
- `gpio_toggle` — 翻转输出电平  

### `src/main.c`
典型嵌入式超级循环：硬件初始化 → 外设初始化 → `while(true)` 主循环。

### `tests/test_gpio.c`
GPIO HAL 单元测试，覆盖正常路径与错误路径（无需外部测试框架）。

---

## 许可证 / License

MIT
