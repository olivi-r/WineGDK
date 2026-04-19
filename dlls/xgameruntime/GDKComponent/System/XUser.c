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
#include <ntdef.h>
#include <time.h>
#include <wincrypt.h>
#include <wininet.h>

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

const char msaAppId[] = "0000000040159362";

static const WCHAR *ACCEPT_JSON[] = { L"application/json", NULL };
static const WCHAR CT_JSON[] = L"Content-Type: application/json";
static const WCHAR CT_FORM_URLENCODED[] = L"Content-Type: application/x-www-form-urlencoded";

static HRESULT encode_base64( const UINT32 dataSize, const BYTE *data, const UINT32 base64Size, char *base64 )
{
    static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const UINT32 size = (dataSize * 8 + 5) / 6, rem = (size % 4) ? 4 - (size % 4) : 0;
    UINT32 div = dataSize / 3; /* 3 bytes of in, 4 chars out */
    const BYTE *cur = data;
    char *ptr = base64;

    TRACE( "dataSize %u, data %p, base64Size %u, base64 %p.\n", dataSize, data, base64Size, base64 );

    if (size > base64Size) return HRESULT_FROM_WIN32( ERROR_INSUFFICIENT_BUFFER );
    while (div > 0)
    {
        /* first 6 bits of byte 0 */
        *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
        /* last 2 bits of byte 0, first 4 bits of byte 1 */
        *ptr++ = b64[ ((cur[0] << 4) & 0x30) | ((cur[1] >> 4) & 0x0f) ];
        /* last 4 bits of byte 1, first 2 bits of byte 2 */
        *ptr++ = b64[ ((cur[1] << 2) & 0x3c) | ((cur[2] >> 6) & 0x03) ];
        /* last 6 bits of byte 2 */
        *ptr++ = b64[ cur[2] & 0x3f ];
        cur += 3;
        div--;
    }

    switch (rem)
    {
        case 1:
            /* first 6 bits of byte 0 */
            *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
            /* last 2 bits of byte 0, first 4 bits of byte 1 */
            *ptr++ = b64[ ((cur[0] << 4) & 0x30) | ((cur[1] >> 4) & 0x0f) ];
            /* last 4 bits of byte 1, rest 0 */
            *ptr++ = b64[ ((cur[1] << 2) & 0x3c) ];
            /* padding */
            *ptr++ = '=';
            break;
        case 2:
            /* first 6 bits of byte 0 */
            *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
            /* last 2 bits of byte 0, rest 0 */
            *ptr++ = b64[ ((cur[0] << 4) & 0x30) ];
            /* padding */
            *ptr++ = '=';
            *ptr++ = '=';
            break;
    }
    return S_OK;
}

static HRESULT encode_base64_utf16( const UINT32 dataSize, const BYTE *data, const UINT32 base64Size, WCHAR *base64 )
{
    static const WCHAR b64[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const UINT32 size = (dataSize * 8 + 5) / 6, rem = (size % 4) ? 4 - (size % 4) : 0;
    UINT32 div = dataSize / 3; /* 3 bytes of in, 4 chars out */
    const BYTE *cur = data;
    WCHAR *ptr = base64;

    TRACE( "dataSize %u, data %p, base64Size %u, base64 %p.\n", dataSize, data, base64Size, base64 );

    if (size > base64Size) return HRESULT_FROM_WIN32( ERROR_INSUFFICIENT_BUFFER );
    while (div > 0)
    {
        /* first 6 bits of byte 0 */
        *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
        /* last 2 bits of byte 0, first 4 bits of byte 1 */
        *ptr++ = b64[ ((cur[0] << 4) & 0x30) | ((cur[1] >> 4) & 0x0f) ];
        /* last 4 bits of byte 1, first 2 bits of byte 2 */
        *ptr++ = b64[ ((cur[1] << 2) & 0x3c) | ((cur[2] >> 6) & 0x03) ];
        /* last 6 bits of byte 2 */
        *ptr++ = b64[ cur[2] & 0x3f ];
        cur += 3;
        div--;
    }

    switch (rem)
    {
        case 1:
            /* first 6 bits of byte 0 */
            *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
            /* last 2 bits of byte 0, first 4 bits of byte 1 */
            *ptr++ = b64[ ((cur[0] << 4) & 0x30) | ((cur[1] >> 4) & 0x0f) ];
            /* last 4 bits of byte 1, rest 0 */
            *ptr++ = b64[ ((cur[1] << 2) & 0x3c) ];
            /* padding */
            *ptr++ = '=';
            break;
        case 2:
            /* first 6 bits of byte 0 */
            *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
            /* last 2 bits of byte 0, rest 0 */
            *ptr++ = b64[ ((cur[0] << 4) & 0x30) ];
            /* padding */
            *ptr++ = '=';
            *ptr++ = '=';
            break;
    }
    return S_OK;
}

static HRESULT encode_base64url( const UINT32 dataSize, const BYTE *data, const UINT32 base64Size, char *base64 )
{
    static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    const UINT32 size = (dataSize * 8 + 5) / 6, rem = (size % 4) ? 4 - (size % 4) : 0;
    UINT32 div = dataSize / 3; /* 3 bytes of in, 4 chars out */
    const BYTE *cur = data;
    char *ptr = base64;

    TRACE( "dataSize %u, data %p, base64Size %u, base64 %p.\n", dataSize, data, base64Size, base64 );

    if (size > base64Size) return HRESULT_FROM_WIN32( ERROR_INSUFFICIENT_BUFFER );
    while (div > 0)
    {
        /* first 6 bits of byte 0 */
        *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
        /* last 2 bits of byte 0, first 4 bits of byte 1 */
        *ptr++ = b64[ ((cur[0] << 4) & 0x30) | ((cur[1] >> 4) & 0x0f) ];
        /* last 4 bits of byte 1, first 2 bits of byte 2 */
        *ptr++ = b64[ ((cur[1] << 2) & 0x3c) | ((cur[2] >> 6) & 0x03) ];
        /* last 6 bits of byte 2 */
        *ptr++ = b64[ cur[2] & 0x3f ];
        cur += 3;
        div--;
    }

    switch (rem)
    {
        case 1:
            /* first 6 bits of byte 0 */
            *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
            /* last 2 bits of byte 0, first 4 bits of byte 1 */
            *ptr++ = b64[ ((cur[0] << 4) & 0x30) | ((cur[1] >> 4) & 0x0f) ];
            /* last 4 bits of byte 1, rest 0 */
            *ptr++ = b64[ ((cur[1] << 2) & 0x3c) ];
            /* no padding */
            break;
        case 2:
            /* first 6 bits of byte 0 */
            *ptr++ = b64[ (cur[0] >> 2) & 0x3f ];
            /* last 2 bits of byte 0, rest 0 */
            *ptr++ = b64[ ((cur[0] << 4) & 0x30) ];
            /* no padding */
            break;
    }
    return S_OK;
}

static HRESULT MultiByteToHSTRING( const char *str, UINT32 str_size, HSTRING *hstr )
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

static HRESULT HSTRINGToMultiByte( HSTRING hstr, char **str, UINT32 *str_size )
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
GetJsonValue_( Value, IJsonValue** )
GetJsonValue_( String, HSTRING* )
GetJsonValue_( Number, DOUBLE* )

static HRESULT ParseJsonObject( const char *str, SIZE_T str_size, IJsonObject **object )
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
    char *classic_gamertag;
    UINT32 classic_gamertag_size;

    BCRYPT_KEY_HANDLE key;
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
        if (impl->classic_gamertag) free( impl->classic_gamertag );
        if (impl->key) BCryptDestroyKey( impl->key );
        free( impl );
    }
    return ref;
}

