#pragma once

#include <SDL.h>

SDL_Window *WindowCreate(int width, int height, const char *title);
void WindowDestroy(SDL_Window *window);

void WindowClear(SDL_Window *window);

SDL_Renderer *WindowGetRenderer(SDL_Window *window);
float WindowGetRendererScale(SDL_Window *window);

void WindowDidResize(SDL_Window *window);
