// TEMPORARY main: line sensor test (copied from tools/line_test_main.c).
// Prints the 8 raw readings once a second. Small = bright floor, large = dark tape.
#include <stdio.h>
#include "line_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    uint16_t raw[LINE_SENSOR_COUNT];

    line_sensor_init();
    while (1) {
        line_sensor_read_raw(raw);
        for (int i = 0; i < LINE_SENSOR_COUNT; i++) {
            printf("%5u ", raw[i]);   // %5u = a number padded to 5 characters, so columns line up
        }
        printf("\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
