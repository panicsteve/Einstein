#pragma once

#include <SDL.h>
#include "TScreenManager.h"

void MainMouseDown(SDL_Window *window, Sint32 x, Sint32 y);
void MainMouseUp(SDL_Window *window, Sint32 x, Sint32 y);
void MainMouseMove(SDL_Window *window, Sint32 x, Sint32 y);

void MainDidQuit(void);
void MainUpdateScreenRect(SRect* inUpdateRect);

