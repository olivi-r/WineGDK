/*
 * Copyright (C) the Wine project
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_XERROR_H
#define __WINE_XERROR_H

typedef enum XErrorOptions XErrorOptions;

typedef void __stdcall XErrorCallback( HRESULT hr, const char *msg, void *context );

enum XErrorOptions
{
    XErrorOptions_None                      = 0x00,
    XErrorOptions_OutputDebugStringOnError  = 0x01,
    XErrorOptions_DebugBreakOnError         = 0x02,
    XErrorOptions_FailFastOnError           = 0x04,
};

#endif
