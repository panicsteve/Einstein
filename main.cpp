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
TScreenManager *screenManager = NULL;
SDL_Surface *surface = NULL;
SDL_Window *window = NULL;

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
		screenManager = new TSDLScreenManager(log);
		
		emulator = new TEmulator(
					log, romImage, flashPath,
					soundManager, screenManager, networkManager, ramSize << 16 );

        surface = SDL_CreateRGBSurfaceWithFormat(0, kNewtonDisplayWidth, kNewtonDisplayHeight, 32, SDL_PIXELFORMAT_RGBA32);

        if ( surface != NULL )
        {
            window = WindowCreate(kNewtonDisplayWidth, kNewtonDisplayHeight, "Einstein");
            
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
                    }
                }

                emulator->Stop();
                pthread_join(thread, NULL);

                WindowDestroy(window);
                window = NULL;
            }
        }
        else
        {
            SDL_Log("SDL_CreateRGBSurfaceWithFormat failed: %s", SDL_GetError());
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

static SDL_bool mouseDown = SDL_FALSE;

void MainMouseDown(SDL_Window *window, Sint32 x, Sint32 y)
{
    screenManager->PenDown(x, y);
    mouseDown = SDL_TRUE;
}

void MainMouseUp(SDL_Window *window, Sint32 x, Sint32 y)
{
    screenManager->PenUp();
    mouseDown = SDL_FALSE;
}

void MainMouseMove(SDL_Window *window, Sint32 x, Sint32 y)
{
    if ( mouseDown )
    {
        screenManager->PenDown(x, y);
    }
}

void MainDidQuit()
{
	sQuit = SDL_TRUE;
}

void MainUpdateScreenRect(SRect* inUpdateRect)
{
    KUInt16 top = inUpdateRect->fTop;
    KUInt16 left = inUpdateRect->fLeft;
    KUInt16 height = inUpdateRect->fBottom - top;
    KUInt16 width = inUpdateRect->fRight - left;

	left = 0;
	width = 320;

    static const int kBitsPerPixel = 4;
    KUInt8 *theScreenBuffer = screenManager->GetScreenBuffer();
    KUInt32 theScreenWidth = screenManager->GetScreenWidth();
    KUInt32 srcRowBytes = theScreenWidth * kBitsPerPixel / 8;
    KUInt32 dstRowBytes = theScreenWidth * 4;
    KUInt32 srcWidthInBytes = width * kBitsPerPixel / 8;

    KUInt8 *srcRowPtr = theScreenBuffer + (top * srcRowBytes) + (left * kBitsPerPixel / 8);
    
    
    SDL_LockSurface(surface);
    KUInt8 *mImageBuffer = (KUInt8 *)surface->pixels;
    
    KUInt8* dstRowPtr =
        ((KUInt8*) mImageBuffer)
        + (top * dstRowBytes)
        + (left * 4);

    KUInt32 palette[] = {
        0xff000000,
        0xff111111,
        0xff222222,
        0xff333333,
        0xff444444,
        0xff555555,
        0xff666666,
        0xff777777,
        0xff888888,
        0xff999999,
        0xffaaaaaa,
        0xffbbbbbb,
        0xffcccccc,
        0xffdddddd,
        0xffeeeeee,
        0xffffffff,
    };
    
    for ( int indexRows = height; indexRows != 0; indexRows-- )
    {
        KUInt8* srcCursor = srcRowPtr;
        KUInt8* srcEnd = srcRowPtr + srcWidthInBytes;
        KUInt32* dstCursor = (KUInt32*) dstRowPtr;
        do {
            KUInt8 theByte = *srcCursor++;
            // First pixel
            KUInt32 thePixel = (theByte & 0xF0) >> 4;
            *dstCursor++ = palette[thePixel];
            // Second pixel
            thePixel = (theByte & 0x0F);
            *dstCursor++ = palette[thePixel];
        } while (srcCursor < srcEnd);
        srcRowPtr += srcRowBytes;
        dstRowPtr += dstRowBytes;
    }

    SDL_UnlockSurface(surface);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(WindowGetRenderer(window), surface);
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = kNewtonDisplayScaledWidth;
    destRect.h = kNewtonDisplayScaledHeight;

    SDL_RenderCopyEx(WindowGetRenderer(window), texture, NULL, &destRect, 0.0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(WindowGetRenderer(window));
    
    SDL_DestroyTexture(texture);
}
