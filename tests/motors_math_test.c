#include <stdio.h>
#include <assert.h>
#include "motors_math.h"
int main(void){
  assert(motors_speed_to_duty(0)==0);
  assert(motors_speed_to_duty(100)==409);
  assert(motors_speed_to_duty(-100)==409);
  assert(motors_speed_to_duty(250)==409);   // clamped
  assert(motors_speed_to_duty(50)==204);
  printf("all duty checks passed (100%% -> %d of 1023)\n", motors_speed_to_duty(100));
}
