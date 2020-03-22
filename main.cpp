#include <assert.h>

#include "constants.h"
#include "event.h"
#include "main.h"
#include "window.h"

#include "KDefinitions.h"
#include "TEmulator.h"
#include "TFlatROMImageWithREX.h"
#include "TNetworkManager.h"
#include "TNullSoundManager.h"
#include "TSDLScreenManager.h"
#include "TStdOutLog.h"

static SDL_bool sQuit = SDL_FALSE;
static TEmulator *emulator = NULL;

void *ThreadEntry(void *arg)
{
	emulator->Run();
	return NULL;
}

int main(int argc, const char *argv[])
{
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
	}
	else
	{
        const char *romPath = "717006.rom";
        const char *rexPath = "717006.rex";
        const char *flashPath = "einstein.flash";
		const int ramSize = 0x40;

        TFlatROMImageWithREX *romImage = new TFlatROMImageWithREX(romPath, rexPath, kMachineString717006, false);

		TLog *log = new TStdOutLog();
		TSoundManager *soundManager = new TNullSoundManager(log);
		TNetworkManager *networkManager = new TNullNetwork(log);
		TScreenManager *screenManager = new TSDLScreenManager(log);
		
		emulator = new TEmulator(
					log, romImage, flashPath,
					soundManager, screenManager, networkManager, ramSize << 16 );

        SDL_Window *window = WindowCreate(kNewtonDisplayScaledWidth, kNewtonDisplayScaledHeight, "Einstein");
		
		if ( window )
		{
			pthread_t thread;
			int err = pthread_create(&thread, NULL, &ThreadEntry, NULL);
			if ( err )
			{
				(void)fprintf( stderr, "Error with pthread_create (%i)\n", err);
				exit(2);
			}

			SDL_Event event;

			while ( sQuit == SDL_FALSE )
			{		
				if ( SDL_WaitEvent(&event) )
				{
					EventDispatch(&event);

                    SDL_RenderPresent(WindowGetRenderer(window));
				}
			}

			emulator->Stop();
			pthread_join(thread, NULL);

			WindowDestroy(window);
			window = NULL;
		}
		
		if ( romImage )
		{
			delete romImage;
		}
	}
	
	SDL_Log("Exiting...");
	SDL_Quit();

	return 0;
}

void MainDidMoveMouse(SDL_Window *window, Sint32 x, Sint32 y)
{
}

void MainDidQuit()
{
	sQuit = SDL_TRUE;
}
