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

HRESULT WINAPI XGameStreamingGetAssociatedFrame( IGameInputReading *gamepadReading, D3D12XBOX_FRAME_PIPELINE_TOKEN *framePipelineToken )
{
    return E_NOTIMPL;
}

UINT32 WINAPI XGameStreamingGetClientCount()
{
    return 0;
}

HRESULT WINAPI XGameStreamingGetClientIPAddress( XGameStreamingClientId client, SIZE_T ipAddressSize, char *ipAddress )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingGetClients( UINT32 clientCount, XGameStreamingClientId *clients, UINT32 *clientsUsed )
{
    return E_NOTIMPL;
}

XGameStreamingConnectionState WINAPI XGameStreamingGetConnectionState( XGameStreamingClientId client )
{
    return XGameStreamingConnectionState_Disconnected;
}

HRESULT WINAPI XGameStreamingGetDisplayDetails( XGameStreamingClientId client, UINT32 maxSupportedPixels, float widestSupportedAspectRatio, float tallestSupportedAspectRatio, XGameStreamingDisplayDetails *displayDetails )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingGetGamepadPhysicality( IGameInputReading *gamepadReading, XGameStreamingGamepadPhysicality *gamepadPhysicality )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingGetLastFrameDisplayed( XGameStreamingClientId client, D3D12XBOX_FRAME_PIPELINE_TOKEN *framePipelineToken )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingGetServerLocationName( SIZE_T serverLocationNameSize, char *serverLocationName )
{
    return E_NOTIMPL;
}

SIZE_T WINAPI XGameStreamingGetServerLocationNameSize()
{
    return 0;
}

HRESULT WINAPI XGameStreamingGetSessionId( XGameStreamingClientId client, SIZE_T sessionIdSize, char *sessionId, SIZE_T *sessionIdUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingGetStreamAddedLatency( XGameStreamingClientId client, UINT32 *averageInputLatencyUs, UINT32 *averageOutputLatencyUs, UINT32 *standardDeviationUs )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingGetStreamPhysicalDimensions( XGameStreamingClientId client, UINT32 *horizontalMm, UINT32 *verticalMm )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingGetTouchBundleVersion( XGameStreamingClientId client, XVersion *version, SIZE_T versionNameSize, char *versionName )
{
    return E_NOTIMPL;
}

SIZE_T WINAPI XGameStreamingGetTouchBundleVersionNameSize( XGameStreamingClientId client )
{
    return 0;
}

void WINAPI XGameStreamingHideTouchControls()
{
}

void WINAPI XGameStreamingHideTouchControlsOnClient( XGameStreamingClientId client )
{
}

HRESULT WINAPI XGameStreamingInitialize()
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XGameStreamingIsStreaming()
{
    return FALSE;
}

HRESULT WINAPI XGameStreamingIsTouchInputEnabled( XGameStreamingClientId client, BOOLEAN *touchInputEnabled )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingRegisterClientPropertiesChanged( XGameStreamingClientId client, XTaskQueueHandle queue, void *context, XGameStreamingClientPropertiesChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingRegisterConnectionStateChanged( XTaskQueueHandle queue, void *context, XGameStreamingConnectionStateChangedCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingSetResolution( UINT32 width, UINT32 height )
{
    return E_NOTIMPL;
}

void WINAPI XGameStreamingShowTouchControlLayout( const char *layout )
{
}

void WINAPI XGameStreamingShowTouchControlLayoutOnClient( XGameStreamingClientId client, const char *layout )
{
}

HRESULT WINAPI XGameStreamingShowTouchControlsWithStateUpdate( const char *layout, SIZE_T operationCount, const XGameStreamingTouchControlsStateOperation *operations )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingShowTouchControlsWithStateUpdateOnClient( XGameStreamingClientId client, const char *layout, SIZE_T operationCount, const XGameStreamingTouchControlsStateOperation *operations )
{
    return E_NOTIMPL;
}

void WINAPI XGameStreamingUninitialize()
{
}

BOOLEAN WINAPI XGameStreamingUnregisterClientPropertiesChanged( XGameStreamingClientId client, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}

BOOLEAN WINAPI XGameStreamingUnregisterConnectionStateChanged( XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}

HRESULT WINAPI XGameStreamingUpdateTouchControlsState( SIZE_T operationCount, const XGameStreamingTouchControlsStateOperation *operations )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameStreamingUpdateTouchControlsStateOnClient( XGameStreamingClientId client, SIZE_T operationCount, const XGameStreamingTouchControlsStateOperation *operations )
{
    return E_NOTIMPL;
}
