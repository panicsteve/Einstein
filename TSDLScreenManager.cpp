// ==============================
// File:			TNullScreenManager.cp
// Project:			Einstein
//
// Copyright 2003-2007 by Paul Guyot (pguyot@kallisys.net).
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// ==============================
// $Id$
// ==============================

#include "TSDLScreenManager.h"

// Einstein
#include "TLog.h"

// -------------------------------------------------------------------------- //
//  * PowerOn( void )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::PowerOn( void )
{
	GetLog()->LogLine("TSDLScreenManager::PowerOn()");
}

// -------------------------------------------------------------------------- //
//  * PowerOffScreen( void )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::PowerOff( void )
{
	GetLog()->LogLine("TSDLScreenManager::PowerOff()");
}

// -------------------------------------------------------------------------- //
//  * PowerOnScreen( void )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::PowerOnScreen( void )
{
	GetLog()->LogLine("TSDLScreenManager::PowerOnScreen()");
}

// -------------------------------------------------------------------------- //
//  * PowerOffScreen( void )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::PowerOffScreen( void )
{
	GetLog()->LogLine("TSDLScreenManager::PowerOffScreen()");
}

// -------------------------------------------------------------------------- //
//  * BacklightChanged( Boolean )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::BacklightChanged( Boolean backlight )
{
	GetLog()->FLogLine("TSDLScreenManager::BacklightChanged(%d)", (int) backlight);
}

// -------------------------------------------------------------------------- //
//  * ContrastChanged( KUInt32 )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::ContrastChanged( KUInt32 contrast )
{
	GetLog()->FLogLine("TSDLScreenManager::ContrastChanged(%u)", (unsigned int) contrast);
}

// -------------------------------------------------------------------------- //
//  * ScreenOrientationChanged( EOrientation )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::ScreenOrientationChanged( EOrientation inNewOrientation )
{
	GetLog()->FLogLine("TSDLScreenManager::ScreenOrientationChanged(%u)", (unsigned int) inNewOrientation);
}

// -------------------------------------------------------------------------- //
//  * TabletOrientationChanged( EOrientation )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::TabletOrientationChanged( EOrientation inNewOrientation )
{
	GetLog()->FLogLine("TSDLScreenManager::TabletOrientationChanged(%u)", (unsigned int) inNewOrientation);
}

// -------------------------------------------------------------------------- //
//  * UpdateScreenRect( SRect* )
// -------------------------------------------------------------------------- //
void
TSDLScreenManager::UpdateScreenRect( SRect* inUpdateRect )
{
	KUInt16 top = inUpdateRect->fTop;
	KUInt16 left = inUpdateRect->fLeft;
	KUInt16 height = inUpdateRect->fBottom - top;
	KUInt16 width = inUpdateRect->fRight - left;

	KUInt8 *theScreenBuffer = GetScreenBuffer();
	KUInt32 theScreenWidth = GetScreenWidth();
	KUInt32 srcRowBytes = theScreenWidth * kBitsPerPixel / 8;
	KUInt32 dstRowBytes = theScreenWidth * 32 / 8;
	KUInt32 srcWidthInBytes = width * kBitsPerPixel / 8;

	KUInt8 *mImageBuffer = (KUInt8 *)malloc(320 * 480 * 4);
	KUInt8 *srcRowPtr = theScreenBuffer + (top * srcRowBytes) + (left * kBitsPerPixel / 8);
	KUInt8* dstRowPtr =
		((KUInt8*) mImageBuffer)
		+ (top * dstRowBytes)
		+ (left * 32 / 8);

	for ( int indexRows = height; indexRows != 0; indexRows-- )
	{
		KUInt8* srcCursor = srcRowPtr;
		KUInt8* srcEnd = srcRowPtr + srcWidthInBytes;
		KUInt32* dstCursor = (KUInt32*) dstRowPtr;
		do {
			KUInt8 theByte = *srcCursor++;
			// First pixel
			KUInt32 thePixel = (theByte & 0xF0) >> 4;
			*dstCursor++ = 0xff0000ff;
			// Second pixel
			thePixel = (theByte & 0x0F);
			*dstCursor++ = 0xff00ffff;
		} while (srcCursor < srcEnd);
		srcRowPtr += srcRowBytes;
		dstRowPtr += dstRowBytes;
	}

	printf("%02x%02x%02x%02x ", mImageBuffer[0], mImageBuffer[1], mImageBuffer[2], mImageBuffer[3]);
	printf("%02x%02x%02x%02x ", mImageBuffer[4], mImageBuffer[5], mImageBuffer[6], mImageBuffer[7]);
	printf("%02x%02x%02x%02x ", mImageBuffer[8], mImageBuffer[9], mImageBuffer[10], mImageBuffer[11]);
	printf("%02x%02x%02x%02x \n", mImageBuffer[12], mImageBuffer[13], mImageBuffer[14], mImageBuffer[15]);

	free(mImageBuffer);
}

// ========================================================================= //
// ... Any resemblance between the above views and those of my employer,     //
// my terminal, or the view out my window are purely coincidental.  Any      //
// resemblance between the above and my own views is non-deterministic.  The //
// question of the existence of views in the absence of anyone to hold them  //
// is left as an exercise for the reader.  The question of the existence of  //
// the reader is left as an exercise for the second god coefficient.  (A     //
// discussion of non-orthogonal, non-integral polytheism is beyond the scope //
// of this article.)                                                         //
// ========================================================================= //
