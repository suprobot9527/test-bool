/**
 * @file gpio.h
 * @brief GPIO 抽象层头文件
 *        GPIO Hardware Abstraction Layer header
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>
#include "config.h"

/**
 * @brief GPIO 方向 / GPIO direction
 */
typedef enum {
    GPIO_DIR_INPUT  = 0,
    GPIO_DIR_OUTPUT = 1
} gpio_dir_t;

/**
 * @brief GPIO 上下拉配置 / GPIO pull configuration
 */
typedef enum {
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP   = 1,
    GPIO_PULL_DOWN = 2
} gpio_pull_t;

/**
 * @brief GPIO 引脚配置结构体 / GPIO pin configuration struct
 */
typedef struct {
    uint8_t     pin;
    gpio_dir_t  direction;
    gpio_pull_t pull;
    bool        initial_state;
} gpio_config_t;

/**
 * @brief 初始化 GPIO 引脚 / Initialize a GPIO pin
 * @param config  指向配置结构体的指针 / Pointer to configuration struct
 * @return ERR_OK on success, error code otherwise
 */
error_code_t gpio_init(const gpio_config_t *config);

/**
 * @brief 设置 GPIO 输出电平 / Set GPIO output level
 * @param pin    引脚编号 / Pin number
 * @param state  true = 高电平, false = 低电平 / true = HIGH, false = LOW
 * @return ERR_OK on success, error code otherwise
 */
error_code_t gpio_write(uint8_t pin, bool state);

/**
 * @brief 读取 GPIO 输入电平 / Read GPIO input level
 * @param pin    引脚编号 / Pin number
 * @param state  指向存储结果的布尔变量 / Pointer to store result
 * @return ERR_OK on success, error code otherwise
 */
error_code_t gpio_read(uint8_t pin, bool *state);

/**
 * @brief 翻转 GPIO 输出电平 / Toggle GPIO output level
 * @param pin    引脚编号 / Pin number
 * @return ERR_OK on success, error code otherwise
 */
error_code_t gpio_toggle(uint8_t pin);

#endif /* GPIO_H */
