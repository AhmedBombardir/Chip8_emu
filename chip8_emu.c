#include <stdio.h>
#include <sys/types.h>

typedef struct
{
  u_int8_t v[16];

  u_int16_t pc;
  u_int16_t reg_i;
  
  u_int8_t sp;
  u_int16_t stack[16];

  u_int8_t delay_timer;
  u_int8_t sound_timer;
  
}Chip8;

 
int main(void)
{
  u_int8_t ram[4096];
  u_int8_t screen[64 * 32];
  return 0;
}
