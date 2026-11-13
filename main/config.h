// config.h - every number that might change lives here.
// (The professor hasn't fixed robot size or distances, so never hard-code these elsewhere.)
#pragma once

// ---------- Motors (MX1508 driver) ----------
// Board: ESP32-S3 (N16R8). These match the KiCad schematic (swarm_robot, nets MOTOR_L_IN1 etc.).
// Rules: avoid GPIO 0,3,45,46 (boot pins), 19-20 (USB), 26-37 (flash/PSRAM), 43-44 (serial).
#define MOTOR_L_IN1_GPIO   4    // left motor, forward pin
#define MOTOR_L_IN2_GPIO   5    // left motor, reverse pin
#define MOTOR_R_IN3_GPIO   6    // right motor, forward pin
#define MOTOR_R_IN4_GPIO   7    // right motor, reverse pin

#define MOTOR_PWM_FREQ_HZ  1000 // pulses per second (raise to ~20000 if motors whine)
#define MOTOR_PWM_BITS     10   // duty range 0..1023
#define MOTOR_DUTY_MAX     1023 // = (1 << MOTOR_PWM_BITS) - 1

// Motors are rated 3-12 V but the battery is up to 8.4 V, so we cap the duty
// to keep the *average* voltage around 3-4 V (about 40%). Raise carefully.
#define MOTOR_MAX_DUTY_PCT 40

// Set to -1 if a motor spins the wrong way (easier than rewiring).
#define MOTOR_L_DIR        1
#define MOTOR_R_DIR        1

// ---------- Line sensor (QTR-8RC, all 8 outputs) ----------
// Order = sensor OUT1..OUT8 across the board. Matches schematic nets LINE_S1..LINE_S8.
#define LINE_SENSOR_COUNT  8
#define LINE_SENSOR_GPIOS  { 15, 16, 17, 18, 8, 9, 2, 42 }

#define LINE_CHARGE_US     10   // how long we push each pin high to charge the sensor (microseconds)
#define LINE_TIMEOUT_US    2500 // stop waiting after this long; a reading this high means "very dark"

// Line position maths works on "darkness" values: 0 = bright floor .. 1000 = black tape.
#define LINE_NOISE_MAX     50   // darkness at or below this is ignored (floor is never perfectly 0)
#define LINE_SEEN_MIN      200  // at least one sensor must be above this, or we say "no line"
