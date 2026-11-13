#include "line_sensor.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"

// How one QTR-8RC sensor works: each output has a tiny capacitor.
//   1. We drive the pin HIGH for a moment  -> the capacitor charges.
//   2. We switch the pin to INPUT          -> the capacitor drains through a light-sensitive part.
//   3. We time how long the pin stays HIGH -> more reflected light = faster drain = shorter time.
// So the "reading" is a time, not a voltage. That is why any digital pin works.

static const gpio_num_t s_pins[LINE_SENSOR_COUNT] = LINE_SENSOR_GPIOS;

void line_sensor_init(void)
{
    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        gpio_config_t c = {
            .pin_bit_mask = 1ULL << s_pins[i],
            .mode         = GPIO_MODE_OUTPUT,
            .pull_up_en   = GPIO_PULLUP_DISABLE,   // a pull-up would fight the capacitor draining
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type    = GPIO_INTR_DISABLE,
        };
        ESP_ERROR_CHECK(gpio_config(&c));
        gpio_set_level(s_pins[i], 1);
    }
}

void line_sensor_read_raw(uint16_t out[LINE_SENSOR_COUNT])
{
    // 1. Charge all the capacitors.
    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        gpio_set_direction(s_pins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(s_pins[i], 1);
    }
    esp_rom_delay_us(LINE_CHARGE_US);

    // 2. Let go of the pins. Assume "timed out" until we see each one drop.
    for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
        out[i] = LINE_TIMEOUT_US;
        gpio_set_direction(s_pins[i], GPIO_MODE_INPUT);
    }

    // 3. Watch all pins together and note the moment each one goes LOW.
    int64_t start = esp_timer_get_time();
    int waiting = LINE_SENSOR_COUNT;
    while (waiting > 0) {
        int64_t elapsed = esp_timer_get_time() - start;
        if (elapsed >= LINE_TIMEOUT_US) break;
        for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
            if (out[i] == LINE_TIMEOUT_US && gpio_get_level(s_pins[i]) == 0) {
                out[i] = (uint16_t)elapsed;
                waiting--;
            }
        }
    }
}