static HRESULT WINAPI user_RequestOAuthCode( IUser *iface, HSTRING *user, HSTRING *uri )
{
    static const char template[] = "scope=service::user.auth.xboxlive.com::MBI_SSL&response_type=device_code&client_id=";
    struct XUser *impl = impl_from_IUser( iface );
    char *buffer = NULL, *data = NULL;
    IJsonObject *object = NULL;
    SIZE_T size = 0;
    HRESULT hr;

    TRACE( "iface %p, user %p, uri %p.\n", iface, user, uri );

    if (!(data = calloc( 1, ARRAY_SIZE( template ) + ARRAY_SIZE( msaAppId ) - 1 )))
    {
        return E_OUTOFMEMORY;
    }
    strcpy( data, template );
    strcat( data, msaAppId );

    if (FAILED(hr = HttpRequest( L"POST", L"login.live.com", L"/oauth20_connect.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, (UCHAR **)&buffer, &size )))
        goto cleanup;
    if (FAILED(hr = ParseJsonObject( buffer, size, &object ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"device_code", &impl->device_code ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"verification_uri", uri ))) goto cleanup;
    if (FAILED(hr = GetJsonNumberValue( object, L"interval", &impl->interval ))) goto cleanup;
    hr = GetJsonStringValue( object, L"user_code", user );

cleanup:
    if (data) free( data );
    if (buffer) free( buffer );
    IJsonObject_Release( object );
    if (SUCCEEDED(hr)) return hr;
    if (*uri) WindowsDeleteString( *uri );
    if (*user) WindowsDeleteString( *user );
    if (impl->device_code) WindowsDeleteString( impl->device_code );
    return hr;
}

static HRESULT WINAPI user_RequestOAuthToken( IUser *iface )
{
    static const char template[] = "grant_type=device_code&device_code=";
    HSTRING access = NULL, refresh = NULL;
    struct XUser *impl = impl_from_IUser( iface );
    char *data, *deviceCode = NULL;
    IJsonObject *object = NULL;
    UINT32 deviceCodeSize = 0;
    char *buffer = NULL;
    DOUBLE delta = 0;
    SIZE_T size = 0;
    time_t expiry;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    if (FAILED(hr = HSTRINGToMultiByte( impl->device_code, &deviceCode, &deviceCodeSize ))) return hr;

    if (!(data = calloc( ARRAY_SIZE( template ) + deviceCodeSize + strlen( "&client_id=" ) + ARRAY_SIZE( msaAppId ) - 1, sizeof(char) )))
    {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    strcpy( data, template );
    strncat( data, deviceCode, deviceCodeSize );
    strcat( data, "&client_id=" );
    strcat( data, msaAppId );

    while (TRUE)
    {
        if (SUCCEEDED(hr = HttpRequest( L"POST", L"login.live.com", L"/oauth20_token.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, (UCHAR **)&buffer, &size ))) break;
        Sleep( impl->interval * 1000 );
    }

    if (FAILED(hr = ParseJsonObject( buffer, size, &object ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"refresh_token", &refresh ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"access_token", &access ))) goto cleanup;
    if (FAILED(hr = GetJsonNumberValue( object, L"expires_in", &delta ))) goto cleanup;

    if ((expiry = time(NULL)) == -1) hr = E_FAIL;
    else impl->oauth_expiry = expiry + delta;

cleanup:
    if (data) free( data );
    if (buffer) free( buffer );
    if (deviceCode) free( deviceCode );
    if (object) IJsonObject_Release( object );
    if (SUCCEEDED(hr))
    {
        if (impl->refresh_token) WindowsDeleteString( impl->refresh_token );
        if (impl->access_token) WindowsDeleteString( impl->access_token );
        impl->refresh_token = refresh;
        impl->access_token = access;
        return hr;
    }
    if (refresh) WindowsDeleteString( refresh );
    if (access) WindowsDeleteString( access );
    return hr;
}

static HRESULT WINAPI user_RefreshOAuthToken( IUser *iface )
{
    static const char template[] = "grant_type=refresh_token&scope=service::user.auth.xboxlive.com::MBI_SSL&client_id=";
    HSTRING new_access = NULL, new_refresh = NULL;
    XUserHandle impl = impl_from_IUser( iface );
    char *data = NULL, *refresh_str = NULL;
    IJsonObject *object = NULL;
    UINT32 refresh_size = 0;
    char *buffer = NULL;
    DOUBLE delta = 0;
    SIZE_T size = 0;
    time_t expiry;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    if (FAILED(hr = HSTRINGToMultiByte( impl->refresh_token, &refresh_str, &refresh_size ))) return hr;
    if (!(data = calloc( ARRAY_SIZE( template ) + ARRAY_SIZE( msaAppId ) + strlen( "&refresh_token=" ) + refresh_size - 1, sizeof(char) )))
    {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    strcpy( data, template );
    strcat( data, msaAppId );
    strcat( data, "&refresh_token=" );
    strncat( data, refresh_str, refresh_size );
    if (FAILED(hr = HttpRequest( L"POST", L"login.live.com", L"/oauth20_token.srf", data, CT_FORM_URLENCODED, ACCEPT_JSON, (UCHAR **)&buffer, &size ))) goto cleanup;
    if (FAILED(hr = ParseJsonObject( buffer, size, &object ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"refresh_token", &new_refresh ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"access_token", &new_access ))) goto cleanup;
    if (FAILED(hr = GetJsonNumberValue( object, L"expires_in", &delta ))) goto cleanup;
    if ((expiry = time(NULL)) == -1) hr = E_FAIL;
    else impl->oauth_expiry = expiry + delta;

cleanup:
    if (data) free( data );
    if (buffer) free( buffer );
    IJsonObject_Release( object );
    if (refresh_str) free( refresh_str );
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
    const char *template = "{\"TokenType\":\"JWT\",\"RelyingParty\":\"http://auth.xboxlive.com\",\"Properties\":{\"AuthMethod\":\"RPS\",\"SiteName\":\"user.auth.xboxlive.com\",\"RpsTicket\":\"";
    struct XUser *impl = impl_from_IUser( iface );
    UINT32 tokenLen, wTokenLen;
    IJsonObject *object = NULL;
    const WCHAR *wToken;
    UCHAR *buf = NULL;
    char *body = NULL;
    SIZE_T bufSize;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    wToken = WindowsGetStringRawBuffer( impl->access_token, &wTokenLen );
    if (!(tokenLen = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wToken, wTokenLen, NULL, 0, NULL, NULL ))) goto error;
    if (!(body = calloc( strlen( template ) + tokenLen + strlen( "\"}}" ), sizeof(char) )))
    {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    /* construct request body */
    strcpy( body, template );
    if (!WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wToken, wTokenLen, body + strlen( template ), tokenLen, NULL, NULL )) goto error;
    strcat( body, "\"}}" );

    if (FAILED(hr = HttpRequest( L"POST", L"user.auth.xboxlive.com", L"/user/authenticate", body, CT_JSON, ACCEPT_JSON, &buf, &bufSize ))) goto cleanup;
    if (FAILED(hr = ParseJsonObject( (char *)buf, bufSize, &object ))) goto cleanup;
    hr = GetJsonStringValue( object, L"Token", &impl->user_token );
    goto cleanup;

error:
    hr = HRESULT_FROM_WIN32( GetLastError() );
cleanup:
    if (buf) free( buf );
    if (body) free( body );
    if (object) IJsonObject_Release( object );
    return hr;
}

static HRESULT WINAPI user_RefreshXstsToken( IUser *iface )
{
    const char *template = "{\"TokenType\":\"JWT\",\"RelyingParty\":\"http://xboxlive.com\",\"Properties\":{\"SandboxId\":\"RETAIL\",\"ProofKey\":{\"alg\":\"ES256\",\"kty\":\"EC\",\"use\":\"sig\",\"crv\":\"P-256\",\"x\":\"";
    IJsonObject *child = NULL, *claims = NULL, *object = NULL;
    UCHAR blob[sizeof(BCRYPT_ECCKEY_BLOB) + 64], *buf = NULL;
    struct XUser *impl = impl_from_IUser( iface );
    char *body = NULL, *token, *x, *y;
    UINT32 tokenLen, wTokenLen;
    IJsonArray *array = NULL;
    HSTRING xuid = NULL;
    const WCHAR *wToken;
    NTSTATUS status;
    SIZE_T bufSize;
    ULONG dummy;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    wToken = WindowsGetStringRawBuffer( impl->user_token, &wTokenLen );
    if (!(tokenLen = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wToken, wTokenLen, NULL, 0, NULL, NULL ))) goto error_win32;
    if (!(body = calloc( strlen( template ) + strlen( "\",\"y\":\"\"},\"UserTokens\":[\"\"]}}" ) + tokenLen + 87, sizeof(char) )))
    {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    /* 32 bytes -> 43 base64url chars without padding */
    x = body + strlen( template );
    y = x + 43 + strlen( "\",\"y\":\"" );
    token = y + 43 + strlen( "\"},\"UserTokens\":[\"" );

    /* construct request body */
    strcpy( body, template );
    if (!NT_SUCCESS(status = BCryptExportKey( impl->key, NULL, BCRYPT_ECCPUBLIC_BLOB, blob, sizeof(blob), &dummy, 0 ))) goto error_nt;
    if (FAILED(hr = encode_base64url( 32, blob + sizeof(BCRYPT_ECCKEY_BLOB), 44, x ))) goto cleanup;
    strcat( body, "\",\"y\":\"" );
    if (FAILED(hr = encode_base64url( 32, blob + sizeof(BCRYPT_ECCKEY_BLOB) + 32, 44, y ))) goto cleanup;
    strcat( body, "\"},\"UserTokens\":[\"" );
    if (!WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wToken, wTokenLen, token, tokenLen, NULL, NULL )) goto error_win32;
    strcat( body, "\"]}}" );

    if (FAILED(hr = HttpRequest( L"POST", L"xsts.auth.xboxlive.com", L"/xsts/authorize", body, CT_JSON, ACCEPT_JSON, &buf, &bufSize ))) goto cleanup;
    if (FAILED(hr = ParseJsonObject( (char *)buf, bufSize, &object ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"Token", &impl->xsts_token ))) goto cleanup;
    if (FAILED(hr = GetJsonObjectValue( object, L"DisplayClaims", &claims ))) goto cleanup;
    if (FAILED(hr = GetJsonArrayValue( claims, L"xui", &array ))) goto cleanup;
    if (FAILED(hr = IJsonArray_GetObjectAt( array, 0, &child ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( child, L"uhs", &impl->user_hash ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( child, L"xid", &xuid ))) goto cleanup;
    impl->xuid = wcstoull( WindowsGetStringRawBuffer( xuid, NULL ), NULL, 10 );
    if (errno == ERANGE) hr = E_UNEXPECTED;
    goto cleanup;

error_nt:
    hr = HRESULT_FROM_NT( status );
    goto cleanup;
error_win32:
    hr = HRESULT_FROM_WIN32( GetLastError() );
cleanup:
    if (buf) free( buf );
    if (body) free( body );
    if (xuid) WindowsDeleteString( xuid );
    if (array) IJsonArray_Release( array );
    if (child) IJsonObject_Release( child );
    if (claims) IJsonObject_Release( claims );
    if (object) IJsonObject_Release( object );
    return hr;
}

static HRESULT WINAPI user_FetchProfileSettings( IUser *iface, const WCHAR *settings, IUnknown **result )
{
    const WCHAR *template = L"/users/me/profile/settings?settings=";
    UINT32 headers_len, token_len, settings_count, uhs_len, url_len = wcslen( template ) + wcslen( settings ) + 1;
    const WCHAR *class_name = RuntimeClass_Windows_Data_Json_JsonObject;
    XUserHandle impl = impl_from_IUser( iface );
    WCHAR *data = NULL, *pathAndQuery, *headers;
    IJsonObject *object = NULL;
    IVector_IJsonValue *vector;
    const WCHAR *token, *uhs;
    HSTRING_HEADER class_hdr;
    HSTRING class, id = NULL;
    IJsonArray *array;
    IJsonValue *value;
    UCHAR *buffer;
    SIZE_T size;
    HRESULT hr;

    TRACE( "iface %p.\n", iface );

    *result = NULL;

    uhs = WindowsGetStringRawBuffer( impl->user_hash, &uhs_len );
    token = WindowsGetStringRawBuffer( impl->xsts_token, &token_len );

    headers_len = wcslen( L"x-xbl-contract-version: 2\r\nAuthorization: XBL3.0 x=;" ) + uhs_len + token_len + 1;
    url_len = wcslen( template ) + wcslen( settings ) + 1;
    if (!(data = calloc( headers_len + url_len, sizeof(WCHAR) ))) return E_OUTOFMEMORY;

    headers = data;
    wcscpy( headers, L"x-xbl-contract-version: 2\r\nAuthorization: XBL3.0 x=" );
    wcsncat( headers, uhs, uhs_len );
    wcscat( headers, L";" );
    wcsncat( headers, token, token_len );

    pathAndQuery = data + headers_len;
    wcscpy( pathAndQuery, template );
    wcscat( pathAndQuery, settings );

    hr = HttpRequest( L"GET", L"profile.xboxlive.com", pathAndQuery, (char *)"", headers, ACCEPT_JSON, &buffer, &size );
    free( data );
    if (FAILED(hr)) return hr;

    hr = ParseJsonObject( (char *)buffer, size, &object );
    free( buffer );
    if (FAILED(hr)) return hr;

    hr = GetJsonArrayValue( object, L"profileUsers", &array );
    IJsonObject_Release( object );
    if (FAILED(hr)) return hr;

    hr = IJsonArray_GetObjectAt( array, 0, &object );
    IJsonArray_Release( array );
    if (FAILED(hr)) return hr;

    hr = GetJsonArrayValue( object, L"settings", &array );
    IJsonObject_Release( object );
    if (FAILED(hr)) return hr;

    /* repack settings for easier access */

    if (FAILED(hr = IJsonArray_QueryInterface( array, &IID_IVector_IJsonValue, (void **)&vector ))) goto cleanup;
    hr = IVector_IJsonValue_get_Size( vector, &settings_count );
    IVector_IJsonValue_Release( vector );
    if (FAILED(hr)) goto cleanup;

    if (FAILED(hr = WindowsCreateStringReference( class_name, wcslen( class_name ), &class_hdr, &class ))) goto cleanup;
    if (FAILED(hr = RoActivateInstance( class, (IInspectable **)result ))) goto cleanup;

    for (UINT32 i = 0; i < settings_count; i++)
    {
        if (FAILED(hr = IJsonArray_GetObjectAt( array, i, &object ))) goto cleanup;
        if (FAILED(hr = GetJsonStringValue( object, L"id", &id ))) goto cleanup;
        if (FAILED(hr = GetJsonValueValue( object, L"value", &value ))) goto cleanup;
        IJsonObject_Release( object );
        object = NULL;
        hr = IJsonObject_SetNamedValue( (IJsonObject *)*result, id, value );
        IJsonValue_Release( value );
        if (FAILED(hr)) goto cleanup;
        WindowsDeleteString( id );
        id = NULL;
    }

cleanup:
    IJsonArray_Release( array );
    if (id) WindowsDeleteString( id );
    if (object) IJsonObject_Release( object );
    if (FAILED(hr) && *result)
    {
        IUnknown_Release( *result );
        *result = NULL;
    }
    return hr;
}

static HRESULT WINAPI user_GenerateKeyPair( IUser *iface )
{
    struct XUser *impl = impl_from_IUser( iface );
    BCRYPT_ALG_HANDLE ecdsa = NULL;
    NTSTATUS status;

    TRACE( "iface %p.\n", iface );

    if (impl->key)
    {
        BCryptDestroyKey( impl->key );
        impl->key = NULL;
    }

    if (!NT_SUCCESS(status = BCryptOpenAlgorithmProvider( &ecdsa, BCRYPT_ECDSA_P256_ALGORITHM, NULL, 0 ))) goto error;
    if (!NT_SUCCESS(status = BCryptGenerateKeyPair( ecdsa, &impl->key, 256, 0 ))) goto error;
    if (!NT_SUCCESS(status = BCryptFinalizeKeyPair( impl->key, 0 ))) goto error;
    goto cleanup;

error:
    if (impl->key)
    {
        BCryptDestroyKey( impl->key );
        impl->key = NULL;
    }
cleanup:
    if (ecdsa) BCryptCloseAlgorithmProvider( ecdsa, 0 );
    return HRESULT_FROM_NT( status );
}

static HRESULT WINAPI user_SignData( IUser *iface, ULONG dataSize, UCHAR *data, ULONG signatureSize, UCHAR *signature )
{
    struct XUser *impl = impl_from_IUser( iface );
    BCRYPT_ALG_HANDLE algorithm = NULL;
    BCRYPT_HASH_HANDLE object = NULL;
    HRESULT hr = S_OK;
    NTSTATUS status;
    UCHAR hash[32];
    ULONG dummy;

    TRACE( "iface %p, dataSize %lu, data %p, signatureSize %lu, signature %p.\n", iface, dataSize, data, signatureSize, signature );

    /* ES256 signs sha-256 hash of data */
    if (signatureSize < 64) return HRESULT_FROM_WIN32( ERROR_INSUFFICIENT_BUFFER );
    if (!NT_SUCCESS(status = BCryptOpenAlgorithmProvider( &algorithm, BCRYPT_SHA256_ALGORITHM, NULL, 0 ))) goto error;
    if (!NT_SUCCESS(status = BCryptCreateHash( algorithm, &object, NULL, 0, NULL, 0, 0 ))) goto error;
    if (!NT_SUCCESS(status = BCryptHashData( object, data, dataSize, 0 ))) goto error;
    if (!NT_SUCCESS(status = BCryptFinishHash( object, hash, 32, 0 ))) goto error;
    if (!NT_SUCCESS(status = BCryptSignHash( impl->key, NULL, hash, 32, signature, signatureSize, &dummy, 0 ))) goto error;
    goto cleanup;

error:
    hr = HRESULT_FROM_NT( status );
cleanup:
    if (object) BCryptDestroyHash( object );
    if (algorithm) BCryptCloseAlgorithmProvider( algorithm, 0 );
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
    user_RefreshOAuthToken,
    user_RefreshUserToken,
    user_RefreshXstsToken,
    user_FetchProfileSettings,
    user_GenerateKeyPair,
    user_SignData,
};

static HRESULT LoadDefaultUser( XUserHandle *user )
{
    IJsonObject *object = NULL;
    HSTRING classic_gamertag;
    char *buffer = NULL;
    struct XUser *impl;
    LSTATUS status;
    IUser *iface;
    HRESULT hr;
    DWORD size;

    TRACE( "user %p.\n", user );

    if (!(impl = calloc( 1, sizeof(*impl) ))) return E_OUTOFMEMORY;

    impl->IUser_iface.lpVtbl = &user_vtbl;
    impl->ref = 1;

    iface = &impl->IUser_iface;

    status = RegGetValueA( HKEY_LOCAL_MACHINE, "Software\\Wine\\WineGDK", "RefreshToken", RRF_RT_REG_SZ, NULL, NULL, &size );
    if (status != ERROR_SUCCESS) goto error;
    if (!(buffer = calloc( 1, size )))
    {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    status = RegGetValueA( HKEY_LOCAL_MACHINE, "Software\\Wine\\WineGDK", "RefreshToken", RRF_RT_REG_SZ, NULL, buffer, &size );
    if (status != ERROR_SUCCESS) goto error;
    if (FAILED(hr = MultiByteToHSTRING( buffer, size, &impl->refresh_token ))) goto cleanup;
    if (FAILED(hr = IUser_RefreshOAuthToken( iface ))) goto cleanup;
    if (FAILED(hr = IUser_RefreshUserToken( iface ))) goto cleanup;
    if (FAILED(hr = IUser_GenerateKeyPair( iface ))) goto cleanup;
    if (FAILED(hr = IUser_RefreshXstsToken( iface ))) goto cleanup;
    if (FAILED(hr = IUser_FetchProfileSettings( iface, L"Gamertag", (IUnknown **)&object ))) goto cleanup;
    if (FAILED(hr = GetJsonStringValue( object, L"Gamertag", &classic_gamertag ))) goto cleanup;
    hr = HSTRINGToMultiByte( classic_gamertag, &impl->classic_gamertag, &impl->classic_gamertag_size );
    goto cleanup;

error:
    hr = HRESULT_FROM_WIN32( status );
cleanup:
    if (buffer) free( buffer );
    if (object) IJsonObject_Release( object );
    if (classic_gamertag) WindowsDeleteString( classic_gamertag );
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
    FIXME( "iface %p, user1 %p, user2 %p stub!\n", iface, user1, user2 );
    return E_NOTIMPL;
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
        case XAsyncOp_Begin:
            hr = IXThreadingImpl_XAsyncSchedule( xthreading, data->async, 0 );
            break;

        case XAsyncOp_GetResult:
            memcpy( data->buffer, &context->user, sizeof(XUserHandle) );
            break;

        case XAsyncOp_DoWork:
            if (context->options & XUserAddOptions_AddDefaultUserSilently)
                hr = LoadDefaultUser( &context->user );
            else hr = E_ABORT;

            IXThreadingImpl_XAsyncComplete( xthreading, data->async, hr, sizeof(XUserHandle) );
            hr = S_OK;
            break;

        case XAsyncOp_Cleanup:
            free( context );
            break;

        case XAsyncOp_Cancel:
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
    hr = IXThreadingImpl_XAsyncGetResult( xthreading, async, NULL, sizeof(*newUser), newUser, NULL );
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
    *userId = user->xuid;
    return S_OK;
}

static HRESULT WINAPI x_user_XUserFindUserById( IXUserImpl6 *iface, UINT64 userId, XUserHandle *handle )
{
    FIXME( "iface %p, userId %llu, handle %p stub!\n", iface, userId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetIsGuest( IXUserImpl6 *iface, XUserHandle user, BOOLEAN *isGuest )
{
    FIXME( "iface %p, user %p, isGuest %p stub!\n", iface, user, isGuest );
    *isGuest = TRUE;
    return S_OK;
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

struct XUserGetGamerPictureContext
{
    XUserHandle user;
    XUserGamerPictureSize pictureSize;
    SIZE_T bufferSize;
    void *buffer;
};

static HRESULT WINAPI XUserGetGamerPictureProvider( XAsyncOp op, const XAsyncProviderData *data )
{
    URL_COMPONENTSW uc = { .dwStructSize = sizeof(URL_COMPONENTSW), .dwHostNameLength = -1, .dwUrlPathLength = -1, .dwExtraInfoLength = -1 };
    static const WCHAR *accept[] = { L"image/png", NULL };
    struct XUserGetGamerPictureContext *context;
    WCHAR *hostName = NULL, *pathAndQuery;
    const WCHAR *buffer, *suffix;
    IXThreadingImpl *xthreading;
    IJsonObject *object = NULL;
    HSTRING url = NULL;
    HRESULT hr;

    TRACE( "op %d, data %p.\n", op, data );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    context = (struct XUserGetGamerPictureContext *)data->context;

    switch (op)
    {
        case XAsyncOp_Begin:
            hr = IXThreadingImpl_XAsyncSchedule( xthreading, data->async, 0 );
            break;

        case XAsyncOp_GetResult:
            memcpy( data->buffer, context->buffer, context->bufferSize );
            break;

        case XAsyncOp_DoWork:
            switch (context->pictureSize)
            {
                case XUserGamerPictureSize_Small:
                    suffix = L"&format=png&w=64&h=64";
                    break;
                case XUserGamerPictureSize_Medium:
                    suffix = L"&format=png&w=208&h=208";
                    break;
                case XUserGamerPictureSize_Large:
                    suffix = L"&format=png&w=424&h=424";
                    break;
                case XUserGamerPictureSize_ExtraLarge:
                    suffix = L"&format=png&w=1080&h=1080";
                    break;
                default:
                    hr = E_INVALIDARG;
                    goto cleanup;
            }

            if (FAILED(hr = IUser_FetchProfileSettings( &context->user->IUser_iface, L"PublicGamerpic", (IUnknown **)&object ))) goto cleanup;
            if (FAILED(hr = GetJsonStringValue( object, L"PublicGamerpic", &url ))) goto cleanup;
            buffer = WindowsGetStringRawBuffer( url, NULL );
            if (!InternetCrackUrlW( buffer, 0, 0, &uc ))
            {
                hr = HRESULT_FROM_WIN32( GetLastError() );
                goto cleanup;
            }

            if (!(hostName = calloc( uc.dwHostNameLength + uc.dwUrlPathLength + uc.dwExtraInfoLength + wcslen( suffix ) + 2, sizeof(WCHAR) )))
            {
                hr = E_OUTOFMEMORY;
                goto cleanup;
            }

            memcpy( hostName, uc.lpszHostName, uc.dwHostNameLength * sizeof(WCHAR) );
            pathAndQuery = hostName + uc.dwHostNameLength + 1;
            memcpy( pathAndQuery, uc.lpszUrlPath, (uc.dwUrlPathLength + uc.dwExtraInfoLength) * sizeof(WCHAR) );

            hr = HttpRequest( L"GET", hostName, pathAndQuery, NULL, NULL, accept, (UCHAR **)&context->buffer, &context->bufferSize );

        cleanup:
            IXThreadingImpl_XAsyncComplete( xthreading, data->async, hr, SUCCEEDED(hr) ? context->bufferSize : 0 );
            if (object) IJsonObject_Release( object );
            if (url) WindowsDeleteString( url );
            if (hostName) free( hostName );
            hr = S_OK;
            break;

        case XAsyncOp_Cleanup:
            IXUserImpl6_XUserCloseHandle( x_user_impl, context->user );
            if (context->buffer) free( context->buffer );
            free( context );
            break;

        case XAsyncOp_Cancel:
            break;
    }

    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureAsync( IXUserImpl6 *iface, XUserHandle user, XUserGamerPictureSize pictureSize, XAsyncBlock *async )
{
    struct XUserGetGamerPictureContext *context;
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, user %p, pictureSize %d, async %p.\n", iface, user, pictureSize, async );

    if (!user || !async) return E_POINTER;
    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    if (!(context = calloc( 1, sizeof(*context) )))
    {
        IXThreadingImpl_Release( xthreading );
        return E_OUTOFMEMORY;
    }

    context->pictureSize = pictureSize;
    if (FAILED(hr = IXUserImpl6_XUserDuplicateHandle( iface, user, &context->user )))
    {
        IXThreadingImpl_Release( xthreading );
        return hr;
    }

    hr = IXThreadingImpl_XAsyncBegin( xthreading, async, context, NULL, "XUserGetGamerPictureAsync", XUserGetGamerPictureProvider );
    IXThreadingImpl_Release( xthreading );
    if (FAILED(hr)) free( context );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, async %p, bufferSize %p.\n", iface, async, bufferSize );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    hr = IXThreadingImpl_XAsyncGetResultSize( xthreading, async, bufferSize );
    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResult( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, SIZE_T *bufferUsed )
{
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, async %p, bufferSize %Iu, buffer %p, bufferUsed %p.\n", iface, async, bufferSize, buffer, bufferUsed );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    hr = IXThreadingImpl_XAsyncGetResult( xthreading, async, NULL, bufferSize, buffer, bufferUsed );
    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetAgeGroup( IXUserImpl6 *iface, XUserHandle user, XUserAgeGroup *ageGroup )
{
    FIXME( "iface %p, user %p, ageGroup %p stub!\n", iface, user, ageGroup );
    *ageGroup = XUserAgeGroup_Adult;
    return S_OK;
}

static HRESULT WINAPI x_user_XUserCheckPrivilege( IXUserImpl6 *iface, XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, BOOLEAN *hasPrivilege, XUserPrivilegeDenyReason *reason )
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

struct XUserGetTokenAndSignatureContext
{
    XUserHandle user;
    XUserGetTokenAndSignatureOptions options;
    char *url;
    char *method;
    SIZE_T headersSize;
    char *headers;
    SIZE_T bodySize;
    void *bodyBuffer;
    BOOLEAN isUtf16;
    union
    {
        XUserGetTokenAndSignatureData *data;
        XUserGetTokenAndSignatureUtf16Data *dataUtf16;
    };
};

static HRESULT WINAPI XUserGetTokenAndSignatureProvider( XAsyncOp op, const XAsyncProviderData *data )
{
    URL_COMPONENTSA uc = { .dwStructSize = sizeof(URL_COMPONENTSA), .dwUrlPathLength = -1, .dwExtraInfoLength = -1 };
    UINT32 authLen, bufLen, dataSize = 0, pathAndQueryLen, tokenLen, userHashLen, wAuthLen, wTokenLen, wUserHashLen;
    struct XUserGetTokenAndSignatureContext *context;
    char *auth, *method, *ptr, *signature;
    const WCHAR *wToken, *wUserHash;
    IXThreadingImpl *xthreading;
    BYTE rawSignature[76] = {}; /* 4 byte version, 8 byte filetime, 64 byte signature */
    WCHAR *wAuth, *wSignature;
    FILETIME timestamp;
    char *buf = NULL;
    HRESULT hr;

    TRACE( "op %d, data %p.\n", op, data );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    context = (struct XUserGetTokenAndSignatureContext *)data->context;

    /*
     * signatures constructed by following
     * https://learn.microsoft.com/gaming/gdk/docs/services/fundamentals/s2s-auth-calls/s2s-calls/live-title-service-calls-xbox-live#proof-keys
     * using signature policy specified for host xboxlive.com at:
     * https://title.mgt.xboxlive.com/titles/default/endpoints?type=1
     * (Version 1, ES256, 0x2000 (8KiB) MaxBodyBytes)
     */

    switch (op)
    {
        case XAsyncOp_Begin:
            hr = IXThreadingImpl_XAsyncSchedule( xthreading, data->async, 0 );
            break;

        case XAsyncOp_GetResult:
            if (context->isUtf16)
                memcpy( data->buffer, context->dataUtf16, sizeof(*context->dataUtf16) + context->dataUtf16->tokenCount );
            else
                memcpy( data->buffer, context->data, sizeof(*context->data) + context->data->tokenSize );
            break;

        case XAsyncOp_DoWork:
            if (!InternetCrackUrlA( context->url, 0, 0, &uc )) goto error;
            pathAndQueryLen = uc.dwUrlPathLength + uc.dwExtraInfoLength;
            wUserHash = WindowsGetStringRawBuffer( context->user->user_hash, &wUserHashLen );
            wToken = WindowsGetStringRawBuffer( context->user->xsts_token, &wTokenLen );
            if (!(userHashLen = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wUserHash, wUserHashLen, NULL, 0, NULL, NULL ))) goto error;
            if (!(tokenLen = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wToken, wTokenLen, NULL, 0, NULL, NULL ))) goto error;
            wAuthLen = wcslen( L"XBL3.0 x=;" ) + wUserHashLen + wTokenLen;
            authLen = strlen( "XBL3.0 x=;" ) + userHashLen + tokenLen;
            bufLen = pathAndQueryLen + authLen + context->headersSize + min( context->bodySize, 0x2000 ) + 18;
            GetSystemTimeAsFileTime( &timestamp );

            if (!(buf = calloc( 1, bufLen )))
            {
                hr = E_OUTOFMEMORY;
                goto cleanup;
            }

            /* version */
            buf[3] = 1;
            memcpy( rawSignature, buf, 4 );

            /* filetime */
            buf[5]  = (timestamp.dwHighDateTime >> 24) & 0xff;
            buf[6]  = (timestamp.dwHighDateTime >> 16) & 0xff;
            buf[7]  = (timestamp.dwHighDateTime >> 8 ) & 0xff;
            buf[8]  =  timestamp.dwHighDateTime        & 0xff;
            buf[9]  = (timestamp.dwLowDateTime  >> 24) & 0xff;
            buf[10] = (timestamp.dwLowDateTime  >> 16) & 0xff;
            buf[11] = (timestamp.dwLowDateTime  >> 8 ) & 0xff;
            buf[12] =  timestamp.dwLowDateTime         & 0xff;
            memcpy( rawSignature + 4, buf + 5, 8 );

            /* method */
            ptr = buf + 14;
            method = context->method;
            while (*method) *(ptr++) = toupper( *(method++) );
            ptr++;

            /* path and query */
            memcpy( ptr, uc.lpszUrlPath, pathAndQueryLen );
            ptr += pathAndQueryLen + 1;

            /* authorization header */
            ptr += strlen( strcpy( ptr, "XBL3.0 x=" ) );
            if (!WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wUserHash, wUserHashLen, ptr, userHashLen, NULL, NULL )) goto error;
            strcat( ptr, ";" );
            ptr += userHashLen + 1;
            if (!WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, wToken, wTokenLen, ptr, tokenLen, NULL, NULL )) goto error;
            ptr += tokenLen + 1;

            /* headers */
            memcpy( ptr, context->headers, context->headersSize );
            ptr += context->headersSize;

            /* body */
            memcpy( ptr, context->bodyBuffer, min( context->bodySize, 0x2000 ) );

            TRACE( "buf: %s\n", debugstr_an( (char *)buf, bufLen ) );
            TRACE( "rawSignature: %s\n", debugstr_an( (char *)rawSignature, 76 ) );

            if (FAILED(hr = IUser_SignData( &context->user->IUser_iface, bufLen, (UCHAR *)buf, 64, rawSignature + 12 ))) goto cleanup;

            if (context->isUtf16)
            {
                /* 76 byte signature = 104 chars base64 with padding */
                dataSize = sizeof(*context->dataUtf16) + (wAuthLen + 106) * sizeof(WCHAR);
                if (!(context->dataUtf16 = calloc( 1, dataSize )))
                {
                    hr = E_OUTOFMEMORY;
                    goto cleanup;
                }

                context->dataUtf16->tokenCount = wAuthLen;
                context->dataUtf16->signatureCount = 104;
                wAuth = (WCHAR *)context->dataUtf16 + sizeof(*context->dataUtf16);
                wSignature = wAuth + wAuthLen + 1;
                context->dataUtf16->token = wAuth;
                context->dataUtf16->signature = wSignature;

                wcscpy( wAuth, L"XBL3.0 x=" );
                wcsncat( wAuth, wUserHash, wUserHashLen );
                wcscat( wAuth, L";" );
                wcsncat( wAuth, wToken, wTokenLen );
                encode_base64_utf16( 76, rawSignature, 104, wSignature );

                TRACE( "token: %s\n", debugstr_wn( context->dataUtf16->token, context->data->tokenSize ) );
                TRACE( "signature: %s\n", debugstr_wn( context->dataUtf16->signature, context->data->signatureSize ) );
            }
            else
            {
                /* 76 byte signature = 104 chars base64 with padding */
                dataSize = sizeof(*context->data) + authLen + 106;
                if (!(context->data = calloc( 1, dataSize )))
                {
                    hr = E_OUTOFMEMORY;
                    goto cleanup;
                }

                context->data->tokenSize = authLen;
                context->data->signatureSize = 104;
                auth = (char *)context->data + sizeof(*context->data);
                signature = auth + authLen + 1;
                context->data->token = auth;
                context->data->signature = signature;

                strcpy( auth, buf + strlen( context->method ) + pathAndQueryLen + 16 );
                encode_base64( 76, rawSignature, 104, signature );

                TRACE( "token: %s\n", debugstr_an( context->data->token, context->data->tokenSize ) );
                TRACE( "signature: %s\n", debugstr_an( context->data->signature, context->data->signatureSize ) );
            }
            goto cleanup;

        error:
            hr = HRESULT_FROM_WIN32( GetLastError() );
        cleanup:
            FIXME( "%#lx.\n", hr );
            if (buf) free( buf );
            if (FAILED(hr))
            {
                dataSize = 0;
                if (context->data) free( context->data );
                if (context->dataUtf16) free( context->dataUtf16 );
            }
            IXThreadingImpl_XAsyncComplete( xthreading, data->async, hr, dataSize );
            hr = S_OK;
            break;

        case XAsyncOp_Cleanup:
            IUser_Release( &context->user->IUser_iface );
            free( context );
            break;

        case XAsyncOp_Cancel:
            break;
    }

    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureAsync( IXUserImpl6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const char *method, const char *url, SIZE_T headerCount, const XUserGetTokenAndSignatureHttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    struct XUserGetTokenAndSignatureContext *context;
    SIZE_T contextSize, headersSize = 0;
    IXThreadingImpl *xthreading;
    HRESULT hr;
    char *ptr;

    TRACE( "iface %p, user %p, options %d, method %s, url %s, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p.\n", iface, user, options, debugstr_a( method ), debugstr_a( url ), headerCount, headers, bodySize, bodyBuffer, async );

    contextSize = sizeof(*context) + strlen( url ) + strlen( method ) + 2 + bodySize;
    for (SIZE_T i = 0; i < headerCount; i++)
        headersSize += (strlen( headers[i].value ) + 1);

    if (!(context = calloc( 1, contextSize + headersSize ))) return E_OUTOFMEMORY;
    IUser_AddRef( &user->IUser_iface );
    context->user = user;
    context->options = options;
    context->headersSize = headersSize;
    context->bodySize = bodySize;
    context->isUtf16 = FALSE;

    /* url */
    ptr = (char *)context + sizeof(*context);
    ptr += strlen( strcpy( (context->url = ptr), url ) ) + 1;
    /* method */
    ptr += (strlen( strcpy( (context->method = ptr), method ) ) + 1);
    /* headers */
    context->headers = ptr;
    for (SIZE_T i = 0; i < headerCount; i++)
        ptr += (strlen( strcpy( ptr, headers[i].value ) ) + 1);
    /* body */
    memcpy( (context->bodyBuffer = ptr), bodyBuffer, bodySize );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) goto error;
    hr = IXThreadingImpl_XAsyncBegin( xthreading, async, context, NULL, "XUserGetTokenAndSignatureAsync", XUserGetTokenAndSignatureProvider );
    IXThreadingImpl_Release( xthreading );
    if (FAILED(hr)) goto error;
    return hr;
error:
    free( context );
    IUser_Release( &user->IUser_iface );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, async %p, bufferSize %p.\n", iface, async, bufferSize );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    hr = IXThreadingImpl_XAsyncGetResultSize( xthreading, async, bufferSize );
    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResult( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureData **ptrToBuffer, SIZE_T *bufferUsed )
{
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p.\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    hr = IXThreadingImpl_XAsyncGetResult( xthreading, async, NULL, bufferSize, buffer, bufferUsed );
    *ptrToBuffer = (XUserGetTokenAndSignatureData *)buffer;
    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Async( IXUserImpl6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const WCHAR *method, const WCHAR *url, SIZE_T headerCount, const XUserGetTokenAndSignatureUtf16HttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    SIZE_T contextSize, headersSize = 0, methodLen, urlLen;
    struct XUserGetTokenAndSignatureContext *context;
    IXThreadingImpl *xthreading;
    HRESULT hr;
    char *ptr;
    int size;

    TRACE( "iface %p, user %p, options %d, method %s, url %s, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p.\n", iface, user, options, debugstr_w( method ), debugstr_w( url ), headerCount, headers, bodySize, bodyBuffer, async );

    if (!(methodLen = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, method, -1, NULL, 0, NULL, NULL ))) return HRESULT_FROM_WIN32( GetLastError() );
    if (!(urlLen = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, url, -1, NULL, 0, NULL, NULL ))) return HRESULT_FROM_WIN32( GetLastError() );
    contextSize = sizeof(*context) + urlLen + methodLen + bodySize;
    for (SIZE_T i = 0; i < headerCount; i++)
    {
        if (!(size = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, headers[i].value, -1, NULL, 0, NULL, NULL ))) return HRESULT_FROM_WIN32( GetLastError() );
        headersSize += size;
    }

    if (!(context = calloc( 1, contextSize + headersSize ))) return E_OUTOFMEMORY;
    IUser_AddRef( &user->IUser_iface );
    context->user = user;
    context->options = options;
    context->headersSize = headersSize;
    context->bodySize = bodySize;
    context->isUtf16 = TRUE;

    /* url */
    ptr = (char *)context + sizeof(*context);
    if (!WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, url, -1, ptr, urlLen, NULL, NULL )) goto error_win32;
    ptr += urlLen;
    /* method */
    if (!WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, method, -1, ptr, methodLen, NULL, NULL )) goto error_win32;
    ptr += methodLen;
    /* headers */
    for (SIZE_T i = 0; i < headerCount; i++)
    {
        if (!(size = WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, headers[i].value, -1, NULL, 0, NULL, NULL ))) goto error_win32;
        if(!WideCharToMultiByte( CP_UTF8, WC_ERR_INVALID_CHARS, headers[i].value, -1, ptr, size, NULL, NULL )) goto error_win32;
        ptr += size;
    }
    /* body */
    memcpy( (context->bodyBuffer = ptr), bodyBuffer, bodySize );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) goto error;
    hr = IXThreadingImpl_XAsyncBegin( xthreading, async, context, NULL, "XUserGetTokenAndSignatureUtf16Async", XUserGetTokenAndSignatureProvider );
    IXThreadingImpl_Release( xthreading );
    if (FAILED(hr)) goto error;
    return hr;

error_win32:
    hr = HRESULT_FROM_WIN32( GetLastError() );
error:
    free( context );
    IUser_Release( &user->IUser_iface );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16ResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, async %p, bufferSize %p.\n", iface, async, bufferSize );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    hr = IXThreadingImpl_XAsyncGetResultSize( xthreading, async, bufferSize );
    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Result( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureUtf16Data **ptrToBuffer, SIZE_T *bufferUsed )
{
    IXThreadingImpl *xthreading;
    HRESULT hr;

    TRACE( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p.\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );

    if (FAILED(hr = QueryApiImpl( &CLSID_XThreadingImpl, &IID_IXThreadingImpl, (void **)&xthreading ))) return hr;
    hr = IXThreadingImpl_XAsyncGetResult( xthreading, async, NULL, bufferSize, buffer, bufferUsed );
    *ptrToBuffer = (XUserGetTokenAndSignatureUtf16Data *)buffer;
    IXThreadingImpl_Release( xthreading );
    return hr;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiAsync( IXUserImpl6 *iface, XUserHandle user, const char *url, XAsyncBlock *async )
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

static BOOLEAN WINAPI x_user_XUserUnregisterForChangeEvent( IXUserImpl6 *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
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

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyAsync( IXUserImpl6 *iface, XUserHandle user, XUserGetMsaTokenSilentlyOptions options, const char *scope, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %u, scope %s, async %p stub!\n", iface, user, options, debugstr_a( scope ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResult( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T resultTokenSize, char *resultToken, SIZE_T *resultTokenUsed )
{
    FIXME( "iface %p, async %p, resultTokenSize %Iu, resultToken %p, resultTokenUsed %p stub!\n", iface, async, resultTokenSize, resultToken, resultTokenUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResultSize( IXUserImpl6 *iface, XAsyncBlock *async, SIZE_T *tokenSize )
{
    FIXME( "iface %p, async %p, tokenSize %p stub!\n", iface, async, tokenSize );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_user_XUserIsStoreUser( IXUserImpl6 *iface, XUserHandle user )
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

static BOOLEAN WINAPI x_user_XUserIsSignOutPresent( IXUserImpl6 *iface )
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

static HRESULT WINAPI x_user_gamertag_XUserGetGamertag( IXUserGamertagImpl *iface, XUserHandle user, XUserGamertagComponent gamertagComponent, SIZE_T gamertagSize, char *gamertag, SIZE_T *gamertagUsed )
{
    FIXME( "iface %p, user %p, gamertagComponent %d, gamertagSize %Iu, gamertag %p, gamertagUsed %p semi-stub!\n", iface, user, gamertagComponent, gamertagSize, gamertag, gamertagUsed );

    switch (gamertagComponent)
    {
        case XUserGamertagComponent_Classic:
            if (gamertagSize <= user->classic_gamertag_size)
                return HRESULT_FROM_WIN32( ERROR_INSUFFICIENT_BUFFER );

            memcpy( gamertag, user->classic_gamertag, user->classic_gamertag_size );
            gamertag[user->classic_gamertag_size] = 0;
            if (gamertagUsed) *gamertagUsed = user->classic_gamertag_size + 1;
            return S_OK;

        default:
            /* TODO: handle modern, modern suffix & unique modern components */
            break;
    }

    return E_INVALIDARG;
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

static BOOLEAN WINAPI x_user_device_XUserUnregisterForDeviceAssociationChanged( IXUserDeviceImpl *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
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

static BOOLEAN WINAPI x_user_device_XUserUnregisterForDefaultAudioEndpointUtf16Changed( IXUserDeviceImpl *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
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
