#pragma once

#include <SDL.h>

void EventDispatch(SDL_Event *event);

void EventHandleKey(SDL_KeyboardEvent *event);
void EventHandleMouseButton(SDL_MouseButtonEvent *event);
void EventHandleMouseMotion(SDL_MouseMotionEvent *event);
void EventHandleQuit(SDL_QuitEvent *event);
void EventHandleWindow(SDL_WindowEvent *event);
