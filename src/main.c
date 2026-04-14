/**
 * @file main.c
 * @brief 嵌入式项目主入口
 *        Embedded project main entry point
 *
 * 典型的嵌入式主循环结构：
 *   1. 硬件初始化
 *   2. 外设驱动初始化
 *   3. 进入超级循环 (super-loop)
 *
 * Typical embedded main loop structure:
 *   1. Hardware initialisation
 *   2. Peripheral driver initialisation
 *   3. Enter super-loop
 */

#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "gpio.h"

/* ------------------------------------------------------------------ */
/*  前向声明 / Forward declarations                                     */
/* ------------------------------------------------------------------ */
static error_code_t system_init(void);
static void         main_loop(void);

/* ------------------------------------------------------------------ */
/*  系统初始化 / System initialisation                                  */
/* ------------------------------------------------------------------ */
static error_code_t system_init(void)
{
    error_code_t err;

    /* 配置状态 LED 为推挽输出，初始低电平 */
    const gpio_config_t led_status_cfg = {
        .pin           = LED_STATUS_PIN,
        .direction     = GPIO_DIR_OUTPUT,
        .pull          = GPIO_PULL_NONE,
        .initial_state = false
    };
    err = gpio_init(&led_status_cfg);
    if (err != ERR_OK) {
        return err;
    }

    /* 配置错误 LED 为推挽输出，初始低电平 */
    const gpio_config_t led_error_cfg = {
        .pin           = LED_ERROR_PIN,
        .direction     = GPIO_DIR_OUTPUT,
        .pull          = GPIO_PULL_NONE,
        .initial_state = false
    };
    err = gpio_init(&led_error_cfg);
    if (err != ERR_OK) {
        return err;
    }

    /* 配置用户按键为输入，上拉 */
    const gpio_config_t btn_cfg = {
        .pin           = BTN_USER_PIN,
        .direction     = GPIO_DIR_INPUT,
        .pull          = GPIO_PULL_UP,
        .initial_state = true
    };
    err = gpio_init(&btn_cfg);
    if (err != ERR_OK) {
        return err;
    }

    return ERR_OK;
}

/* ------------------------------------------------------------------ */
/*  主循环 / Main super-loop                                            */
/* ------------------------------------------------------------------ */
static void main_loop(void)
{
    bool btn_state = true;

    while (true) {
        /* 读取按键状态 */
        gpio_read(BTN_USER_PIN, &btn_state);

        if (!btn_state) {
            /* 按键按下（低有效）：点亮状态 LED */
            gpio_write(LED_STATUS_PIN, true);
        } else {
            /* 按键释放：翻转状态 LED（心跳指示） */
            gpio_toggle(LED_STATUS_PIN);
        }

        /*
         * 在真实硬件上，此处应调用系统延时函数，例如：
         * hal_delay_ms(SYS_TICK_PERIOD_MS);
         *
         * On real hardware, insert a system delay here, e.g.:
         * hal_delay_ms(SYS_TICK_PERIOD_MS);
         */

        /* 在主机仿真时退出循环以便测试 */
#ifndef EMBEDDED_TARGET
        break;
#endif
    }
}

/* ------------------------------------------------------------------ */
/*  程序入口 / Program entry point                                      */
/* ------------------------------------------------------------------ */
int main(void)
{
    error_code_t err = system_init();
    if (err != ERR_OK) {
        /* 初始化失败：点亮错误 LED */
        gpio_write(LED_ERROR_PIN, true);
        /*
         * 在真实硬件上，应在 system_init() 中配置并启动看门狗定时器，
         * 使系统在此处自动复位。
         * On real hardware, configure and start a watchdog timer inside
         * system_init() so the device resets automatically at this point.
         */
        while (true) { /* 等待看门狗复位 / spin waiting for watchdog */ }
    }

    main_loop();

    return 0;
}
