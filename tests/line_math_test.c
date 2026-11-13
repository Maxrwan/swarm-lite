#include <stdio.h>
#include <assert.h>
#include "line_sensor_math.h"
int main(void){
  // line exactly under one sensor
  uint16_t s1[8]={1000,0,0,0,0,0,0,0};           assert(line_position(s1,8)==0);
  uint16_t s8[8]={0,0,0,0,0,0,0,1000};           assert(line_position(s8,8)==7000);
  uint16_t s3[8]={0,0,1000,0,0,0,0,0};           assert(line_position(s3,8)==2000);
  // tape covering sensors 4 and 5 equally = centred
  uint16_t mid[8]={0,0,0,1000,1000,0,0,0};       assert(line_position(mid,8)==3500);
  // tape mostly on 4, a little on 5 = between them, closer to 4
  uint16_t off[8]={0,0,0,900,300,0,0,0};         assert(line_position(off,8)==3250);
  // small floor noise must not move the answer
  uint16_t noisy[8]={30,40,20,1000,1000,50,10,45}; assert(line_position(noisy,8)==3500);
  // nothing dark enough = no line
  uint16_t none[8]={30,40,20,100,150,50,10,45};  assert(line_position(none,8)==-1);
  uint16_t zero[8]={0};                          assert(line_position(zero,8)==-1);
  // all black (a junction) still gives the centre
  uint16_t all[8]={1000,1000,1000,1000,1000,1000,1000,1000}; assert(line_position(all,8)==3500);
  printf("all line position checks passed (centre = %d)\n", line_position(mid,8));
}
