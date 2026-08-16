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
