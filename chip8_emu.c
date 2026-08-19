#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <stdio.h>
#include <sys/types.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

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

void Cycle(Chip8 *cpu, u_int8_t *memory)
{
  //fetch
  u_int16_t instruction = (memory[cpu->pc] << 8 | memory[cpu->pc + 1]);
  cpu->pc += 2;

  //decode
  u_int8_t x = (instruction & 0x0F00) >> 8;
  u_int8_t y = (instruction & 0x00F0) >> 4;
  u_int8_t n = (instruction & 0x000F);
  u_int8_t nn = (instruction & 0x00FF);
  u_int8_t nnn = (instruction & 0x0FFF);

  switch((instruction & 0xF000) >> 12)
  {
    case 0x0:
      
      switch(nn)
      {
        //clear screen
        case 0xE0:
          break;

        //return from a subroutine
        case 0xEE:
          break;

        default:
          SDL_Log("Unknown opcode: 0x%04X", instruction);
          break;
      }

      break;

    //put nn value in register[x]
    case 0x6:
      cpu->v[x] = nn;
      break;

    //add nn value to register[x]
    case 0x7:
      cpu->v[x] += nn;
      break;

    case 0x8:

      switch(n)
      {
        case 0x0:
          break;

        case 0x1:
          break;

        case 0x2:
          break;

        case 0x3:
          break;

        case 0x4:
          break;

        case 0x5:
          break;

        case 0x6:
          break;

        case 0x7:
          break;

        case 0xE:
          break;

      }
  }
  //execute
  cpu->v[x] = nn;

}
 
int main()
{
  bool running = true;
  SDL_Surface *winSurface = NULL;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  u_int8_t ram[4096];
  u_int8_t screen[64 * 32];

  
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ERROR: could not initialize SDL: %s", SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow("CHIP-8 emu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64 * 10, 32 * 10, SDL_WINDOW_SHOWN);

  if(window == NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ERROR: could not create window: %s", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  while(running)
  {
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        running = false;
      }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      SDL_RenderPresent(renderer);
    }
  }
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
