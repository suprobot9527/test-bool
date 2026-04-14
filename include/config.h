/**
 * @file config.h
 * @brief 项目全局配置头文件
 *        Project global configuration header
 */

#ifndef CONFIG_H
#define CONFIG_H

/* 系统时钟频率 (Hz) / System clock frequency (Hz) */
#define SYS_CLK_FREQ        72000000UL

/* 系统心跳定时器周期 (ms) / System tick period (ms) */
#define SYS_TICK_PERIOD_MS  1U

/* 调试串口波特率 / Debug UART baud rate */
#define DEBUG_UART_BAUDRATE 115200U

/* 版本信息 / Version info */
#define FW_VERSION_MAJOR    1
#define FW_VERSION_MINOR    0
#define FW_VERSION_PATCH    0

/**
 * 版本号用法示例 / Version usage example:
 *   printf("FW v%d.%d.%d\n",
 *          FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_PATCH);
 * 或者通过调试串口在系统初始化时打印版本号。
 * Or print via debug UART during system_init().
 */

/* GPIO 引脚定义 / GPIO pin definitions */
#define LED_STATUS_PIN      13U
#define LED_ERROR_PIN       14U
#define BTN_USER_PIN        0U

/* 布尔类型定义 / Boolean type definitions */
#ifndef __cplusplus
#include <stdbool.h>
#endif

/* 错误码 / Error codes */
typedef enum {
    ERR_OK       = 0,
    ERR_TIMEOUT  = 1,
    ERR_INVALID  = 2,
    ERR_BUSY     = 3,
    ERR_OVERFLOW = 4
} error_code_t;

#endif /* CONFIG_H */
