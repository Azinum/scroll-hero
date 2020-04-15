// window.c

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"
#include "player.h"
#include "window.h"

struct Window {
  SDL_Renderer* renderer;
  SDL_Window* window;
  SDL_Event event;
  TTF_Font* font;
  unsigned char init;
};

static struct Window window;

int window_init(const char* screen_title, int32_t screen_width, int32_t screen_height) {
  log_out("Window init (w: %i, h: %i)\n", screen_width, screen_height);
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    log_out("%s\n", SDL_GetError());
    return -1;
  }
  window.window = SDL_CreateWindow(
    screen_title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    screen_width,
    screen_height,
    SDL_WINDOW_SHOWN
  );
  if (!window.window) {
    log_out("%s\n", SDL_GetError());
    return ERR;
  }
  // SDL_RENDERER_ACCELERATED | SDL_RENDERER_SOFTWARE § SDL_RENDERER_PRESENTVSYNC
  window.renderer = SDL_CreateRenderer(window.window, -1,
    SDL_RENDERER_PRESENTVSYNC
  );
  if (!window.renderer) {
    log_out("%s\n", SDL_GetError());
    return ERR;
  }
  if (SDL_SetRenderDrawBlendMode(window.renderer, SDL_BLENDMODE_BLEND) != 0) {
    log_out("%s\n", SDL_GetError());
    return ERR;
  }
  if (TTF_Init() != 0) {
    log_out("TTF_Init: %s\n", TTF_GetError());
    return ERR;
  }
  if (!(window.font = TTF_OpenFont("resources/fonts/font.ttf", 30))) {
    log_out("TTF_OpenFont: %s\n", TTF_GetError());
    return ERR;
  }
  window.init = 1;
  return NO_ERR;
}

void* window_renderer() {
  return window.renderer;
}

void* window_font() {
  return window.font;
}

const uint8_t* window_keyboardstate() {
  return SDL_GetKeyboardState(NULL);
}

void window_change_title(const char* new_title) {
  assert(window.window != NULL);
  SDL_SetWindowTitle(window.window, new_title);
}

int window_pollevent() {
  while (SDL_PollEvent(&window.event)) {
    switch (window.event.type) {
      case SDL_QUIT:
        return -1;

      case SDL_KEYDOWN: {
        switch (window.event.key.keysym.sym) {
          case SDLK_ESCAPE:
            return -1;

          default:
            break;
        }
        break;
      }

      default:
        break;
    }
  }
  return 0;
}

double window_time() {
  return SDL_GetPerformanceCounter();
}

void window_clear() {
  assert(window.renderer != NULL);
  SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
  SDL_RenderClear(window.renderer);
}

void window_render() {
  assert(window.renderer != NULL);
  SDL_RenderPresent(window.renderer);
}

void window_free() {
  SDL_DestroyWindow(window.window);
  SDL_DestroyRenderer(window.renderer);
  TTF_CloseFont(window.font);
  TTF_Quit();
  SDL_Quit();
}