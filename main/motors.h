#pragma once

// Call once at startup.
void motors_init(void);

// left/right: -100 (full reverse) .. 0 (stop) .. +100 (full forward).
// "100" means the capped maximum from config.h, not the raw battery voltage.
void motors_set(int left, int right);

// Both motors off.
void motors_stop(void);
