/**
 * @file gpio.c
 * @brief GPIO 抽象层实现
 *        GPIO Hardware Abstraction Layer implementation
 *
 * 本文件提供与平台无关的 GPIO 操作接口。
 * 在实际硬件平台上使用时，请将下方的模拟实现替换为对应的
 * 寄存器/HAL 库操作。
 *
 * This file provides a platform-independent GPIO interface.
 * When targeting real hardware, replace the stub implementations
 * below with the appropriate register-level or HAL library calls.
 */

#include "gpio.h"
#include <stddef.h>

/* ---- 平台模拟层 (stub) ---- */
/* 使用一个静态数组模拟 GPIO 引脚状态，共支持 32 个引脚 */
#define GPIO_MAX_PINS 32U

static bool  s_pin_state[GPIO_MAX_PINS]       = { false };
static bool  s_pin_initialized[GPIO_MAX_PINS] = { false };
static gpio_dir_t s_pin_dir[GPIO_MAX_PINS]    = { GPIO_DIR_INPUT };

/* ------------------------------------------------------------------ */

error_code_t gpio_init(const gpio_config_t *config)
{
    if (config == NULL) {
        return ERR_INVALID;
    }
    if (config->pin >= GPIO_MAX_PINS) {
        return ERR_INVALID;
    }

    s_pin_dir[config->pin]         = config->direction;
    s_pin_state[config->pin]       = config->initial_state;
    s_pin_initialized[config->pin] = true;

    return ERR_OK;
}

error_code_t gpio_write(uint8_t pin, bool state)
{
    if (pin >= GPIO_MAX_PINS) {
        return ERR_INVALID;
    }
    if (!s_pin_initialized[pin]) {
        return ERR_INVALID;
    }
    if (s_pin_dir[pin] != GPIO_DIR_OUTPUT) {
        return ERR_INVALID;
    }

    s_pin_state[pin] = state;
    return ERR_OK;
}

error_code_t gpio_read(uint8_t pin, bool *state)
{
    if (pin >= GPIO_MAX_PINS || state == NULL) {
        return ERR_INVALID;
    }
    if (!s_pin_initialized[pin]) {
        return ERR_INVALID;
    }

    *state = s_pin_state[pin];
    return ERR_OK;
}

error_code_t gpio_toggle(uint8_t pin)
{
    if (pin >= GPIO_MAX_PINS) {
        return ERR_INVALID;
    }
    if (!s_pin_initialized[pin]) {
        return ERR_INVALID;
    }
    if (s_pin_dir[pin] != GPIO_DIR_OUTPUT) {
        return ERR_INVALID;
    }

    s_pin_state[pin] = !s_pin_state[pin];
    return ERR_OK;
}
