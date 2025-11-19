/*
 * Xbox Game runtime Library
 *  GDK Component: Networking API -> XNetworking
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

#include "XNetworking.h"

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

static inline struct x_networking *impl_from_IXNetworking( IXNetworking *iface )
{
    return CONTAINING_RECORD( iface, struct x_networking, IXNetworking_iface );
}

static HRESULT WINAPI x_networking_QueryInterface( IXNetworking *iface, REFIID iid, void **out )
{
    struct x_networking *impl = impl_from_IXNetworking( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IXNetworking ) ||
        /*
         * For some strange, unexplainable reason, the xgameruntime.lib library shipped with
         * PlayFabMultiplayerGDK has the GUID of IXNetworkingImpl of the class Id of XNetworking.
         * This is for compatibility reasons only.
         */
        IsEqualGUID( iid, &CLSID_XNetworkingImpl ))
    {
        *out = &impl->IXNetworking_iface;
        IXNetworking_AddRef( *out );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_networking_AddRef( IXNetworking *iface )
{
    struct x_networking *impl = impl_from_IXNetworking( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_networking_Release( IXNetworking *iface )
{
    struct x_networking *impl = impl_from_IXNetworking( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_networking_XNetworkingQueryPreferredLocalUdpMultiplayerPort( IXNetworking *iface, UINT16 *preferredLocalUdpMultiplayerPort )
{
    FIXME( "iface %p, preferredLocalUdpMultiplayerPort %p stub!\n", iface, preferredLocalUdpMultiplayerPort );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQueryPreferredLocalUdpMultiplayerPortAsync( IXNetworking *iface, XAsyncBlock *asyncBlock )
{
    FIXME( "iface %p, asyncBlock %p stub!\n", iface, asyncBlock );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQueryPreferredLocalUdpMultiplayerPortAsyncResult( IXNetworking *iface, XAsyncBlock *asyncBlock, UINT16 *preferredLocalUdpMultiplayerPort )
{
    FIXME( "iface %p, asyncBlock %p, preferredLocalUdpMultiplayerPort %p stub!\n", iface, asyncBlock, preferredLocalUdpMultiplayerPort );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingRegisterPreferredLocalUdpMultiplayerPortChanged( IXNetworking *iface, XTaskQueueHandle queue, void *context, XNetworkingPreferredLocalUdpMultiplayerPortChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_networking_XNetworkingUnregisterPreferredLocalUdpMultiplayerPortChanged( IXNetworking *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_networking_XNetworkingQuerySecurityInformationForUrlAsync( IXNetworking *iface, const CHAR *url, XAsyncBlock *asyncBlock )
{
    FIXME( "iface %p, url %p, asyncBlock %p stub!\n", iface, url, asyncBlock );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQuerySecurityInformationForUrlAsyncResultSize( IXNetworking *iface, XAsyncBlock *asyncBlock, SIZE_T *securityInformationBufferByteCount )
{
    FIXME( "iface %p, asyncBlock %p, securityInformationBufferByteCount %p stub!\n", iface, asyncBlock, securityInformationBufferByteCount );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQuerySecurityInformationForUrlAsyncResult( IXNetworking *iface, XAsyncBlock *asyncBlock, SIZE_T securityInformationBufferByteCount, SIZE_T *securityInformationBufferByteCountUsed, UINT8 *securityInformationBuffer, XNetworkingSecurityInformation **securityInformation )
{
    FIXME( "iface %p, asyncBlock %p, securityInformationBufferByteCount %Iu, securityInformationBufferByteCountUsed %p, securityInformationBuffer %p, securityInformation %p stub!\n", iface, asyncBlock, securityInformationBufferByteCount, securityInformationBufferByteCountUsed, securityInformationBuffer, securityInformation );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQuerySecurityInformationForUrlUtf16Async( IXNetworking *iface, const WCHAR *url, XAsyncBlock *asyncBlock )
{
    FIXME( "iface %p, url %p, asyncBlock %p stub!\n", iface, url, asyncBlock );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQuerySecurityInformationForUrlUtf16AsyncResultSize( IXNetworking *iface, XAsyncBlock *asyncBlock, SIZE_T *securityInformationBufferByteCount )
{
    FIXME( "iface %p, asyncBlock %p, securityInformationBufferByteCount %p stub!\n", iface, asyncBlock, securityInformationBufferByteCount );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQuerySecurityInformationForUrlUtf16AsyncResult( IXNetworking *iface, XAsyncBlock *asyncBlock, SIZE_T securityInformationBufferByteCount, SIZE_T *securityInformationBufferByteCountUsed, UINT8 *securityInformationBuffer, XNetworkingSecurityInformation **securityInformation )
{
    FIXME( "iface %p, asyncBlock %p, securityInformationBufferByteCount %Iu, securityInformationBufferByteCountUsed %p, securityInformationBuffer %p, securityInformation %p stub!\n", iface, asyncBlock, securityInformationBufferByteCount, securityInformationBufferByteCountUsed, securityInformationBuffer, securityInformation );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingVerifyServerCertificate( IXNetworking *iface, void *requestHandle, const XNetworkingSecurityInformation *securityInformation )
{
    FIXME( "iface %p, requestHandle %p, securityInformation %p stub!\n", iface, requestHandle, securityInformation );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingGetConnectivityHint( IXNetworking *iface, XNetworkingConnectivityHint *connectivityHint )
{
    XNetworkingConnectivityHint hint;

    TRACE( "iface %p, connectivityHint %p\n", iface, connectivityHint );

    hint.ianaInterfaceType = 0; /* There's no direct way to get NDIS interface type in userspace. */
    hint.roaming = FALSE;
    hint.overDataLimit = FALSE;
    hint.networkInitialized = TRUE;
    hint.approachingDataLimit = FALSE;
    hint.connectivityLevel = XNetworkingConnectivityLevelHint_InternetAccess;
    hint.connectivityCost = XNetworkingConnectivityCostHint_Unrestricted;

    *connectivityHint = hint;

    return S_OK;
}

static HRESULT WINAPI x_networking_XNetworkingRegisterConnectivityHintChanged( IXNetworking *iface, XTaskQueueHandle queue, void *context, XNetworkingConnectivityHintChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return S_OK;
}

static BOOLEAN WINAPI x_networking_XNetworkingUnregisterConnectivityHintChanged( IXNetworking *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_networking_XNetworkingQueryConfigurationSetting( IXNetworking *iface, XNetworkingConfigurationSetting configurationSetting, UINT64 *value )
{
    FIXME( "iface %p, configurationSetting %d, value %p stub!\n", iface, configurationSetting, value );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingSetConfigurationSetting( IXNetworking *iface, XNetworkingConfigurationSetting configurationParameter, UINT64 value )
{
    FIXME( "iface %p, configurationParameter %d, value %llu stub!\n", iface, configurationParameter, value );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_networking_XNetworkingQueryStatistics( IXNetworking *iface, XNetworkingStatisticsType statisticsType, XNetworkingStatisticsBuffer *statisticsBuffer )
{
    FIXME( "iface %p, statisticsType %d, statisticsBuffer %p stub!\n", iface, statisticsType, statisticsBuffer );
    return E_NOTIMPL;
}

static const struct IXNetworkingVtbl x_networking_vtbl =
{
    x_networking_QueryInterface,
    x_networking_AddRef,
    x_networking_Release,
    /* IXNetworking methods */
    x_networking_XNetworkingQueryPreferredLocalUdpMultiplayerPort,
    x_networking_XNetworkingQueryPreferredLocalUdpMultiplayerPortAsync,
    x_networking_XNetworkingQueryPreferredLocalUdpMultiplayerPortAsyncResult,
    x_networking_XNetworkingRegisterPreferredLocalUdpMultiplayerPortChanged,
    x_networking_XNetworkingUnregisterPreferredLocalUdpMultiplayerPortChanged,
    x_networking_XNetworkingQuerySecurityInformationForUrlAsync,
    x_networking_XNetworkingQuerySecurityInformationForUrlAsyncResultSize,
    x_networking_XNetworkingQuerySecurityInformationForUrlAsyncResult,
    x_networking_XNetworkingQuerySecurityInformationForUrlUtf16Async,
    x_networking_XNetworkingQuerySecurityInformationForUrlUtf16AsyncResultSize,
    x_networking_XNetworkingQuerySecurityInformationForUrlUtf16AsyncResult,
    x_networking_XNetworkingVerifyServerCertificate,
    x_networking_XNetworkingGetConnectivityHint,
    x_networking_XNetworkingRegisterConnectivityHintChanged,
    x_networking_XNetworkingUnregisterConnectivityHintChanged,
    x_networking_XNetworkingQueryConfigurationSetting,
    x_networking_XNetworkingSetConfigurationSetting,
    x_networking_XNetworkingQueryStatistics,
};

static struct x_networking x_networking =
{
    {&x_networking_vtbl},
    0,
};

IXNetworking *x_networking_impl = &x_networking.IXNetworking_iface;
