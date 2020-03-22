#include <assert.h>

#include "event.h"
#include "main.h"
#include "window.h"

void EventDispatch(SDL_Event *event)
{
	assert(event != NULL);

    switch ( event->type )
	{
		case SDL_KEYDOWN :
		case SDL_KEYUP :
			EventHandleKey(&event->key);
			break;
	
		case SDL_MOUSEBUTTONDOWN :
		case SDL_MOUSEBUTTONUP :
			EventHandleMouseButton(&event->button);
			break;
			
		case SDL_MOUSEMOTION :
			EventHandleMouseMotion(&event->motion);
			break;
			
		case SDL_QUIT :
			EventHandleQuit(&event->quit);
			break;

		default :
			break;
	}
}

void EventHandleKey(SDL_KeyboardEvent *event)
{
	assert(event != NULL);

	SDL_Log("Key event");
}

void EventHandleMouseButton(SDL_MouseButtonEvent *event)
{
	assert(event != NULL);
	
	SDL_Log("Mouse button event");

    SDL_Window *window = SDL_GetWindowFromID(event->windowID);
    
    if ( event->type == SDL_MOUSEBUTTONDOWN )
    {
        MainMouseDown(window, event->x, event->y);
    }
    else if ( event->type == SDL_MOUSEBUTTONUP )
    {
        MainMouseUp(window, event->x, event->y);
    }
}

void EventHandleMouseMotion(SDL_MouseMotionEvent *event)
{
	assert(event != NULL);

	SDL_Window *window = SDL_GetWindowFromID(event->windowID);
	MainMouseMove(window, event->x, event->y);
}

void EventHandleQuit(SDL_QuitEvent *event)
{
	assert(event != NULL);

	MainDidQuit();
}

