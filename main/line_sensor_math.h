// line_sensor_math.h - pure maths (no ESP-IDF), so we can test it on a PC.
#pragma once
#include <stdint.h>
#include "config.h"

// Where is the line under the sensor array?
//
// dark[i] = darkness of sensor i: 0 (bright floor) .. 1000 (black tape).
//
// Returns a position where each sensor is worth 1000:
//      0 = line exactly under sensor 1
//   1000 = under sensor 2 ...   7000 = under sensor 8 (with 8 sensors)
//   3500 = centred (halfway between sensors 4 and 5)
// Returns -1 if no sensor sees the line.
//
// Method: a weighted average. Each sensor "votes" for its own place (i * 1000),
// and darker sensors get a bigger vote. Two sensors half on the tape pull the
// answer to the point between them, so we get finer steps than 8 positions.
static inline int line_position(const uint16_t dark[], int count)
{
    long weighted_sum = 0;
    long total = 0;
    int  seen = 0;

    for (int i = 0; i < count; i++) {
        if (dark[i] >= LINE_SEEN_MIN) seen = 1;
        if (dark[i] > LINE_NOISE_MAX) {
            weighted_sum += (long)dark[i] * (i * 1000);
            total        += dark[i];
        }
    }
    if (!seen) return -1;
    return (int)(weighted_sum / total);
}
