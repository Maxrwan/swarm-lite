#pragma once
#include <stdint.h>
#include "config.h"

// Call once at startup.
void line_sensor_init(void);

// Reads all sensors once (takes up to LINE_TIMEOUT_US microseconds).
// out[i] = how long sensor i took to discharge, in microseconds.
//   small number = bright surface (floor)    large number = dark surface (tape)
// A value equal to LINE_TIMEOUT_US means the sensor never finished: very dark, or not connected.
void line_sensor_read_raw(uint16_t out[LINE_SENSOR_COUNT]);
