/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XUser
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

#include "../../private.h"

#include <time.h>
#include <winhttp.h>

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

const CHAR *msaAppId = "0000000040159362";

static const WCHAR *ACCEPT_JSON[] = { L"application/json", NULL };
static const WCHAR *CT_JSON = L"Content-Type: application/json";
static const WCHAR *CT_FORM_URLENCODED = L"Content-Type: application/x-www-form-urlencoded";

static HRESULT HttpRequest( const WCHAR *method, const WCHAR *domain, const WCHAR *object, CHAR *data, const WCHAR *headers, const WCHAR **accept, CHAR **buffer, SIZE_T *used )
{
    HINTERNET connection = NULL, request = NULL, session = NULL;
    DWORD size = sizeof( DWORD ), status;
    CHAR *temp_buffer = NULL;
    SIZE_T temp_used = 0;
    HRESULT hr = S_OK;

    if (!(session = WinHttpOpen( L"curl/1.0", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0 )))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto _CLEANUP;
    }

    if (!(connection = WinHttpConnect( session, domain, INTERNET_DEFAULT_HTTPS_PORT, 0 )))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto _CLEANUP;
    }

    if (!(request = WinHttpOpenRequest( connection, method, object, NULL, WINHTTP_NO_REFERER, accept, WINHTTP_FLAG_SECURE )))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto _CLEANUP;
    }


    if (!WinHttpSendRequest( request, headers, -1, data, strlen( data ), strlen( data ), 0 ))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto _CLEANUP;
    }

    if (!WinHttpReceiveResponse( request, NULL ))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto _CLEANUP;
    }

    if (!WinHttpQueryHeaders( request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &status, &size, WINHTTP_NO_HEADER_INDEX ))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto _CLEANUP;
    }

    if (status != 200)
    {
        hr = E_FAIL;
        goto _CLEANUP;
    }

    /* buffer response data */
    do
    {
        if (!WinHttpQueryDataAvailable( request, &size ))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto _CLEANUP;
        }

        if (!size) break;
        if (!(temp_buffer = realloc( temp_buffer, temp_used + size )))
        {
            hr = E_OUTOFMEMORY;
            goto _CLEANUP;
        }

        if (!WinHttpReadData( request, temp_buffer + temp_used, size, &size ))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto _CLEANUP;
        }

        temp_used += size;
    }
    while (size);

    *buffer = temp_buffer;
    *used = temp_used;

_CLEANUP:

    if (request) WinHttpCloseHandle( request );
    if (session) WinHttpCloseHandle( session );
    if (connection) WinHttpCloseHandle( connection );
    if (SUCCEEDED(hr)) return hr;
    if (temp_buffer) free( temp_buffer );
    return hr;
}

static HRESULT MultiByteToHSTRING( const CHAR *str, UINT32 str_size, HSTRING *hstr )
{
    UINT32 wstr_size;
    WCHAR *wstr;
    HRESULT hr;

    if (!(wstr_size = MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS, str, str_size, NULL, 0 )))
        return HRESULT_FROM_WIN32( GetLastError() );

    if (!(wstr = calloc( wstr_size, sizeof(WCHAR) ))) return E_OUTOFMEMORY;

    if (!(wstr_size = MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS, str, str_size, wstr, wstr_size )))
    {
        free( wstr );
        return HRESULT_FROM_WIN32( GetLastError() );
    }

    hr = WindowsCreateString( wstr, wstr_size, hstr );
    free( wstr );
    return hr;
}

static HRESULT HSTRINGToMultiByte( HSTRING hstr, CHAR **str, UINT32 *str_size )
{
    UINT32 wstr_size;
    const WCHAR *wstr = WindowsGetStringRawBuffer( hstr, &wstr_size );

    if (!(*str_size = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wstr, wstr_size, NULL, 0, NULL, NULL )))
        return HRESULT_FROM_WIN32( GetLastError() );

    if (!(*str = calloc( 1, *str_size ))) return E_OUTOFMEMORY;

    if (!(*str_size = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wstr, wstr_size, *str, *str_size, NULL, NULL )))
    {
        free( *str );
        return HRESULT_FROM_WIN32( GetLastError() );
    }

    return S_OK;
}

