/*
 * Xbox Game runtime Library
 *
 * Copyright 2026 Olivia Ryan
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

#include <wine/test.h>
#include <xgameruntime.h>

typedef HRESULT (WINAPI *InitializeApiImpl_f)( ULONG gdkVer, ULONG gsVer );
typedef HRESULT (WINAPI *QueryApiImpl_f)( const GUID *classId, REFIID interfaceId, void **out );
typedef HRESULT (WINAPI *UninitializeApiImpl_f)( void );

InitializeApiImpl_f InitializeApiImpl = NULL;
QueryApiImpl_f QueryApiImpl = NULL;
UninitializeApiImpl_f UninitializeApiImpl = NULL;

static BOOLEAN test_Init( void )
{
    HMODULE xgameruntime;
    HRESULT hr;

    xgameruntime = LoadLibraryA( "xgameruntime.dll" );
    ok( xgameruntime != NULL, "got error %lu.\n", GetLastError() );
    if (!xgameruntime) goto failed;

    InitializeApiImpl = (InitializeApiImpl_f)GetProcAddress( xgameruntime, "InitializeApiImpl" );
    ok( InitializeApiImpl != NULL, "got error %lu.\n", GetLastError() );
    if (!InitializeApiImpl) goto failed;

    QueryApiImpl = (QueryApiImpl_f)GetProcAddress( xgameruntime, "QueryApiImpl" );
    ok( QueryApiImpl != NULL, "got error %lu.\n", GetLastError() );
    if (!QueryApiImpl) goto failed;

    UninitializeApiImpl = (UninitializeApiImpl_f)GetProcAddress( xgameruntime, "UninitializeApiImpl" );
    ok( UninitializeApiImpl != NULL, "got error %lu.\n", GetLastError() );
    if (!UninitializeApiImpl) goto failed;

    hr = InitializeApiImpl( GDKC_VERSION, GAMING_SERVICES_VERSION );
    ok( hr == S_OK, "got hr %#lx.\n", hr );
    if (FAILED(hr)) goto failed;

    return TRUE;

failed:
    return FALSE;
}

START_TEST(xgameruntime)
{
    HRESULT hr;

    if (!test_Init())
    {
        win_skip( "Failed to initialize xgameruntime, skipping tests.\n" );
        return;
    }

    hr = UninitializeApiImpl();
    ok( hr == S_OK, "got hr %#lx.\n", hr );
}
