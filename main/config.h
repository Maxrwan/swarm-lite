// config.h - every number that might change lives here.
// (The professor hasn't fixed robot size or distances, so never hard-code these elsewhere.)
#pragma once

// ---------- Motors (MX1508 driver) ----------
// PLACEHOLDER pins: agree on the final pin map with your teammate on day 1.
// Rules: avoid GPIO 0,2,5,12,15 (boot pins), 6-11 (flash), 34-39 (input only), 14 (PWM at boot).
#define MOTOR_L_IN1_GPIO   25   // left motor, forward pin
#define MOTOR_L_IN2_GPIO   26   // left motor, reverse pin
#define MOTOR_R_IN3_GPIO   27   // right motor, forward pin
#define MOTOR_R_IN4_GPIO   33   // right motor, reverse pin

#define MOTOR_PWM_FREQ_HZ  1000 // pulses per second (raise to ~20000 if motors whine)
#define MOTOR_PWM_BITS     10   // duty range 0..1023
#define MOTOR_DUTY_MAX     1023 // = (1 << MOTOR_PWM_BITS) - 1

// Motors are rated 3-12 V but the battery is up to 8.4 V, so we cap the duty
// to keep the *average* voltage around 3-4 V (about 40%). Raise carefully.
#define MOTOR_MAX_DUTY_PCT 40

// Set to -1 if a motor spins the wrong way (easier than rewiring).
#define MOTOR_L_DIR        1
#define MOTOR_R_DIR        1
