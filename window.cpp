#include <assert.h>

#include "window.h"

void WindowClear(SDL_Window *window)
{
	assert(window != NULL);

	SDL_Renderer *renderer = SDL_GetRenderer(window);
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderClear(renderer);
}

SDL_Window *WindowCreate(int inWidth, int inHeight, const char *title)
{
	SDL_Window *window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			inWidth, inHeight,
			SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if ( window != NULL )
	{
		// Enumerate available drivers 

		int numDrivers = SDL_GetNumRenderDrivers();
		SDL_Log("Render drivers available: %d", numDrivers);

		for ( int i = 0; i < numDrivers; ++i )
		{
			SDL_RendererInfo driverInfo;

			if ( SDL_GetRenderDriverInfo(i, &driverInfo) == 0 )
			{
				SDL_Log("- Driver #%d: %s", i, driverInfo.name);
			}
		}

		// Create renderer for window

		int driverIndex = -1;
		SDL_Renderer *renderer = SDL_CreateRenderer(window, driverIndex, SDL_RENDERER_ACCELERATED);

		if ( renderer != NULL )
		{
			// Just some debug info

			SDL_RendererInfo rendererInfo;
			SDL_GetRendererInfo(renderer, &rendererInfo);
			SDL_Log("Using renderer: %s", rendererInfo.name);

			float scale = WindowGetRendererScale(window);

			int rendererOutputWidth = 0;
			int rendererOutputHeight = 0;
			SDL_GetRendererOutputSize(renderer, &rendererOutputWidth, &rendererOutputHeight);

			SDL_Log("Renderer output size=%dx%dpx scale=%.2f", rendererOutputWidth, rendererOutputHeight, scale);
            
            WindowClear(window);
            SDL_RenderPresent(renderer);
		}
		else
		{
			SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());

			SDL_DestroyWindow(window);
			window = NULL;
		}
	}
	else
	{
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
	}

	return window;
}

void WindowDestroy(SDL_Window *window)
{
	assert(window != NULL);
	
	SDL_Renderer *renderer = SDL_GetRenderer(window);
	
	if ( renderer != NULL )
	{
		SDL_DestroyRenderer(renderer);
	}
	
	SDL_DestroyWindow(window);
}

void WindowDidResize(SDL_Window *window)
{
	assert(window != NULL);

	WindowClear(window);
}

SDL_Renderer *WindowGetRenderer(SDL_Window *window)
{
    assert(window != NULL);

    return SDL_GetRenderer(window);
}

float WindowGetRendererScale(SDL_Window *window)
{
	assert(window != NULL);

	// Determine scale of renderer (high DPI display?)

	int rendererOutputWidth = 0;
	int rendererOutputHeight = 0;
	int width;
	int height;
		
	SDL_Renderer *renderer = SDL_GetRenderer(window);		
	SDL_GetRendererOutputSize(renderer, &rendererOutputWidth, &rendererOutputHeight);
	SDL_GetWindowSize(window, &width, &height);

	float rendererScale = rendererOutputWidth / width;
	
	return rendererScale;
}

