/**
 * @file test_gpio.c
 * @brief GPIO 抽象层单元测试
 *        Unit tests for GPIO HAL
 *
 * 使用轻量级宏断言，无需外部测试框架。
 * Uses lightweight macro assertions without external test framework.
 *
 * 编译并运行 / Build and run:
 *   cc -I../include ../src/gpio.c test_gpio.c -o test_gpio && ./test_gpio
 */

#include <stdio.h>
#include <stdbool.h>
#include "gpio.h"

/* ------------------------------------------------------------------ */
/*  最简断言宏 / Minimal assertion macro                               */
/* ------------------------------------------------------------------ */
static int s_pass = 0;
static int s_fail = 0;

#define ASSERT(cond, msg)                                           \
    do {                                                            \
        if (cond) {                                                 \
            printf("[PASS] %s\n", (msg));                          \
            s_pass++;                                               \
        } else {                                                    \
            printf("[FAIL] %s  (line %d)\n", (msg), __LINE__);     \
            s_fail++;                                               \
        }                                                           \
    } while (0)

/* ------------------------------------------------------------------ */
/*  测试用例 / Test cases                                               */
/* ------------------------------------------------------------------ */

static void test_gpio_init_output(void)
{
    gpio_config_t cfg = {
        .pin           = 5U,
        .direction     = GPIO_DIR_OUTPUT,
        .pull          = GPIO_PULL_NONE,
        .initial_state = false
    };
    error_code_t err = gpio_init(&cfg);
    ASSERT(err == ERR_OK, "gpio_init output pin returns ERR_OK");
}

static void test_gpio_init_input(void)
{
    gpio_config_t cfg = {
        .pin           = 6U,
        .direction     = GPIO_DIR_INPUT,
        .pull          = GPIO_PULL_UP,
        .initial_state = true
    };
    error_code_t err = gpio_init(&cfg);
    ASSERT(err == ERR_OK, "gpio_init input pin returns ERR_OK");
}

static void test_gpio_init_null(void)
{
    error_code_t err = gpio_init(NULL);
    ASSERT(err == ERR_INVALID, "gpio_init NULL config returns ERR_INVALID");
}

static void test_gpio_init_invalid_pin(void)
{
    gpio_config_t cfg = {
        .pin       = 255U,   /* out of range */
        .direction = GPIO_DIR_OUTPUT,
        .pull      = GPIO_PULL_NONE
    };
    error_code_t err = gpio_init(&cfg);
    ASSERT(err == ERR_INVALID, "gpio_init out-of-range pin returns ERR_INVALID");
}

static void test_gpio_write_and_read(void)
{
    const uint8_t pin = 7U;
    gpio_config_t cfg = {
        .pin           = pin,
        .direction     = GPIO_DIR_OUTPUT,
        .pull          = GPIO_PULL_NONE,
        .initial_state = false
    };
    gpio_init(&cfg);

    bool state = false;

    gpio_write(pin, true);
    gpio_read(pin, &state);
    ASSERT(state == true, "gpio_write HIGH then gpio_read returns true");

    gpio_write(pin, false);
    gpio_read(pin, &state);
    ASSERT(state == false, "gpio_write LOW then gpio_read returns false");
}

static void test_gpio_toggle(void)
{
    const uint8_t pin = 8U;
    gpio_config_t cfg = {
        .pin           = pin,
        .direction     = GPIO_DIR_OUTPUT,
        .pull          = GPIO_PULL_NONE,
        .initial_state = false
    };
    gpio_init(&cfg);

    bool state = false;

    gpio_toggle(pin);
    gpio_read(pin, &state);
    ASSERT(state == true, "gpio_toggle from LOW -> HIGH");

    gpio_toggle(pin);
    gpio_read(pin, &state);
    ASSERT(state == false, "gpio_toggle from HIGH -> LOW");
}

static void test_gpio_write_to_input_fails(void)
{
    const uint8_t pin = 9U;
    gpio_config_t cfg = {
        .pin       = pin,
        .direction = GPIO_DIR_INPUT,
        .pull      = GPIO_PULL_UP,
        .initial_state = true
    };
    gpio_init(&cfg);

    error_code_t err = gpio_write(pin, false);
    ASSERT(err == ERR_INVALID, "gpio_write to input pin returns ERR_INVALID");
}

static void test_gpio_read_null_state(void)
{
    const uint8_t pin = 10U;
    gpio_config_t cfg = {
        .pin       = pin,
        .direction = GPIO_DIR_INPUT,
        .pull      = GPIO_PULL_NONE,
        .initial_state = false
    };
    gpio_init(&cfg);

    error_code_t err = gpio_read(pin, NULL);
    ASSERT(err == ERR_INVALID, "gpio_read with NULL state pointer returns ERR_INVALID");
}

static void test_gpio_toggle_input_fails(void)
{
    const uint8_t pin = 11U;
    gpio_config_t cfg = {
        .pin       = pin,
        .direction = GPIO_DIR_INPUT,
        .pull      = GPIO_PULL_NONE,
        .initial_state = false
    };
    gpio_init(&cfg);

    error_code_t err = gpio_toggle(pin);
    ASSERT(err == ERR_INVALID, "gpio_toggle on input pin returns ERR_INVALID");
}

/* ------------------------------------------------------------------ */
/*  测试入口 / Test runner                                              */
/* ------------------------------------------------------------------ */
int main(void)
{
    printf("=== GPIO HAL Unit Tests ===\n\n");

    test_gpio_init_output();
    test_gpio_init_input();
    test_gpio_init_null();
    test_gpio_init_invalid_pin();
    test_gpio_write_and_read();
    test_gpio_toggle();
    test_gpio_write_to_input_fails();
    test_gpio_read_null_state();
    test_gpio_toggle_input_fails();

    printf("\n=== Results: %d passed, %d failed ===\n", s_pass, s_fail);
    return (s_fail == 0) ? 0 : 1;
}
