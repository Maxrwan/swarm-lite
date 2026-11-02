// STEP 3 hardware test (use as main.c temporarily): wheels OFF THE GROUND / robot on a stand!
#include "motors.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    motors_init();
    while (1) {
        motors_set(50, 50);   vTaskDelay(pdMS_TO_TICKS(2000)); // both forward, half of capped max
        motors_stop();        vTaskDelay(pdMS_TO_TICKS(1000));
        motors_set(-50, -50); vTaskDelay(pdMS_TO_TICKS(2000)); // both reverse
        motors_stop();        vTaskDelay(pdMS_TO_TICKS(1000));
        motors_set(50, -50);  vTaskDelay(pdMS_TO_TICKS(2000)); // spin in place
        motors_stop();        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
