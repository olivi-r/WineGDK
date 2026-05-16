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

#include <wtypes.h>
#include <xgameruntime.h>

HRESULT WINAPI XNetworkingGetConnectivityHint( XNetworkingConnectivityHint *connectivityHint )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQueryConfigurationSetting( XNetworkingConfigurationSetting configurationSetting, UINT64 *value )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQueryPreferredLocalUdpMultiplayerPort( UINT16 *preferredLocalUdpMultiplayerPort )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQueryPreferredLocalUdpMultiplayerPortAsync( XAsyncBlock *asyncBlock )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQueryPreferredLocalUdpMultiplayerPortAsyncResult( XAsyncBlock *asyncBlock, UINT16 *preferredLocalUdpMultiplayerPort )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQuerySecurityInformationForUrlAsync( const char *url, XAsyncBlock *asyncBlock )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQuerySecurityInformationForUrlAsyncResult( XAsyncBlock *asyncBlock, SIZE_T securityInformationBufferByteCount, SIZE_T *securityInformationBufferByteCountUsed, UINT8 *securityInformationBuffer, XNetworkingSecurityInformation **securityInformation )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQuerySecurityInformationForUrlAsyncResultSize( XAsyncBlock *asyncBlock, SIZE_T *securityInformationBufferByteCount )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQuerySecurityInformationForUrlUtf16Async( const WCHAR *url, XAsyncBlock *asyncBlock )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQuerySecurityInformationForUrlUtf16AsyncResult( XAsyncBlock *asyncBlock, SIZE_T securityInformationBufferByteCount, SIZE_T *securityInformationBufferByteCountUsed, UINT8 *securityInformationBuffer, XNetworkingSecurityInformation **securityInformation )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQuerySecurityInformationForUrlUtf16AsyncResultSize( XAsyncBlock *asyncBlock, SIZE_T *securityInformationBufferByteCount )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingQueryStatistics( XNetworkingStatisticsType statisticsType, XNetworkingStatisticsBuffer *statisticsBuffer )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingRegisterConnectivityHintChanged( XTaskQueueHandle queue, void *context, XNetworkingConnectivityHintChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingRegisterPreferredLocalUdpMultiplayerPortChanged( XTaskQueueHandle queue, void *context, XNetworkingPreferredLocalUdpMultiplayerPortChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XNetworkingSetConfigurationSetting( XNetworkingConfigurationSetting configurationParameter, UINT64 value )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XNetworkingUnregisterConnectivityHintChanged( XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}

BOOLEAN WINAPI XNetworkingUnregisterPreferredLocalUdpMultiplayerPortChanged( XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}

HRESULT WINAPI XNetworkingVerifyServerCertificate( void *requestHandle, const XNetworkingSecurityInformation *securityInformation )
{
    return E_NOTIMPL;
}
