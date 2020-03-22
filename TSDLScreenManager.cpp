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
    // Ignore this.
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
