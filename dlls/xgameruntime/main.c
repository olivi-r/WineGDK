/*
 * Xbox Game runtime Library
 *
 * Written by Weather
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

#include "private.h"

WINE_DEFAULT_DEBUG_CHANNEL(xgameruntime);

static HMODULE xgameruntime;

HRESULT WINAPI DllCanUnloadNow( void )
{
    return xgameruntime != NULL ? S_FALSE : S_OK;
}

BOOL WINAPI DllMain( HINSTANCE hinst, DWORD reason, void *reserved )
{
    TRACE( "hinst %p, reason %lu, reserved %p.\n", hinst, reason, reserved );

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls( hinst );
            break;

        case DLL_PROCESS_DETACH:
            if (reserved) break;
            if (xgameruntime) FreeLibrary( xgameruntime );
            break;
    }

    return TRUE;
}

HRESULT WINAPI InitializeApiImplEx2( ULONG gdkVer, ULONG gsVer, CHAR mode, INITIALIZE_OPTIONS *options )
{
    FIXME( "gdkVer %ld, gsVer %ld, mode %d, options %p stub!\n", gdkVer, gsVer, mode, options );
    return E_NOTIMPL;
}

HRESULT WINAPI InitializeApiImplEx( ULONG gdkVer, ULONG gsVer, CHAR mode )
{
    TRACE( "gdkVer %ld, gsVer %ld, mode %d.\n", gdkVer, gsVer, mode );
    return InitializeApiImplEx2( gdkVer, gsVer, mode, NULL );
}

HRESULT WINAPI InitializeApiImpl( ULONG gdkVer, ULONG gsVer )
{
    TRACE( "gdkVer %ld, gsVer %ld.\n", gdkVer, gsVer );
    return InitializeApiImplEx2( gdkVer, gsVer, 0, NULL );
}

HRESULT WINAPI QueryApiImpl( const GUID *runtimeClassId, REFIID interfaceId, void **out )
{
    FIXME( "runtimeClassId %s, interfaceId %s, out %p stub!\n", debugstr_guid( runtimeClassId ), debugstr_guid( interfaceId ), out );
    return E_NOINTERFACE;
}

HRESULT WINAPI UninitializeApiImpl( void )
{
    FIXME( "stub!\n" );
    return E_NOTIMPL;
}

HRESULT WINAPI XErrorReport( HRESULT status, const CHAR *message )
{
    FIXME( "status %#lx, message %s stub!\n", status, debugstr_a( message ) );
    return E_NOTIMPL;
}
