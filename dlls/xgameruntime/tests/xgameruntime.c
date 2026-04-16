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

#include <initguid.h>
#include <wine/test.h>

#define COBJMACROS
#include <xgameruntime.h>

typedef HRESULT (WINAPI *InitializeApiImpl_f)( ULONG gdkVer, ULONG gsVer );
typedef HRESULT (WINAPI *QueryApiImpl_f)( const GUID *classId, REFIID interfaceId, void **out );
typedef HRESULT (WINAPI *UninitializeApiImpl_f)( void );

InitializeApiImpl_f InitializeApiImpl = NULL;
QueryApiImpl_f QueryApiImpl = NULL;
UninitializeApiImpl_f UninitializeApiImpl = NULL;

#define check_interface( obj, iid ) check_interface_( __LINE__, obj, iid )
static void check_interface_( unsigned int line, void *obj, const IID *iid )
{
    IUnknown *iface = obj, *unknown;
    HRESULT hr;

    hr = IUnknown_QueryInterface( iface, iid, (void **)&unknown );
    ok_(__FILE__, line)( hr == S_OK, "got hr %#lx.\n", hr );
    if (SUCCEEDED(hr)) IUnknown_Release( unknown );
}

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

static void test_XAccessibility( void )
{
    IXAccessibility *xaccessibility = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XAccessibilityImpl, &IID_IXAccessibility, (void **)&xaccessibility );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XAccessibilityImpl ) );
        return;
    }
    if (!xaccessibility) return;

    check_interface( xaccessibility, &IID_IUnknown );
    check_interface( xaccessibility, &IID_IXAccessibility );

    IXAccessibility_Release( xaccessibility );
}

static void test_XAppCapture( void )
{
    IXAppCapture2 *xappcapture2 = NULL;
    IXAppCapture *xappcapture = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XAppCaptureImpl, &IID_IXAppCapture, (void **)&xappcapture );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XAppCaptureImpl ) );
        return;
    }
    if (!xappcapture) return;

    check_interface( xappcapture, &IID_IUnknown );
    check_interface( xappcapture, &IID_IXAppCapture );

    IXAppCapture_Release( xappcapture );

    hr = QueryApiImpl( &CLSID_XAppCaptureImpl2, &IID_IXAppCapture2, (void **)&xappcapture2 );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XAppCaptureImpl2 ) );
        return;
    }
    if (!xappcapture2) return;

    check_interface( xappcapture2, &IID_IUnknown );
    check_interface( xappcapture2, &IID_IXAppCapture2 );
    flaky check_interface( xappcapture2, &IID_IXAppCapture3 );
    flaky check_interface( xappcapture2, &IID_IXAppCapture4 );
    flaky check_interface( xappcapture2, &IID_IXAppCapture5 );

    IXAppCapture2_Release( xappcapture2 );
}

static void test_XDisplay( void )
{
    IXDisplay *xdisplay = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XDisplayImpl, &IID_IXDisplay, (void **)&xdisplay );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XDisplayImpl ) );
        return;
    }
    if (!xdisplay) return;

    check_interface( xdisplay, &IID_IUnknown );
    check_interface( xdisplay, &IID_IXDisplay );

    IXDisplay_Release( xdisplay );
}

static void test_XError( void )
{
    IXError *xerror = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XErrorImpl, &IID_IXError, (void **)&xerror );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XErrorImpl ) );
        return;
    }
    if (!xerror) return;

    check_interface( xerror, &IID_IUnknown );
    check_interface( xerror, &IID_IXError );

    IXError_Release( xerror );
}

static void test_XGame( void )
{
    IXGame *xgame = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XGameImpl, &IID_IXGame, (void **)&xgame );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XGameImpl ) );
        return;
    }
    if (!xgame) return;

    check_interface( xgame, &IID_IUnknown );
    check_interface( xgame, &IID_IXGame );
    flaky check_interface( xgame, &IID_IXGame2 );
    flaky check_interface( xgame, &IID_IXGame3 );

    IXGame_Release( xgame );
}

static void test_XLauncher( void )
{
    IXLauncher *xlauncher = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XLauncherImpl, &IID_IXLauncher, (void **)&xlauncher );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XLauncherImpl ) );
        return;
    }
    if (!xlauncher) return;

    check_interface( xlauncher, &IID_IUnknown );
    check_interface( xlauncher, &IID_IXLauncher );

    IXLauncher_Release( xlauncher );
}

static void test_XThreading( void )
{
    IXThreading *xthreading = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreading, (void **)&xthreading );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XThreadingImpl ) );
        return;
    }
    if (!xthreading) return;

    check_interface( xthreading, &IID_IUnknown );
    check_interface( xthreading, &IID_IXThreading );

    IXThreading_Release( xthreading );
}

static void test_XUser( void )
{
    IXUser *xuser = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XUserImpl, &IID_IXUser, (void **)&xuser );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XUserImpl ) );
        return;
    }
    if (!xuser) return;

    check_interface( xuser, &IID_IUnknown );
    check_interface( xuser, &IID_IXUser );
    flaky check_interface( xuser, &IID_IXUser2 );
    flaky check_interface( xuser, &IID_IXUser3 );
    flaky check_interface( xuser, &IID_IXUser4 );
    flaky check_interface( xuser, &IID_IXUser5 );
    flaky check_interface( xuser, &IID_IXUser6 );
    flaky check_interface( xuser, &IID_IXUserGamertag );

    IXUser_Release( xuser );
}

static void test_XUserDevice( void )
{
    IXUserDevice *xuserdevice = NULL;
    HRESULT hr;

    hr = QueryApiImpl( &CLSID_XUserDeviceImpl, &IID_IXUserDevice, (void **)&xuserdevice );
    ok( hr == S_OK || broken( hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) ), "got hr %#lx.\n", hr );
    if (hr == HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED ) )
    {
        win_skip( "clsid %s not supported, skipping tests.\n", debugstr_guid( &CLSID_XUserDeviceImpl ) );
        return;
    }
    if (!xuserdevice) return;

    check_interface( xuserdevice, &IID_IUnknown );
    check_interface( xuserdevice, &IID_IXUserDevice );
    flaky check_interface( xuserdevice, &IID_IXUserDevice2 );

    IXUserDevice_Release( xuserdevice );
}

START_TEST(xgameruntime)
{
    HRESULT hr;

    if (!test_Init())
    {
        win_skip( "Failed to initialize xgameruntime, skipping tests.\n" );
        return;
    }

    test_XAccessibility();
    test_XAppCapture();
    test_XDisplay();
    test_XError();
    test_XGame();
    test_XLauncher();
    test_XThreading();
    test_XUser();
    test_XUserDevice();

    hr = UninitializeApiImpl();
    ok( hr == S_OK, "got hr %#lx.\n", hr );
}
