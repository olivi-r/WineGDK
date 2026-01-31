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

#include <initguid.h>

#include "private.h"

WINE_DEFAULT_DEBUG_CHANNEL(xgameruntime);

HRESULT WINAPI DllCanUnloadNow( void )
{
    return S_FALSE;
}

BOOL WINAPI DllMain( HINSTANCE hinst, DWORD reason, void *reserved )
{
    TRACE( "hinst %p, reason %lu, reserved %p.\n", hinst, reason, reserved );

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls( hinst );
            break;
    }

    return TRUE;
}

HRESULT WINAPI InitializeApiImplEx2( ULONG gdkVer, ULONG gsVer, char mode, const XGameRuntimeOptions *options )
{
    TRACE( "gdkVer %ld, gsVer %ld, mode %d, options %p.\n", gdkVer, gsVer, mode, options );
    return GDKC_InitAPI( gdkVer, gsVer, mode, options );
}

HRESULT WINAPI InitializeApiImplEx( ULONG gdkVer, ULONG gsVer, char mode )
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
    TRACE( "runtimeClassId %s, interfaceId %s, out %p.\n", debugstr_guid( runtimeClassId ), debugstr_guid( interfaceId ), out );

    if (IsEqualGUID( runtimeClassId, &CLSID_XAccessibilityImpl ))
        return IXAccessibility_QueryInterface( x_accessibility_impl, interfaceId, out );
    if (IsEqualGUID( runtimeClassId, &CLSID_XAppCaptureImpl ))
        return IXAppCapture_QueryInterface( capture_impl, interfaceId, out );
    if (IsEqualGUID( runtimeClassId, &CLSID_XAppCaptureImpl2 ))
        return IXAppCapture2_QueryInterface( capture2_impl, interfaceId, out );
    if (IsEqualGUID( runtimeClassId, &CLSID_XLauncherImpl ))
        return IXLauncher_QueryInterface( x_launcher_impl, interfaceId, out );

    FIXME( "%s not implemented, returning ERROR_NOT_SUPPORTED.\n", debugstr_guid( runtimeClassId ) );
    return HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED );
}

HRESULT WINAPI UninitializeApiImpl( void )
{
    FIXME( "stub!\n" );
    return E_NOTIMPL;
}

HRESULT WINAPI XErrorReport( HRESULT status, const char *message )
{
    FIXME( "status %#lx, message %s stub!\n", status, debugstr_a( message ) );
    return E_NOTIMPL;
}
