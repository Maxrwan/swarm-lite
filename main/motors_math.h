// motors_math.h - pure maths (no ESP-IDF), so we can test it on a PC.
#pragma once
#include <stdlib.h>
#include "config.h"

// speed is -100..100 (percent of the allowed maximum). Returns duty 0..cap.
static inline int motors_speed_to_duty(int speed)
{
    int mag = abs(speed);
    if (mag > 100) mag = 100;
    int cap = (MOTOR_DUTY_MAX * MOTOR_MAX_DUTY_PCT) / 100;
    return (mag * cap) / 100;
}