#define GetJsonValue_( obj_type, ret_type )                                                                 \
static inline HRESULT GetJson##obj_type##Value( IJsonObject *object, const WCHAR *key, ret_type value )     \
{                                                                                                           \
    HSTRING_HEADER key_hdr;                                                                                 \
    HSTRING key_hstr;                                                                                       \
    HRESULT hr;                                                                                             \
                                                                                                            \
    if (FAILED(hr = WindowsCreateStringReference( key, wcslen( key ), &key_hdr, &key_hstr ))) return hr;    \
    return IJsonObject_GetNamed##obj_type( object, key_hstr, value );                                       \
}

GetJsonValue_( String, HSTRING* )
GetJsonValue_( Number, DOUBLE* )

static HRESULT ParseJsonObject( const CHAR *str, SIZE_T str_size, IJsonObject **object )
{
    const WCHAR *class_name = RuntimeClass_Windows_Data_Json_JsonValue;
    IJsonValueStatics *statics;
    HSTRING_HEADER class_hdr;
    HSTRING class, content;
    IJsonValue *value;
    HRESULT hr;

    if (FAILED(hr = WindowsCreateStringReference( class_name, wcslen( class_name ), &class_hdr, &class ))) return hr;
    if (FAILED(hr = RoGetActivationFactory( class, &IID_IJsonValueStatics, (void **)&statics ))) return hr;
    if (FAILED(hr = MultiByteToHSTRING( str, str_size, &content )))
    {
        IJsonValueStatics_Release( statics );
        return hr;
    }

    hr = IJsonValueStatics_Parse( statics, content, &value );
    IJsonValueStatics_Release( statics );
    WindowsDeleteString( content );
    if (FAILED(hr)) return hr;

    hr = IJsonValue_GetObject( value, object );
    IJsonValue_Release( value );
    return hr;
}

struct user
{
    IUser IUser_iface;
    LONG ref;

    DOUBLE interval;
    time_t oauth_expiry;
    HSTRING device_code;
    HSTRING access_token;
    HSTRING refresh_token;
    HSTRING user_token;
};

static inline struct user *impl_from_IUser( IUser *iface )
{
    return CONTAINING_RECORD( iface, struct user, IUser_iface );
}

