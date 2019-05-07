/**
 * @brief 蓝牙主机驱动
 * 
 * @file host_driver.c
 * @author Jim Jiang
 * @date 2019-05-07
 */
#include "keyboard_host_driver.h"
#include <stdint.h>

#include "../ble/ble_hid_service.h"
#include "custom_hook.h"

uint8_t keyboard_leds(void);
void send_keyboard(report_keyboard_t* report);
void send_mouse(report_mouse_t* report);
void send_system(uint16_t data);
void send_consumer(uint16_t data);

host_driver_t driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};

static uint8_t keyboard_leds()
{
    return keyboard_led_val;
}

static void send_keyboard(report_keyboard_t* report)
{
    keys_send(0, KEYBOARD_REPORT_SIZE, report->raw);
    hook_send_keyboard(report);
}

static void send_mouse(report_mouse_t* report)
{
    // unsupport, and will not support in future.
}

static void send_system(uint16_t data)
{
    keys_send(1, 2, (uint8_t*)&data);
}

static void send_consumer(uint16_t data)
{
    keys_send(0, 2, (uint8_t*)&data);
}