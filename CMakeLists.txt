cmake_minimum_required(VERSION 3.16)
project(test-bool C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------
# 编译选项 / Compiler options
# -----------------------------------------------------------------------
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -Wundef
    )
endif()

# -----------------------------------------------------------------------
# 包含路径 / Include directories
# -----------------------------------------------------------------------
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

# -----------------------------------------------------------------------
# 驱动库 / Driver library
# -----------------------------------------------------------------------
add_library(drivers STATIC
    src/gpio.c
)
target_include_directories(drivers PUBLIC ${INC_DIR})

# -----------------------------------------------------------------------
# 主固件可执行文件 / Main firmware executable
# 定义 EMBEDDED_TARGET 以启用无限超级循环。
# Define EMBEDDED_TARGET to enable the infinite super-loop.
# -----------------------------------------------------------------------
add_executable(firmware
    src/main.c
)
target_include_directories(firmware PRIVATE ${INC_DIR})
target_link_libraries(firmware PRIVATE drivers)

# -----------------------------------------------------------------------
# 单元测试 / Unit tests
# -----------------------------------------------------------------------
enable_testing()

add_executable(test_gpio
    tests/test_gpio.c
    src/gpio.c
)
target_include_directories(test_gpio PRIVATE ${INC_DIR})

add_test(NAME gpio_hal_tests COMMAND test_gpio)
