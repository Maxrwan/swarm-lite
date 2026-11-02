#include "motors.h"
#include "motors_math.h"
#include "config.h"
#include "driver/ledc.h"
#include "esp_err.h"

// Each motor has TWO inputs. PWM on one input with the other held low = one direction;
// swap them = the other direction. So we give all 4 pins a PWM channel.
enum { CH_L_FWD, CH_L_REV, CH_R_FWD, CH_R_REV, CH_COUNT };

static const int s_pins[CH_COUNT] = {
    MOTOR_L_IN1_GPIO, MOTOR_L_IN2_GPIO, MOTOR_R_IN3_GPIO, MOTOR_R_IN4_GPIO,
};

static void set_duty(int ch, int duty)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)ch, duty));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)ch));
}

void motors_init(void)
{
    ledc_timer_config_t timer = {
        .speed_mode      = LEDC_LOW_SPEED_MODE,
        .duty_resolution = (ledc_timer_bit_t)MOTOR_PWM_BITS,
        .timer_num       = LEDC_TIMER_0,
        .freq_hz         = MOTOR_PWM_FREQ_HZ,
        .clk_cfg         = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    for (int ch = 0; ch < CH_COUNT; ch++) {
        ledc_channel_config_t c = {
            .gpio_num   = s_pins[ch],
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel    = (ledc_channel_t)ch,
            .timer_sel  = LEDC_TIMER_0,
            .duty       = 0,      // start stopped
            .hpoint     = 0,
        };
        ESP_ERROR_CHECK(ledc_channel_config(&c));
    }
}

static void drive_one(int fwd_ch, int rev_ch, int speed)
{
    int duty = motors_speed_to_duty(speed);
    if (speed >= 0) { set_duty(rev_ch, 0); set_duty(fwd_ch, duty); }
    else            { set_duty(fwd_ch, 0); set_duty(rev_ch, duty); }
}

void motors_set(int left, int right)
{
    drive_one(CH_L_FWD, CH_L_REV, left  * MOTOR_L_DIR);
    drive_one(CH_R_FWD, CH_R_REV, right * MOTOR_R_DIR);
}

void motors_stop(void)
{
    motors_set(0, 0);
}
