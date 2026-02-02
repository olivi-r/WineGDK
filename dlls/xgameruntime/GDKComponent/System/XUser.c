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

#include <errno.h>
#include <time.h>
#include <winhttp.h>

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

const CHAR *msaAppId = "0000000040159362";

static const WCHAR *ACCEPT_JSON[] = { L"application/json", NULL };
static const WCHAR *CT_JSON = L"Content-Type: application/json";
static const WCHAR *CT_FORM_URLENCODED = L"Content-Type: application/x-www-form-urlencoded";

static HRESULT HttpRequest( const WCHAR *method, const WCHAR *url, CHAR *data, const WCHAR *headers, const WCHAR **accept, void **buffer, SIZE_T *used )
{
    URL_COMPONENTS uc = { .dwStructSize = sizeof(URL_COMPONENTS), .dwHostNameLength = -1, .dwUrlPathLength = -1, .dwExtraInfoLength = -1};
    HINTERNET connection = NULL, request = NULL, session = NULL;
    DWORD size = sizeof( DWORD ), status;
    CHAR *temp_buffer = NULL;
    SIZE_T temp_used = 0;
    HRESULT hr = S_OK;
    WCHAR *object;

    TRACE( "method %s, url %s, data %s, headers %s, accept %p, buffer %p, used %p.\n", debugstr_w( method ), debugstr_w( url ), debugstr_a( data ), debugstr_w( headers ), accept, buffer, used );

    if (!WinHttpCrackUrl( url, wcslen( url ), 0, &uc )) return HRESULT_FROM_WIN32( GetLastError() );
    if (!(object = calloc( uc.dwUrlPathLength + uc.dwExtraInfoLength + 1, sizeof(WCHAR) ))) return E_OUTOFMEMORY;
    memcpy( object, uc.lpszUrlPath, uc.dwUrlPathLength );
    wcsncat( object, uc.lpszExtraInfo, uc.dwExtraInfoLength );

    if (!(session = WinHttpOpen( L"curl/1.0", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0 ))) goto _FAILED;
    if (!(connection = WinHttpConnect( session, uc.lpszHostName, INTERNET_DEFAULT_HTTPS_PORT, 0 ))) goto _FAILED;
    if (!(request = WinHttpOpenRequest( connection, method, object, NULL, WINHTTP_NO_REFERER, accept, WINHTTP_FLAG_SECURE ))) goto _FAILED;
    if (!WinHttpSendRequest( request, headers, -1, data, strlen( data ), strlen( data ), 0 )) goto _FAILED;
    if (!WinHttpReceiveResponse( request, NULL )) goto _FAILED;
    if (!WinHttpQueryHeaders( request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &status, &size, WINHTTP_NO_HEADER_INDEX )) goto _FAILED;
    if (status != 200)
    {
        hr = E_FAIL;
        goto _CLEANUP;
    }

    /* buffer response data */
    do
    {
        if (!WinHttpQueryDataAvailable( request, &size )) goto _FAILED;
        if (!size) break;
        if (!(temp_buffer = realloc( temp_buffer, temp_used + size )))
        {
            hr = E_OUTOFMEMORY;
            goto _CLEANUP;
        }

        if (!WinHttpReadData( request, temp_buffer + temp_used, size, &size )) goto _FAILED;
        temp_used += size;
    }
    while (size);

    *buffer = temp_buffer;
    *used = temp_used;
    goto _CLEANUP;

_FAILED:

    hr = HRESULT_FROM_WIN32( GetLastError() );

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

GetJsonValue_( Object, IJsonObject** )
GetJsonValue_( Array, IJsonArray** )
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

struct XUser
{
    IUser IUser_iface;
    LONG ref;

    UINT64 xuid;
    HSTRING user_hash;

    DOUBLE interval;
    time_t oauth_expiry;
    HSTRING device_code;
    HSTRING access_token;
    HSTRING refresh_token;
    HSTRING user_token;
    HSTRING xsts_token;
};

static inline struct XUser *impl_from_IUser( IUser *iface )
{
    return CONTAINING_RECORD( iface, struct XUser, IUser_iface );
}

static HRESULT WINAPI user_QueryInterface( IUser *iface, REFIID iid, void **out )
{
    struct XUser *impl = impl_from_IUser( iface );

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
    struct XUser *impl = impl_from_IUser( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI user_Release( IUser *iface )
{
    struct XUser *impl = impl_from_IUser( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    if (!ref)
    {
        if (impl->user_hash) WindowsDeleteString( impl->user_hash );
        if (impl->device_code) WindowsDeleteString( impl->device_code );
        if (impl->access_token) WindowsDeleteString( impl->access_token );
        if (impl->refresh_token) WindowsDeleteString( impl->refresh_token );
        if (impl->user_token) WindowsDeleteString( impl->user_token );
        if (impl->xsts_token) WindowsDeleteString( impl->xsts_token );
        free( impl );
    }
    return ref;
}

static HRESULT WINAPI user_RequestOAuthCode( IUser *iface, HSTRING *user, HSTRING *uri )
{
    const CHAR *template = "scope=service::user.auth.xboxlive.com::MBI_SSL&response_type=device_code&client_id=";
    struct XUser *impl = impl_from_IUser( iface );
    IJsonObject *object = NULL;
    void *buffer = NULL;
    SIZE_T size = 0;
    HRESULT hr;
    CHAR *data;

    TRACE( "iface %p, user %p, uri %p.\n", iface, user, uri );

    data = calloc( strlen( template ) + strlen( msaAppId ) + 1, sizeof( CHAR ) );
    strcpy( data, template );
    strcat( data, msaAppId );

    hr = HttpRequest( L"POST", L"login.live.com/oauth20_connect.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, &buffer, &size );
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
    HSTRING new_access = NULL, new_refresh = NULL;
    struct XUser *impl = impl_from_IUser( iface );
    CHAR *data, *device_code = NULL;
    UINT32 device_code_size = 0;
    void *buffer = NULL;
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
        if (SUCCEEDED(hr = HttpRequest( L"POST", L"login.live.com/oauth20_token.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, &buffer, &size ))) break;
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

static HRESULT WINAPI user_RequestXToken( IUser *iface, const WCHAR *url, const CHAR *relyingParty, const CHAR *props, IUnknown **object )
{
    const CHAR *template = "{\"TokenType\":\"JWT\",\"RelyingParty\":\"";
    void *buffer = NULL;
    SIZE_T size;
    HRESULT hr;
    CHAR *data;

    TRACE( "iface %p, url %s, relyingParty %s, props %s, object %p.\n", iface, debugstr_w( url ), debugstr_a( relyingParty ), debugstr_a( props ), object );

    if (!(data = calloc(
        strlen( template ) + strlen( relyingParty ) + strlen( "\",\"Properties\":}" ) + strlen( props ) + 1, sizeof(CHAR)
    ))) return E_OUTOFMEMORY;

    strcpy( data, template );
    strcat( data, relyingParty );
    strcat( data, "\",\"Properties\":" );
    strcat( data, props );
    strcat( data, "}" );

    if (FAILED(hr = HttpRequest( L"POST", url, data, CT_JSON, ACCEPT_JSON, &buffer, &size ))) return hr;

    hr = ParseJsonObject( buffer, size, (IJsonObject **)object );
    free( buffer );
    return hr;
}

static HRESULT WINAPI user_RefreshOAuthToken( IUser *iface )
{
    const CHAR *template = "grant_type=refresh_token&scope=service::user.auth.xboxlive.com::MBI_SSL&client_id=";
    HSTRING new_access = NULL, new_refresh = NULL;
    struct XUser *impl = impl_from_IUser( iface );
    CHAR *data, *refresh_str = NULL;
    IJsonObject *object = NULL;
    UINT32 refresh_size = 0;
    void *buffer = NULL;
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

    hr = HttpRequest( L"POST", L"login.live.com/oauth20_token.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, &buffer, &size );
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
    struct XUser *impl = impl_from_IUser( iface );
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

    hr = IUser_RequestXToken( iface, L"user.auth.xboxlive.com/user/authenticate", "http://auth.xboxlive.com", props, (IUnknown **)&object );
    free( props );
    if (FAILED(hr)) return hr;

    hr = GetJsonStringValue( object, L"Token", &impl->user_token );
    IJsonObject_Release( object );
    return hr;
}

static HRESULT WINAPI user_RefreshXstsToken( IUser *iface )
{
    const CHAR *template = "{\"SandboxId\":\"RETAIL\",\"UserTokens\":[\"";
    IJsonObject *child = NULL, *claims = NULL, *object;
    struct XUser *impl = impl_from_IUser( iface );
    IJsonArray *array = NULL;
    CHAR *props, *token_str;
    HSTRING xuid = NULL;
    UINT32 token_size;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    if (FAILED(hr = HSTRINGToMultiByte( impl->user_token, &token_str, &token_size ))) return hr;
    if (!(props = calloc( strlen( template ) + token_size + strlen( "\"]}" ), sizeof(CHAR) )))
    {
        free( token_str );
        return E_OUTOFMEMORY;
    }

    strcpy( props, template );
    strncat( props, token_str, token_size );
    strcat( props, "\"]}" );
    free( token_str );

    hr = IUser_RequestXToken( iface, L"xsts.auth.xboxlive.com/xsts/authorize", "http://xboxlive.com", props, (IUnknown **)&object );
    free( props );
    if (FAILED(hr)) return hr;

    if (FAILED(hr = GetJsonStringValue( object, L"Token", &impl->xsts_token ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonObjectValue( object, L"DisplayClaims", &claims ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonArrayValue( claims, L"xui", &array ))) goto _CLEANUP;
    if (FAILED(hr = IJsonArray_GetObjectAt( array, 0, &child ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonStringValue( child, L"uhs", &impl->user_hash ))) goto _CLEANUP;
    if (FAILED(hr = GetJsonStringValue( child, L"xid", &xuid ))) goto _CLEANUP;
    impl->xuid = wcstoull( WindowsGetStringRawBuffer( xuid, NULL ), NULL, 10 );
    if (errno == ERANGE) hr = E_UNEXPECTED;

_CLEANUP:

    IJsonObject_Release( object );
    if (xuid) WindowsDeleteString( xuid );
    if (array) IJsonArray_Release( array );
    if (child) IJsonObject_Release( child );
    if (claims) IJsonObject_Release( claims );
    return hr;
}

static HRESULT WINAPI user_get_Authorization( IUser *iface, HSTRING *value )
{
    struct XUser *impl = impl_from_IUser( iface );
    UINT32 token_len, user_hash_len, len;
    const WCHAR *token, *user_hash;
    WCHAR *buffer;
    HRESULT hr;

    TRACE( "iface %p, value %p.\n", iface, value );

    if (!value) return E_POINTER;
    token = WindowsGetStringRawBuffer( impl->xsts_token, &token_len );
    user_hash = WindowsGetStringRawBuffer( impl->user_hash, &user_hash_len );
    len = wcslen( L"XBL3.0 x=;" ) + user_hash_len + token_len;
    if (!(buffer = calloc( len + 1, sizeof(WCHAR) ))) return E_OUTOFMEMORY;

    wcscpy( buffer, L"XBL3.0 x=" );
    wcsncat( buffer, user_hash, user_hash_len );
    wcscat( buffer, L";" );
    wcsncat( buffer, token, token_len );

    hr = WindowsCreateString( buffer, len, value );
    free( buffer );
    return hr;
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
    CHAR *buffer = NULL;
    struct XUser *impl;
    LSTATUS status;
    IUser *iface;
    HRESULT hr;
    DWORD size;

    TRACE( "user %p.\n", user );

    if (!(impl = calloc( 1, sizeof(*impl) ))) return E_OUTOFMEMORY;

    impl->IUser_iface.lpVtbl = &user_vtbl;
    impl->ref = 1;

    impl->user_hash = NULL;
    impl->device_code = NULL;
    impl->access_token = NULL;
    impl->refresh_token = NULL;
    impl->user_token = NULL;
    impl->xsts_token = NULL;

    iface = &impl->IUser_iface;

    if (ERROR_SUCCESS != (status = RegGetValueA(
        HKEY_LOCAL_MACHINE, "Software\\Wine\\WineGDK", "RefreshToken", RRF_RT_REG_SZ, NULL, NULL, &size
    )))
    {
        hr = HRESULT_FROM_WIN32( status );
        goto _CLEANUP;
    }

    if (!(buffer = calloc( 1, size )))
    {
        hr = E_OUTOFMEMORY;
        goto _CLEANUP;
    }

    if (ERROR_SUCCESS != (status = RegGetValueA(
        HKEY_LOCAL_MACHINE, "Software\\Wine\\WineGDK", "RefreshToken", RRF_RT_REG_SZ, NULL, buffer, &size
    )))
    {
        hr = HRESULT_FROM_WIN32( status );
        goto _CLEANUP;
    }

    if (FAILED(hr = MultiByteToHSTRING( buffer, size, &impl->refresh_token ))) goto _CLEANUP;
    if (FAILED(hr = IUser_RefreshOAuthToken( iface ))) goto _CLEANUP;
    if (FAILED(hr = IUser_RefreshUserToken( iface ))) goto _CLEANUP;
    hr = IUser_RefreshXstsToken( iface );

_CLEANUP:

    if (buffer) free( buffer );
    if (SUCCEEDED(hr)) *user = (XUserHandle)impl;
    else IUser_Release( iface );
    return hr;
}

struct x_user
{
    IXUserImpl6 IXUserImpl_iface;
    IXUserGamertagImpl IXUserGamertagImpl_iface;
    LONG ref;
};

static inline struct x_user *impl_from_IXUserImpl( IXUserImpl6 *iface )
{
    return CONTAINING_RECORD( iface, struct x_user, IXUserImpl_iface );
}

static HRESULT WINAPI x_user_QueryInterface( IXUserImpl6 *iface, REFIID iid, void **out )
{
    struct x_user *impl = impl_from_IXUserImpl( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown    ) ||
        IsEqualGUID( iid, &IID_IXUserImpl  ) ||
        IsEqualGUID( iid, &IID_IXUserImpl2 ) ||
        IsEqualGUID( iid, &IID_IXUserImpl3 ) ||
        IsEqualGUID( iid, &IID_IXUserImpl4 ) ||
        IsEqualGUID( iid, &IID_IXUserImpl5 ) ||
        IsEqualGUID( iid, &IID_IXUserImpl6 ))
    {
        IXUserImpl6_AddRef( *out = &impl->IXUserImpl_iface );
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_IXUserGamertagImpl ))
    {
        IXUserGamertagImpl_AddRef( *out = &impl->IXUserGamertagImpl_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_user_AddRef( IXUserImpl6 *iface )
{
    struct x_user *impl = impl_from_IXUserImpl( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_user_Release( IXUserImpl6 *iface )
{
    struct x_user *impl = impl_from_IXUserImpl( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_user_XUserDuplicateHandle( IXUserImpl6 *iface, XUserHandle handle, XUserHandle *duplicatedHandle )
{
    TRACE( "iface %p, handle %p, duplicatedHandle %p.\n", iface, handle, duplicatedHandle );
    if (!handle || !duplicatedHandle) return E_POINTER;
    IUser_AddRef( &handle->IUser_iface );
    *duplicatedHandle = handle;
    return S_OK;
}

static void WINAPI x_user_XUserCloseHandle( IXUserImpl6 *iface, XUserHandle user )
{
    TRACE( "iface %p, user %p.\n", iface, user );
    if (!user) return;
    IUser_Release( &user->IUser_iface );
}

static INT32 WINAPI x_user_XUserCompare( IXUserImpl6 *iface, XUserHandle user1, XUserHandle user2 )
{
    TRACE( "iface %p, user1 %p, user2 %p.\n", iface, user1, user2 );
    if (!user1 || !user2) return 1;
    return user1->xuid == user2->xuid ? 0 : 1;
}

static HRESULT WINAPI x_user_XUserGetMaxUsers( IXUserImpl6 *iface, UINT32 *maxUsers )
{
    TRACE( "iface %p, maxUsers %p.\n", iface, maxUsers );
    *maxUsers = 1;
    return S_OK;
}

struct XUserAddContext
{
    XUserAddOptions options;
    XUserHandle user;
};

static HRESULT WINAPI XUserAddProvider( XAsyncOp op, const XAsyncProviderData *data )
{
    struct XUserAddContext *context;
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "op %d, data %p.\n", op, data );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    context = (struct XUserAddContext *)data->context;

    switch (op)
    {
        case Begin:
            hr = IXThreadingImpl_XAsyncSchedule( xthreading, data->async, 0 );
            break;

        case GetResult:
            memcpy( data->buffer, &context->user, sizeof(XUserHandle) );
            break;

        case DoWork:
            if (context->options & XUserAddOptions_AddDefaultUserSilently)
                hr = LoadDefaultUser( &context->user );
            else hr = E_ABORT;

            IXThreadingImpl_XAsyncComplete( xthreading, data->async, hr, sizeof(XUserHandle) );
            hr = S_OK;
            break;

        case Cleanup:
            free( context );
            break;

        case Cancel:
            break;
    }

    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserAddAsync( IXUserImpl6 *iface, XUserAddOptions options, XAsyncBlock *async )
{
    struct XUserAddContext *context;
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, options %d, async %p.\n", iface, options, async );

    if (!async) return E_POINTER;
    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    if (!(context = calloc( 1, sizeof(*context) )))
    {
        IXThreadingImpl_Release( xthreading );
        return E_OUTOFMEMORY;
    }

    context->options = options;
    hr = IXThreadingImpl_XAsyncBegin( xthreading, async, context, NULL, "XUserAddAsync", XUserAddProvider );
    IXThreadingImpl_Release( xthreading );
    if (FAILED(hr)) free( context );
    return hr;
}

static HRESULT WINAPI x_user_XUserAddResult( IXUserImpl6 *iface, XAsyncBlock *async, XUserHandle *newUser )
{
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, async %p, newUser %p.\n", iface, async, newUser );

    if (!async || !newUser) return E_POINTER;
    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    hr = IXThreadingImpl_XAsyncGetResult( xthreading, async, x_user_XUserAddAsync, sizeof(XUserHandle), newUser, NULL );
    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetLocalId( IXUserImpl6 *iface, XUserHandle user, XUserLocalId *userLocalId )
{
    FIXME( "iface %p, user %p, userLocalId %p stub!\n", iface, user, userLocalId );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserFindUserByLocalId( IXUserImpl6 *iface, XUserLocalId userLocalId, XUserHandle *handle )
{
    FIXME( "iface %p, userLocalId %p, handle %p stub!\n", iface, &userLocalId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetId( IXUserImpl6 *iface, XUserHandle user, UINT64 *userId )
{
    TRACE( "iface %p, user %p, userId %p.\n", iface, user, userId );
    if (!user || !userId) return E_POINTER;
    *userId = user->xuid;
    return S_OK;
}

static HRESULT WINAPI x_user_XUserFindUserById( IXUserImpl6 *iface, UINT64 userId, XUserHandle *handle )
{
    FIXME( "iface %p, userId %llu, handle %p stub!\n", iface, userId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetIsGuest( IXUserImpl6 *iface, XUserHandle user, boolean *isGuest )
{
    FIXME( "iface %p, user %p, isGuest %p stub!\n", iface, user, isGuest );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetState( IXUserImpl6 *iface, XUserHandle user, XUserState *state )
{
    FIXME( "iface %p, user %p, state %p stub!\n", iface, user, state );
    return E_NOTIMPL;
}

static HRESULT WINAPI __PADDING__( IXUserImpl6 *iface )
{
    WARN( "iface %p padding function called! It's unknown what this function does.\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureAsync( IXUserImpl6 *iface, XUserHandle user, XUserGamerPictureSize pictureSize, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, pictureSize %d, async %p stub!\n", iface, user, pictureSize, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResult( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetAgeGroup( IXUserImpl6 *iface, XUserHandle user, XUserAgeGroup *ageGroup )
{
    FIXME( "iface %p, user %p, ageGroup %p stub!\n", iface, user, ageGroup );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserCheckPrivilege( IXUserImpl6 *iface, XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, boolean *hasPrivilege, XUserPrivilegeDenyReason *reason )
{
    FIXME( "iface %p, user %p, options %d, privilege %d, hasPrivilege %p, reason %p stub!\n", iface, user, options, privilege, hasPrivilege, reason );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolvePrivilegeWithUiAsync( IXUserImpl6 *iface, XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, privilege %d, async %p stub!\n", iface, user, options, privilege, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolvePrivilegeWithUiResult( IXUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureAsync( IXUserImpl6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const CHAR *method, const CHAR *url, SIZE_T headerCount, const XUserGetTokenAndSignatureHttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, method %s, url %s, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p stub!\n", iface, user, options, debugstr_a( method ), debugstr_a( url ), headerCount, headers, bodySize, bodyBuffer, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResult( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureData **ptrToBuffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Async( IXUserImpl6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const WCHAR *method, const WCHAR *url, SIZE_T headerCount, const XUserGetTokenAndSignatureUtf16HttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, method %s, url %s, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p stub!\n", iface, user, options, debugstr_w( method ), debugstr_w( url ), headerCount, headers, bodySize, bodyBuffer, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16ResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Result( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureUtf16Data **ptrToBuffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiAsync( IXUserImpl6 *iface, XUserHandle user, const CHAR *url, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, url %s, async %p stub!\n", iface, user, debugstr_a( url ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiResult( IXUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiUtf16Async( IXUserImpl6 *iface, XUserHandle user, const WCHAR *url, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, url %s, async %p stub!\n", iface, user, debugstr_w( url ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiUtf16Result( IXUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserRegisterForChangeEvent( IXUserImpl6 *iface, XTaskQueueHandle queue, void *context, XUserChangeEventCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_XUserUnregisterForChangeEvent( IXUserImpl6 *iface, XTaskQueueRegistrationToken token, boolean wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_user_XUserGetSignOutDeferral( IXUserImpl6 *iface, XUserSignOutDeferralHandle *deferral )
{
    TRACE( "iface %p, deferral %p.\n", iface, deferral );
    *deferral = NULL;
    return E_GAMEUSER_DEFERRAL_NOT_AVAILABLE;
}

static void WINAPI x_user_XUserCloseSignOutDeferralHandle( IXUserImpl6 *iface, XUserSignOutDeferralHandle deferral )
{
    TRACE( "iface %p, deferral %p.\n", iface, deferral );
}

static HRESULT WINAPI x_user_XUserAddByIdWithUiAsync( IXUserImpl6 *iface, UINT64 userId, XAsyncBlock *async )
{
    FIXME( "iface %p, userId %llu, async %p stub!\n", iface, userId, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserAddByIdWithUiResult( IXUserImpl6 *iface, XAsyncBlock *async, XUserHandle *newUser )
{
    FIXME( "iface %p, async %p, newUser %p stub!\n", iface, async, newUser );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyAsync( IXUserImpl6 *iface, XUserHandle user, XUserGetMsaTokenSilentlyOptions options, const CHAR *scope, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %u, scope %s, async %p stub!\n", iface, user, options, debugstr_a( scope ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResult( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T resultTokenSize, CHAR *resultToken, SIZE_T *resultTokenUsed )
{
    FIXME( "iface %p, async %p, resultTokenSize %Iu, resultToken %p, resultTokenUsed %p stub!\n", iface, async, resultTokenSize, resultToken, resultTokenUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *tokenSize )
{
    FIXME( "iface %p, async %p, tokenSize %p stub!\n", iface, async, tokenSize );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_XUserIsStoreUser( IXUserImpl6 *iface, XUserHandle user )
{
    FIXME( "iface %p, user %p stub!\n", iface, user );
    return TRUE;
}

static HRESULT WINAPI x_user_XUserPlatformRemoteConnectSetEventHandlers( IXUserImpl6 *iface, XTaskQueueHandle queue, XUserPlatformRemoteConnectEventHandlers *handlers )
{
    FIXME( "iface %p, queue %p, handlers %p stub!\n", iface, queue, handlers );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformRemoteConnectCancelPrompt( IXUserImpl6 *iface, XUserPlatformOperation operation )
{
    FIXME( "iface %p, operation %p stub!\n", iface, operation );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformSpopPromptSetEventHandlers( IXUserImpl6 *iface, XTaskQueueHandle queue, XUserPlatformSpopPromptEventHandler *handler, void *context )
{
    FIXME( "iface %p, queue %p, handler %p, context %p stub!\n", iface, queue, handler, context );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformSpopPromptComplete( IXUserImpl6 *iface, XUserPlatformOperation operation, XUserPlatformOperationResult result )
{
    FIXME( "iface %p, operation %p, result %d stub!\n", iface, operation, result );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_XUserIsSignOutPresent( IXUserImpl6 *iface )
{
    TRACE( "iface %p.\n", iface );
    return FALSE;
}

static HRESULT WINAPI x_user_XUserSignOutAsync( IXUserImpl6 *iface, XUserHandle user, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, async %p stub!\n", iface, user, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserSignOutResult( IXUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static const struct IXUserImpl6Vtbl x_user_vtbl =
{
    x_user_QueryInterface,
    x_user_AddRef,
    x_user_Release,
    /* IXUserImpl methods */
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
    /* IXUserImpl2 methods */
    x_user_XUserAddByIdWithUiAsync,
    x_user_XUserAddByIdWithUiResult,
    /* IXUserImpl3 methods */
    x_user_XUserGetMsaTokenSilentlyAsync,
    x_user_XUserGetMsaTokenSilentlyResult,
    x_user_XUserGetMsaTokenSilentlyResultSize,
    /* IXUserImpl4 methods */
    x_user_XUserIsStoreUser,
    /* IXUserImpl5 methods */
    x_user_XUserPlatformRemoteConnectSetEventHandlers,
    x_user_XUserPlatformRemoteConnectCancelPrompt,
    x_user_XUserPlatformSpopPromptSetEventHandlers,
    x_user_XUserPlatformSpopPromptComplete,
    /* IXUserImpl6 methods */
    x_user_XUserIsSignOutPresent,
    x_user_XUserSignOutAsync,
    x_user_XUserSignOutResult,
};

static inline struct x_user *impl_from_IXUserGamertagImpl( IXUserGamertagImpl *iface )
{
    return CONTAINING_RECORD( iface, struct x_user, IXUserGamertagImpl_iface );
}

static HRESULT WINAPI x_user_gamertag_QueryInterface( IXUserGamertagImpl *iface, REFIID riid, void **out )
{
    struct x_user *impl = impl_from_IXUserGamertagImpl( iface );
    return IXUserImpl6_QueryInterface( &impl->IXUserImpl_iface, riid, out );
}

static ULONG WINAPI x_user_gamertag_AddRef( IXUserGamertagImpl *iface )
{
    struct x_user *impl = impl_from_IXUserGamertagImpl( iface );
    return IXUserImpl6_AddRef( &impl->IXUserImpl_iface );
}

static ULONG WINAPI x_user_gamertag_Release( IXUserGamertagImpl *iface )
{
    struct x_user *impl = impl_from_IXUserGamertagImpl( iface );
    return IXUserImpl6_Release( &impl->IXUserImpl_iface );
}

static HRESULT WINAPI x_user_gamertag_XUserGetGamertag( IXUserGamertagImpl *iface, XUserHandle user, XUserGamertagComponent gamertagComponent, SIZE_T gamertagSize, CHAR *gamertag, SIZE_T *gamertagUsed )
{
    FIXME( "iface %p, user %p, gamertagComponent %d, gamertagSize %Iu, gamertag %p, gamertagUsed %p stub!\n", iface, user, gamertagComponent, gamertagSize, gamertag, gamertagUsed );
    return E_NOTIMPL;
}

static const struct IXUserGamertagImplVtbl x_user_gamertag_vtbl =
{
    x_user_gamertag_QueryInterface,
    x_user_gamertag_AddRef,
    x_user_gamertag_Release,
    /* IXUserGamertagImpl methods */
    x_user_gamertag_XUserGetGamertag,
};

struct x_user_device
{
    IXUserDeviceImpl IXUserDeviceImpl_iface;
    LONG ref;
};

static inline struct x_user_device *impl_from_IXUserDeviceImpl( IXUserDeviceImpl *iface )
{
    return CONTAINING_RECORD( iface, struct x_user_device, IXUserDeviceImpl_iface );
}

static HRESULT WINAPI x_user_device_QueryInterface( IXUserDeviceImpl *iface, REFIID iid, void **out )
{
    struct x_user_device *impl = impl_from_IXUserDeviceImpl( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown         ) ||
        IsEqualGUID( iid, &IID_IXUserDeviceImpl ))
    {
        IXUserDeviceImpl_AddRef( *out = &impl->IXUserDeviceImpl_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_user_device_AddRef( IXUserDeviceImpl *iface )
{
    struct x_user_device *impl = impl_from_IXUserDeviceImpl( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_user_device_Release( IXUserDeviceImpl *iface )
{
    struct x_user_device *impl = impl_from_IXUserDeviceImpl( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_user_device_XUserFindForDevice( IXUserDeviceImpl *iface, const APP_LOCAL_DEVICE_ID *deviceId, XUserHandle *handle )
{
    FIXME( "iface %p, deviceId %p, handle %p stub!\n", iface, deviceId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_device_XUserRegisterForDeviceAssociationChanged( IXUserDeviceImpl *iface, XTaskQueueHandle queue, void *context, XUserDeviceAssociationChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_device_XUserUnregisterForDeviceAssociationChanged( IXUserDeviceImpl *iface, XTaskQueueRegistrationToken token, boolean wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_user_device_XUserGetDefaultAudioEndpointUtf16( IXUserDeviceImpl *iface, XUserLocalId user, XUserDefaultAudioEndpointKind defaultAudioEndpointKind, SIZE_T endpointIdUtf16Count, WCHAR *endpointIdUtf16, SIZE_T *endpointIdUtf16Used )
{
    FIXME( "iface %p, user %p, defaultAudioEndpointKind %d, endpointIdUtf16Count %Iu, endpointIdUtf16 %p, endpointIdUtf16used %p stub!\n", iface, &user, defaultAudioEndpointKind, endpointIdUtf16Count, endpointIdUtf16, endpointIdUtf16Used );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_device_XUserRegisterForDefaultAudioEndpointUtf16Changed( IXUserDeviceImpl *iface, XTaskQueueHandle queue, void *context, XUserDefaultAudioEndpointUtf16ChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static boolean WINAPI x_user_device_XUserUnregisterForDefaultAudioEndpointUtf16Changed( IXUserDeviceImpl *iface, XTaskQueueRegistrationToken token, boolean wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_user_device_XUserFindControllerForUserWithUiAsync( IXUserDeviceImpl *iface, XUserHandle user, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, async %p stub!\n", iface, user, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_device_XUserFindControllerForUserWithUiResult( IXUserDeviceImpl *iface, XAsyncBlock *async, APP_LOCAL_DEVICE_ID *deviceId )
{
    FIXME( "iface %p, async %p, deviceId %p stub!\n", iface, async, deviceId );
    return E_NOTIMPL;
}

static const struct IXUserDeviceImplVtbl x_user_device_vtbl =
{
    x_user_device_QueryInterface,
    x_user_device_AddRef,
    x_user_device_Release,
    /* IXUserDeviceImpl methods */
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

IXUserImpl6 *x_user_impl = &x_user.IXUserImpl_iface;
IXUserDeviceImpl *x_user_device_impl = &x_user_device.IXUserDeviceImpl_iface;