static HRESULT WINAPI user_QueryInterface( IUser *iface, REFIID iid, void **out )
{
    struct user *impl = impl_from_IUser( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IUser    ))
    {
        IUser_AddRef( *out = &impl->IUser_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI user_AddRef( IUser *iface )
{
    struct user *impl = impl_from_IUser( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI user_Release( IUser *iface )
{
    struct user *impl = impl_from_IUser( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    if (!ref)
    {
        if (impl->device_code) WindowsDeleteString( impl->device_code );
        if (impl->access_token) WindowsDeleteString( impl->access_token );
        if (impl->refresh_token) WindowsDeleteString( impl->refresh_token );
        if (impl->user_token) WindowsDeleteString( impl->user_token );
        free( impl );
    }
    return ref;
}

static HRESULT WINAPI user_RequestOAuthCode( IUser *iface, HSTRING *user, HSTRING *uri )
{
    const CHAR *template = "scope=service::user.auth.xboxlive.com::MBI_SSL&response_type=device_code&client_id=";
    struct user *impl = impl_from_IUser( iface );
    CHAR *buffer = NULL, *data;
    IJsonObject *object = NULL;
    SIZE_T size = 0;
    HRESULT hr;

    TRACE( "iface %p, user %p, uri %p.\n", iface, user, uri );

    data = calloc( strlen( template ) + strlen( msaAppId ) + 1, sizeof( CHAR ) );
    strcpy( data, template );
    strcat( data, msaAppId );

    hr = HttpRequest(
        L"POST", L"login.live.com", L"/oauth20_connect.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, &buffer, &size
    );

    free( data );
    if (FAILED(hr)) return hr;

    hr = ParseJsonObject( buffer, size, &object );
    free( buffer );
    if (FAILED(hr)) return hr;

    impl->device_code = NULL;
    *user = NULL;
    *uri = NULL;

    if (FAILED(hr = GetJsonStringValue( object, L"device_code", &impl->device_code ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonStringValue( object, L"verification_uri", uri ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonNumberValue( object, L"interval", &impl->interval ))) goto _CLEANUP;
    hr = GetJsonStringValue( object, L"user_code", user );

_CLEANUP:

    IJsonObject_Release( object );
    if (SUCCEEDED(hr)) return hr;
    if (*uri) WindowsDeleteString( *uri );
    if (*user) WindowsDeleteString( *user );
    if (impl->device_code) WindowsDeleteString( impl->device_code );
    return hr;
}

static HRESULT WINAPI user_RequestOAuthToken( IUser *iface )
{
    const CHAR *template = "grant_type=device_code&device_code=";
    CHAR *buffer = NULL, *data, *device_code = NULL;
    HSTRING new_access = NULL, new_refresh = NULL;
    struct user *impl = impl_from_IUser( iface );
    UINT32 device_code_size = 0;
    IJsonObject *object;
    DOUBLE delta = 0;
    SIZE_T size = 0;
    time_t expiry;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    if (FAILED(hr = HSTRINGToMultiByte( impl->device_code, &device_code, &device_code_size ))) return hr;

    if (!(data = calloc( strlen( template ) + device_code_size + strlen( "&client_id=" ) + strlen( msaAppId ) + 1, sizeof(CHAR) )))
    {
        free( device_code );
        return E_OUTOFMEMORY;
    }

    strcpy( data, template );
    strncat( data, device_code, device_code_size );
    strcat( data, "&client_id=" );
    strcat( data, msaAppId );
    free( device_code );

    while (TRUE)
    {
        if (SUCCEEDED(hr = HttpRequest(
            L"POST", L"login.live.com", L"/oauth20_token.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, &buffer, &size
        ))) break;
        Sleep( impl->interval * 1000 );
    }

    free( data );
    hr = ParseJsonObject( buffer, size, &object );
    free( buffer );
    if (FAILED(hr)) return hr;

    if (FAILED(hr = GetJsonStringValue( object, L"refresh_token", &new_refresh ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonStringValue( object, L"access_token", &new_access ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonNumberValue( object, L"expires_in", &delta ))) goto _CLEANUP;

    if ((expiry = time(NULL)) == -1) hr = E_FAIL;
    else impl->oauth_expiry = expiry + delta;

_CLEANUP:

    IJsonObject_Release( object );
    if (SUCCEEDED(hr))
    {
        impl->refresh_token = new_refresh;
        impl->access_token = new_access;
        return hr;
    }

    if (new_refresh) WindowsDeleteString( new_refresh );
    if (new_access) WindowsDeleteString( new_access );
    return hr;
}

static HRESULT WINAPI user_RequestXToken( IUser *iface, const WCHAR *domain, const WCHAR *path, const CHAR *relyingParty, const CHAR *props, IUnknown **object )
{
    const CHAR *template = "{\"TokenType\":\"JWT\",\"RelyingParty\":\"";
    CHAR *buffer, *data;
    SIZE_T size;
    HRESULT hr;

    TRACE( "iface %p, domain %s, path %s, relyingParty %s, props %s, object %p.\n", iface, debugstr_w( domain ), debugstr_w( path ), debugstr_a( relyingParty ), debugstr_a( props ), object );

    if (!(data = calloc(
        strlen( template ) + strlen( relyingParty ) + strlen( "\",\"Properties\":}" ) + strlen( props ) + 1, sizeof(CHAR)
    ))) return E_OUTOFMEMORY;

    strcpy( data, template );
    strcat( data, relyingParty );
    strcat( data, "\",\"Properties\":" );
    strcat( data, props );
    strcat( data, "}" );

    if (FAILED(hr = HttpRequest( L"POST", domain, path, data, CT_JSON, ACCEPT_JSON, &buffer, &size ))) return hr;

    hr = ParseJsonObject( buffer, size, (IJsonObject **)object );
    free( buffer );
    return hr;
}

static HRESULT WINAPI user_RefreshOAuthToken( IUser *iface )
{
    const CHAR *template = "grant_type=refresh_token&scope=service::user.auth.xboxlive.com::MBI_SSL&client_id=";
    CHAR *buffer = NULL, *data, *refresh_str = NULL;
    HSTRING new_access = NULL, new_refresh = NULL;
    struct user *impl = impl_from_IUser( iface );
    IJsonObject *object = NULL;
    UINT32 refresh_size = 0;
    DOUBLE delta = 0;
    SIZE_T size = 0;
    time_t expiry;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    if (FAILED(hr = HSTRINGToMultiByte( impl->refresh_token, &refresh_str, &refresh_size ))) return hr;

    if (!(data = calloc(
        strlen( template ) + strlen( msaAppId ) + strlen( "&refresh_token=" ) + refresh_size + 1, sizeof(CHAR)
    ))) return E_OUTOFMEMORY;

    strcpy( data, template );
    strcat( data, msaAppId );
    strcat( data, "&refresh_token=" );
    strncat( data, refresh_str, refresh_size );

    hr = HttpRequest(
        L"POST", L"login.live.com", L"/oauth20_token.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, &buffer, &size
    );

    free(data);
    if (FAILED(hr)) return hr;

    hr = ParseJsonObject( buffer, size, &object );
    free( buffer );
    if (FAILED(hr)) return hr;

    if (FAILED(hr = GetJsonStringValue( object, L"refresh_token", &new_refresh ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonStringValue( object, L"access_token", &new_access ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonNumberValue( object, L"expires_in", &delta ))) goto _CLEANUP;

    if ((expiry = time(NULL)) == -1) hr = E_FAIL;
    else impl->oauth_expiry = expiry + delta;

_CLEANUP:

    IJsonObject_Release( object );
    if (SUCCEEDED(hr))
    {
        impl->refresh_token = new_refresh;
        impl->access_token = new_access;
        return hr;
    }

    if (new_refresh) WindowsDeleteString( new_refresh );
    if (new_access) WindowsDeleteString( new_access );
    return hr;
}

static HRESULT WINAPI user_RefreshUserToken( IUser *iface )
{
    const CHAR *template = "{\"AuthMethod\":\"RPS\",\"SiteName\":\"user.auth.xboxlive.com\",\"RpsTicket\":\"";
    struct user *impl = impl_from_IUser( iface );
    CHAR *props, *token_str;
    IJsonObject *object;
    UINT32 token_size;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    if (FAILED(hr = HSTRINGToMultiByte( impl->access_token, &token_str, &token_size ))) return hr;
    if (!(props = calloc( strlen( template ) + token_size + strlen( "\"}" ), sizeof(CHAR) )))
    {
        free( token_str );
        return E_OUTOFMEMORY;
    }

    strcpy( props, template );
    strncat( props, token_str, token_size );
    strcat( props, "\"}" );
    free( token_str );

    hr = IUser_RequestXToken( iface, L"user.auth.xboxlive.com", L"/user/authenticate", "http://auth.xboxlive.com", props, (IUnknown **)&object );
    free( props );
    if (FAILED(hr)) return hr;

    hr = GetJsonStringValue( object, L"Token", &impl->user_token );
    IJsonObject_Release( object );
    return hr;
}

static HRESULT WINAPI user_RefreshXstsToken( IUser *iface )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI user_get_Authorization( IUser *iface, HSTRING *value )
{
    FIXME( "iface %p, value %p stub!\n", iface, value );
    return E_NOTIMPL;
}

static const struct IUserVtbl user_vtbl =
{
    user_QueryInterface,
    user_AddRef,
    user_Release,
    /* IUser methods */
    user_RequestOAuthCode,
    user_RequestOAuthToken,
    user_RequestXToken,
    user_RefreshOAuthToken,
    user_RefreshUserToken,
    user_RefreshXstsToken,
    user_get_Authorization,
};

static HRESULT LoadDefaultUser( XUserHandle *user )
{
    struct user *impl;
    IUser *iface;
    HRESULT hr;

    TRACE( "user %p.\n", user );

    if (!(impl = calloc( 1, sizeof(*impl) ))) return E_OUTOFMEMORY;

    impl->IUser_iface.lpVtbl = &user_vtbl;
    impl->ref = 1;

    impl->device_code = NULL;
    impl->access_token = NULL;
    impl->refresh_token = NULL;
    impl->user_token = NULL;

    iface = &impl->IUser_iface;

    if (FAILED(hr = IUser_RefreshOAuthToken( iface ))) goto _CLEANUP;
    hr = IUser_RefreshUserToken( iface );

_CLEANUP:

    if (SUCCEEDED(hr)) *user = (XUserHandle)impl;
    else IUser_Release( iface );
    return hr;
}

struct x_user
{
    IXUser6 IXUser_iface;
    IXUserGamertag IXUserGamertag_iface;
    LONG ref;
};

static inline struct x_user *impl_from_IXUser( IXUser6 *iface )
{
    return CONTAINING_RECORD( iface, struct x_user, IXUser_iface );
}

static HRESULT WINAPI x_user_QueryInterface( IXUser6 *iface, REFIID iid, void **out )
{
    struct x_user *impl = impl_from_IXUser( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown    ) ||
        IsEqualGUID( iid, &IID_IXUser  ) ||
        IsEqualGUID( iid, &IID_IXUser2 ) ||
        IsEqualGUID( iid, &IID_IXUser3 ) ||
        IsEqualGUID( iid, &IID_IXUser4 ) ||
        IsEqualGUID( iid, &IID_IXUser5 ) ||
        IsEqualGUID( iid, &IID_IXUser6 ))
    {
        IXUser6_AddRef( *out = &impl->IXUser_iface );
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_IXUserGamertag ))
    {
        IXUserGamertag_AddRef( *out = &impl->IXUserGamertag_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_user_AddRef( IXUser6 *iface )
{
    struct x_user *impl = impl_from_IXUser( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_user_Release( IXUser6 *iface )
{
    struct x_user *impl = impl_from_IXUser( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_user_XUserDuplicateHandle( IXUser6 *iface, XUserHandle handle, XUserHandle *duplicatedHandle )
{
    TRACE( "iface %p, handle %p, duplicatedHandle %p.\n", iface, handle, duplicatedHandle );
    if (!handle || !duplicatedHandle) return E_POINTER;
    IUser_AddRef( &((struct user *)handle)->IUser_iface );
    *duplicatedHandle = handle;
    return S_OK;
}

static void WINAPI x_user_XUserCloseHandle( IXUser6 *iface, XUserHandle user )
{
    TRACE( "iface %p, user %p.\n", iface, user );
    if (!user) return;
    IUser_Release( &((struct user *)user)->IUser_iface );
}

static INT32 WINAPI x_user_XUserCompare( IXUser6 *iface, XUserHandle user1, XUserHandle user2 )
{
    FIXME( "iface %p, user1 %p, user2 %p stub!\n", iface, user1, user2 );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMaxUsers( IXUser6 *iface, UINT32 *maxUsers )
{
    FIXME( "iface %p, maxUsers %p stub!\n", iface, maxUsers );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserAddAsync( IXUser6 *iface, XUserAddOptions options, XAsyncBlock *async )
{
    FIXME( "iface %p, options %d, async %p stub!\n", iface, options, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserAddResult( IXUser6 *iface, XAsyncBlock *async, XUserHandle *newUser )
{
    FIXME( "iface %p, async %p, newUser %p stub!\n", iface, async, newUser );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetLocalId( IXUser6 *iface, XUserHandle user, XUserLocalId *userLocalId )
{
    FIXME( "iface %p, user %p, userLocalId %p stub!\n", iface, user, userLocalId );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserFindUserByLocalId( IXUser6 *iface, XUserLocalId userLocalId, XUserHandle *handle )
{
    FIXME( "iface %p, userLocalId %p, handle %p stub!\n", iface, &userLocalId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetId( IXUser6 *iface, XUserHandle user, UINT64 *userId )
{
    FIXME( "iface %p, user %p, userId %p stub!\n", iface, user, userId );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserFindUserById( IXUser6 *iface, UINT64 userId, XUserHandle *handle )
{
    FIXME( "iface %p, userId %llu, handle %p stub!\n", iface, userId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetIsGuest( IXUser6 *iface, XUserHandle user, boolean *isGuest )
{
    FIXME( "iface %p, user %p, isGuest %p stub!\n", iface, user, isGuest );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetState( IXUser6 *iface, XUserHandle user, XUserState *state )
{
    FIXME( "iface %p, user %p, state %p stub!\n", iface, user, state );
    return E_NOTIMPL;
}

static HRESULT WINAPI __PADDING__( IXUser6 *iface )
{
    WARN( "iface %p padding function called! It's unknown what this function does\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureAsync( IXUser6 *iface, XUserHandle user, XUserGamerPictureSize pictureSize, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, pictureSize %d, async %p stub!\n", iface, user, pictureSize, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResultSize( IXUser6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResult( IXUser6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetAgeGroup( IXUser6 *iface, XUserHandle user, XUserAgeGroup *ageGroup )
{
    FIXME( "iface %p, user %p, ageGroup %p stub!\n", iface, user, ageGroup );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserCheckPrivilege( IXUser6 *iface, XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, boolean *hasPrivilege, XUserPrivilegeDenyReason *reason )
{
    FIXME( "iface %p, user %p, options %d, privilege %d, hasPrivilege %p, reason %p stub!\n", iface, user, options, privilege, hasPrivilege, reason );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolvePrivilegeWithUiAsync( IXUser6 *iface, XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, privilege %d, async %p stub!\n", iface, user, options, privilege, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolvePrivilegeWithUiResult( IXUser6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureAsync( IXUser6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const CHAR *method, const CHAR *url, SIZE_T headerCount, const XUserGetTokenAndSignatureHttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, method %s, url %s, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p stub!\n", iface, user, options, method, url, headerCount, headers, bodySize, bodyBuffer, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResultSize( IXUser6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResult( IXUser6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureData **ptrToBuffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Async( IXUser6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const WCHAR *method, const WCHAR *url, SIZE_T headerCount, const XUserGetTokenAndSignatureUtf16HttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, method %hs, url %hs, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p stub!\n", iface, user, options, method, url, headerCount, headers, bodySize, bodyBuffer, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16ResultSize( IXUser6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Result( IXUser6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureUtf16Data **ptrToBuffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiAsync( IXUser6 *iface, XUserHandle user, const CHAR *url, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, url %s, async %p stub!\n", iface, user, url, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiResult( IXUser6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiUtf16Async( IXUser6 *iface, XUserHandle user, const WCHAR *url, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, url %hs, async %p stub!\n", iface, user, url, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiUtf16Result( IXUser6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserRegisterForChangeEvent( IXUser6 *iface, XTaskQueueHandle queue, void *context, XUserChangeEventCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, context %p, callback %p, token %p stub!\n", iface, context, callback, token );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_XUserUnregisterForChangeEvent( IXUser6 *iface, XTaskQueueRegistrationToken token, boolean wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_user_XUserGetSignOutDeferral( IXUser6 *iface, XUserSignOutDeferralHandle *deferral )
{
    FIXME( "iface %p, deferral %p stub!\n", iface, deferral );
    return E_GAMEUSER_DEFERRAL_NOT_AVAILABLE;
}

static void WINAPI x_user_XUserCloseSignOutDeferralHandle( IXUser6 *iface, XUserSignOutDeferralHandle deferral )
{
    FIXME( "iface %p, deferral %p stub!\n", iface, deferral );
}

static HRESULT WINAPI x_user_XUserAddByIdWithUiAsync( IXUser6 *iface, UINT64 userId, XAsyncBlock *async )
{
    FIXME( "iface %p, userId %llu, async %p stub!\n", iface, userId, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserAddByIdWithUiResult( IXUser6 *iface, XAsyncBlock *async, XUserHandle *newUser )
{
    FIXME( "iface %p, async %p, newUser %p stub!\n", iface, async, newUser );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyAsync( IXUser6 *iface, XUserHandle user, XUserGetMsaTokenSilentlyOptions options, const CHAR *scope, XAsyncBlock *async )
{
    FIXME( "iface %p, options %u, scope %s, async %p stub!\n", iface, options, scope, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResult( IXUser6 *iface, XAsyncBlock *async, SIZE_T resultTokenSize, CHAR *resultToken, SIZE_T *resultTokenUsed )
{
    FIXME( "iface %p, async %p, resultTokenSize %Iu, resultToken %p, resultTokenUsed %p stub!\n", iface, async, resultTokenSize, resultToken, resultTokenUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResultSize( IXUser6 *iface, XAsyncBlock *async, SIZE_T *tokenSize )
{
    FIXME( "iface %p, async %p, tokenSize %p stub!\n", iface, async, tokenSize );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_user_XUserIsStoreUser( IXUser6 *iface, XUserHandle user )
{
    FIXME( "iface %p, user %p stub!\n", iface, user );
    return TRUE;
}

static HRESULT WINAPI x_user_XUserPlatformRemoteConnectSetEventHandlers( IXUser6 *iface, XTaskQueueHandle queue, XUserPlatformRemoteConnectEventHandlers *handlers )
{
    FIXME( "iface %p, queue %p, handlers %p stub!\n", iface, queue, handlers );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformRemoteConnectCancelPrompt( IXUser6 *iface, XUserPlatformOperation operation )
{
    FIXME( "iface %p, operation %p stub!\n", iface, operation );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformSpopPromptSetEventHandlers( IXUser6 *iface, XTaskQueueHandle queue, XUserPlatformSpopPromptEventHandler *handler, void *context )
{
    FIXME( "iface %p, queue %p, handler %p, context %p stub!\n", iface, queue, handler, context );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformSpopPromptComplete( IXUser6 *iface, XUserPlatformOperation operation, XUserPlatformOperationResult result )
{
    FIXME( "iface %p iface, operation %p, result %d stub!\n", iface, operation, result );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_user_XUserIsSignOutPresent( IXUser6 *iface )
{
    FIXME( "iface %p stub!\n", iface );
    return FALSE;
}

static HRESULT WINAPI x_user_XUserSignOutAsync( IXUser6 *iface, XUserHandle user, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, async %p stub!\n", iface, user, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserSignOutResult( IXUser6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static const struct IXUser6Vtbl x_user_vtbl =
{
    x_user_QueryInterface,
    x_user_AddRef,
    x_user_Release,
    /* IXUser methods */
    x_user_XUserDuplicateHandle,
    x_user_XUserCloseHandle,
    x_user_XUserCompare,
    x_user_XUserGetMaxUsers,
    x_user_XUserAddAsync,
    x_user_XUserAddResult,
    x_user_XUserGetLocalId,
    x_user_XUserFindUserByLocalId,
    x_user_XUserGetId,
    x_user_XUserFindUserById,
    x_user_XUserGetIsGuest,
    x_user_XUserGetState,
    __PADDING__,
    x_user_XUserGetGamerPictureAsync,
    x_user_XUserGetGamerPictureResultSize,
    x_user_XUserGetGamerPictureResult,
    x_user_XUserGetAgeGroup,
    x_user_XUserCheckPrivilege,
    x_user_XUserResolvePrivilegeWithUiAsync,
    x_user_XUserResolvePrivilegeWithUiResult,
    x_user_XUserGetTokenAndSignatureAsync,
    x_user_XUserGetTokenAndSignatureResultSize,
    x_user_XUserGetTokenAndSignatureResult,
    x_user_XUserGetTokenAndSignatureUtf16Async,
    x_user_XUserGetTokenAndSignatureUtf16ResultSize,
    x_user_XUserGetTokenAndSignatureUtf16Result,
    x_user_XUserResolveIssueWithUiAsync,
    x_user_XUserResolveIssueWithUiResult,
    x_user_XUserResolveIssueWithUiUtf16Async,
    x_user_XUserResolveIssueWithUiUtf16Result,
    x_user_XUserRegisterForChangeEvent,
    x_user_XUserUnregisterForChangeEvent,
    x_user_XUserGetSignOutDeferral,
    x_user_XUserCloseSignOutDeferralHandle,
    /* IXUser2 methods */
    x_user_XUserAddByIdWithUiAsync,
    x_user_XUserAddByIdWithUiResult,
    /* IXUser3 methods */
    x_user_XUserGetMsaTokenSilentlyAsync,
    x_user_XUserGetMsaTokenSilentlyResult,
    x_user_XUserGetMsaTokenSilentlyResultSize,
    /* IXUser4 methods */
    x_user_XUserIsStoreUser,
    /* IXUser5 methods */
    x_user_XUserPlatformRemoteConnectSetEventHandlers,
    x_user_XUserPlatformRemoteConnectCancelPrompt,
    x_user_XUserPlatformSpopPromptSetEventHandlers,
    x_user_XUserPlatformSpopPromptComplete,
    /* IXUser6 methods */
    x_user_XUserIsSignOutPresent,
    x_user_XUserSignOutAsync,
    x_user_XUserSignOutResult,
};

static inline struct x_user *impl_from_IXUserGamertag( IXUserGamertag *iface )
{
    return CONTAINING_RECORD( iface, struct x_user, IXUserGamertag_iface );
}

static HRESULT WINAPI x_user_gamertag_QueryInterface( IXUserGamertag *iface, REFIID riid, void **out )
{
    struct x_user *impl = impl_from_IXUserGamertag( iface );
    return IXUser6_QueryInterface( &impl->IXUser_iface, riid, out );
}

static ULONG WINAPI x_user_gamertag_AddRef( IXUserGamertag *iface )
{
    struct x_user *impl = impl_from_IXUserGamertag( iface );
    return IXUser6_AddRef( &impl->IXUser_iface );
}

static ULONG WINAPI x_user_gamertag_Release( IXUserGamertag *iface )
{
    struct x_user *impl = impl_from_IXUserGamertag( iface );
    return IXUser6_Release( &impl->IXUser_iface );
}

static HRESULT WINAPI x_user_gamertag_XUserGetGamertag( IXUserGamertag *iface, XUserHandle user, XUserGamertagComponent gamertagComponent, SIZE_T gamertagSize, CHAR *gamertag, SIZE_T *gamertagUsed )
{
    FIXME( "iface %p, user %p, gamertagComponent %d, gamertagSize %Iu, gamertag %p, gamertagUsed %p stub!\n", iface, user, gamertagComponent, gamertagSize, gamertag, gamertagUsed );
    return E_NOTIMPL;
}

static const struct IXUserGamertagVtbl x_user_gamertag_vtbl =
{
    x_user_gamertag_QueryInterface,
    x_user_gamertag_AddRef,
    x_user_gamertag_Release,
    /* IXUserGamertag methods */
    x_user_gamertag_XUserGetGamertag,
};

struct x_user_device
{
    IXUserDevice IXUserDevice_iface;
    LONG ref;
};

static inline struct x_user_device *impl_from_IXUserDevice( IXUserDevice *iface )
{
    return CONTAINING_RECORD( iface, struct x_user_device, IXUserDevice_iface );
}

static HRESULT WINAPI x_user_device_QueryInterface( IXUserDevice *iface, REFIID iid, void **out )
{
    struct x_user_device *impl = impl_from_IXUserDevice( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown         ) ||
        IsEqualGUID( iid, &IID_IXUserDevice ))
    {
        IXUserDevice_AddRef( *out = &impl->IXUserDevice_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_user_device_AddRef( IXUserDevice *iface )
{
    struct x_user_device *impl = impl_from_IXUserDevice( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_user_device_Release( IXUserDevice *iface )
{
    struct x_user_device *impl = impl_from_IXUserDevice( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_user_device_XUserFindForDevice( IXUserDevice *iface, const APP_LOCAL_DEVICE_ID *deviceId, XUserHandle *handle )
{
    FIXME( "iface %p, deviceId %p, handle %p stub!\n", iface, deviceId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_device_XUserRegisterForDeviceAssociationChanged( IXUserDevice *iface, XTaskQueueHandle queue, void *context, XUserDeviceAssociationChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_device_XUserUnregisterForDeviceAssociationChanged( IXUserDevice *iface, XTaskQueueRegistrationToken token, boolean wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_user_device_XUserGetDefaultAudioEndpointUtf16( IXUserDevice *iface, XUserLocalId user, XUserDefaultAudioEndpointKind defaultAudioEndpointKind, SIZE_T endpointIdUtf16Count, WCHAR *endpointIdUtf16, SIZE_T *endpointIdUtf16Used )
{
    FIXME( "iface %p, user %p, defaultAudioEndpointKind %d, endpointIdUtf16Count %Iu, endpointIdUtf16 %p, endpointIdUtf16used %p stub!\n", iface, &user, defaultAudioEndpointKind, endpointIdUtf16Count, endpointIdUtf16, endpointIdUtf16Used );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_device_XUserRegisterForDefaultAudioEndpointUtf16Changed( IXUserDevice *iface, XTaskQueueHandle queue, void *context, XUserDefaultAudioEndpointUtf16ChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_device_XUserUnregisterForDefaultAudioEndpointUtf16Changed( IXUserDevice *iface, XTaskQueueRegistrationToken token, boolean wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_user_device_XUserFindControllerForUserWithUiAsync( IXUserDevice *iface, XUserHandle user, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, async %p stub!\n", iface, user, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_device_XUserFindControllerForUserWithUiResult( IXUserDevice *iface, XAsyncBlock *async, APP_LOCAL_DEVICE_ID *deviceId )
{
    FIXME( "iface %p async %p deviceId %p stub!\n", iface, async, deviceId );
    return E_NOTIMPL;
}

static const struct IXUserDeviceVtbl x_user_device_vtbl =
{
    x_user_device_QueryInterface,
    x_user_device_AddRef,
    x_user_device_Release,
    /* IXUserDevice methods */
    x_user_device_XUserFindForDevice,
    x_user_device_XUserRegisterForDeviceAssociationChanged,
    x_user_device_XUserUnregisterForDeviceAssociationChanged,
    x_user_device_XUserGetDefaultAudioEndpointUtf16,
    x_user_device_XUserRegisterForDefaultAudioEndpointUtf16Changed,
    x_user_device_XUserUnregisterForDefaultAudioEndpointUtf16Changed,
    x_user_device_XUserFindControllerForUserWithUiAsync,
    x_user_device_XUserFindControllerForUserWithUiResult,
};

static struct x_user x_user =
{
    {&x_user_vtbl},
    {&x_user_gamertag_vtbl},
    0,
};

static struct x_user_device x_user_device =
{
    {&x_user_device_vtbl},
    0,
};

IXUser6 *x_user_impl = &x_user.IXUser_iface;
IXUserDevice *x_user_device_impl = &x_user_device.IXUserDevice_iface;
