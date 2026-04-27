/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XAppCapture
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

#include "private.h"

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

struct capture
{
    IXAppCapture IXAppCapture_iface;
    IXAppCapture2 IXAppCapture2_iface;
    LONG ref;
};

static inline struct capture *impl_from_IXAppCapture( IXAppCapture *iface )
{
    return CONTAINING_RECORD( iface, struct capture, IXAppCapture_iface );
}

static HRESULT WINAPI capture_QueryInterface( IXAppCapture *iface, REFIID iid, void **out )
{
    struct capture *impl = impl_from_IXAppCapture( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown     ) ||
        IsEqualGUID( iid, &IID_IXAppCapture ))
    {
        IXAppCapture_AddRef( *out = &impl->IXAppCapture_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI capture_AddRef( IXAppCapture *iface )
{
    struct capture *impl = impl_from_IXAppCapture( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI capture_Release( IXAppCapture *iface )
{
    struct capture *impl = impl_from_IXAppCapture( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static BOOLEAN WINAPI capture_XAppBroadcastIsAppBroadcasting( IXAppCapture *iface )
{
    FIXME( "iface %p stub!\n", iface );
    return FALSE;
}

static HRESULT WINAPI capture_XAppBroadcastShowUI( IXAppCapture *iface, XUserHandle requestingUser )
{
    FIXME( "iface %p requestingUser %p stub!\n", iface, requestingUser );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppBroadcastGetStatus( IXAppCapture *iface, XUserHandle requestingUser, XAppBroadcastStatus *appBroadcastStatus )
{
    FIXME( "iface %p, requestingUser %p, appBroadcastStatus %p stub!\n", iface, requestingUser, appBroadcastStatus );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppBroadcastRegisterIsAppBroadcastingChanged( IXAppCapture *iface, XTaskQueueHandle queue, void *context, XAppBroadcastMonitorCallback *appBroadcastMonitorCallback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, appBroadcastMonitorCallback %p, token %p stub!\n", iface, queue, context, appBroadcastMonitorCallback, token );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI capture_XAppBroadcastUnregisterIsAppBroadcastingChanged( IXAppCapture *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return TRUE;
}

static HRESULT WINAPI capture_XAppCaptureMetadataAddStringEvent( IXAppCapture *iface, const char *name, const char *value, XAppCaptureMetadataPriority priority )
{
    FIXME( "iface %p, name %s, value %s, priority %d stub!\n", iface, debugstr_a( name ), debugstr_a( value ), priority );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataAddInt32Event( IXAppCapture *iface, const char *name, INT32 value, XAppCaptureMetadataPriority priority )
{
    FIXME( "iface %p, name %s, value %d, priority %d stub!\n", iface, debugstr_a( name ), value, priority );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataAddDoubleEvent( IXAppCapture *iface, const char *name, double value, XAppCaptureMetadataPriority priority )
{
    FIXME( "iface %p, name %s, value %e, priority %d stub!\n", iface, debugstr_a( name ), value, priority );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataStartStringState( IXAppCapture *iface, const char *name, const char *value, XAppCaptureMetadataPriority priority )
{
    FIXME( "iface %p, name %s, value %s, priority %d stub!\n", iface, debugstr_a( name ), debugstr_a( value ), priority );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataStartInt32State( IXAppCapture *iface, const char *name, INT32 value, XAppCaptureMetadataPriority priority )
{
    FIXME( "iface %p, name %s, value %d, priority %d stub!\n", iface, debugstr_a( name ), value, priority );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataStartDoubleState( IXAppCapture *iface, const char *name, double value, XAppCaptureMetadataPriority priority )
{
    FIXME( "iface %p, name %s, value %e, priority %d stub!\n", iface, debugstr_a( name ), value, priority );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataStopState( IXAppCapture *iface, const char *name )
{
    FIXME( "iface %p, name %s stub!\n", iface, debugstr_a( name ) );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataStopAllStates( IXAppCapture *iface )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureMetadataRemainingStorageBytesAvailable( IXAppCapture *iface, UINT64 *value )
{
    FIXME( "iface %p, value %p stub!\n", iface, value );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture_XAppCaptureRegisterMetadataPurged( IXAppCapture *iface, XTaskQueueHandle queue, void *context, XAppCaptureMetadataPurgedCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI capture_XAppCaptureUnRegisterMetadataPurged( IXAppCapture *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return TRUE;
}

static const struct IXAppCaptureVtbl capture_vtbl =
{
    capture_QueryInterface,
    capture_AddRef,
    capture_Release,
    /* IXAppCapture methods */
    capture_XAppBroadcastIsAppBroadcasting,
    capture_XAppBroadcastShowUI,
    capture_XAppBroadcastGetStatus,
    capture_XAppBroadcastRegisterIsAppBroadcastingChanged,
    capture_XAppBroadcastUnregisterIsAppBroadcastingChanged,
    capture_XAppCaptureMetadataAddStringEvent,
    capture_XAppCaptureMetadataAddInt32Event,
    capture_XAppCaptureMetadataAddDoubleEvent,
    capture_XAppCaptureMetadataStartStringState,
    capture_XAppCaptureMetadataStartInt32State,
    capture_XAppCaptureMetadataStartDoubleState,
    capture_XAppCaptureMetadataStopState,
    capture_XAppCaptureMetadataStopAllStates,
    capture_XAppCaptureMetadataRemainingStorageBytesAvailable,
    capture_XAppCaptureRegisterMetadataPurged,
    capture_XAppCaptureUnRegisterMetadataPurged,
};

static inline struct capture *impl_from_IXAppCapture2( IXAppCapture2 *iface )
{
    return CONTAINING_RECORD( iface, struct capture, IXAppCapture2_iface );
}

static HRESULT WINAPI capture2_QueryInterface( IXAppCapture2 *iface, REFIID iid, void **out )
{
    struct capture *impl = impl_from_IXAppCapture2( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown      ) ||
        IsEqualGUID( iid, &IID_IXAppCapture2 ))
    {
        IXAppCapture2_AddRef( *out = &impl->IXAppCapture2_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI capture2_AddRef( IXAppCapture2 *iface )
{
    struct capture *impl = impl_from_IXAppCapture2( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI capture2_Release( IXAppCapture2 *iface )
{
    struct capture *impl = impl_from_IXAppCapture2( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI capture2_XAppCaptureTakeDiagnosticScreenshot( IXAppCapture2 *iface, BOOLEAN gamescreenOnly, XAppCaptureScreenshotFormatFlag captureFlags, const char *filenamePrefix, XAppCaptureDiagnosticScreenshotResult *result )
{
    FIXME( "iface %p, gamescreenOnly %d, captureFlags %x, filenamePrefix %s, result %p stub!\n", iface, gamescreenOnly, captureFlags, debugstr_a( filenamePrefix ), result );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureRecordDiagnosticClip( IXAppCapture2 *iface, time_t startTime, UINT32 durationInMs, const char *filenamePrefix, XAppCaptureRecordClipResult *result )
{
    FIXME( "iface %p, startTime %Iu, durationInMs %u, filenamePrefix %s, result %p stub!\n", iface, startTime, durationInMs, debugstr_a( filenamePrefix ), result );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureTakeScreenshot( IXAppCapture2 *iface, XUserHandle requestingUser, XAppCaptureTakeScreenshotResult *result )
{
    FIXME( "iface %p, requestingUser %p, result %p stub!\n", iface, requestingUser, result );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureOpenScreenshotStream( IXAppCapture2 *iface, const char *localId, XAppCaptureScreenshotFormatFlag screenshotFormat, XAppCaptureScreenshotStreamHandle *handle, UINT64 *totalBytes )
{
    FIXME( "iface %p, localId %s, screenshotFormat %d, handle %p, totalBytes %p stub!\n", iface, debugstr_a( localId ), screenshotFormat, handle, totalBytes );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureReadScreenshotStream( IXAppCapture2 *iface, XAppCaptureScreenshotStreamHandle handle, UINT64 startPosition, UINT32 bytesToRead, UINT8 *bytes, UINT32 *bytesWritten )
{
    FIXME( "iface %p, handle %p, startPosition %llu, bytesToRead %u, bytes %p, bytesWritten %p stub!\n", iface, handle, startPosition, bytesToRead, bytes, bytesWritten );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureCloseScreenshotStream( IXAppCapture2 *iface, XAppCaptureScreenshotStreamHandle handle )
{
    FIXME( "iface %p, handle %p stub!\n", iface, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureEnableRecord( IXAppCapture2 *iface )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureDisableRecord( IXAppCapture2 *iface )
{
    FIXME( "iface %p stub!\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureGetVideoCaptureSettings( IXAppCapture2 *iface, XAppCaptureVideoCaptureSettings *userCaptureSettings )
{
    FIXME( "iface %p, userCaptureSettings %p stub!\n", iface, userCaptureSettings );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureRecordTimespan( IXAppCapture2 *iface, const SYSTEMTIME *startTimestamp, UINT64 durationInMilliseconds, XAppCaptureLocalResult *result )
{
    FIXME( "iface %p, startTimestamp %p, durationInMilliseconds %llu, result %p stub!\n", iface, startTimestamp, durationInMilliseconds, result );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureReadLocalStream( IXAppCapture2 *iface, XAppCaptureLocalStreamHandle handle, SIZE_T startPosition, UINT32 bytesToRead, UINT8 *bytes, UINT32 *bytesWritten )
{
    FIXME( "iface %p, handle %p, startPosition %Iu, bytesToRead %u, bytes %p, bytesWritten %p stub!\n", iface, handle, startPosition, bytesToRead, bytes, bytesWritten );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureCloseLocalStream( IXAppCapture2 *iface, XAppCaptureLocalStreamHandle handle )
{
    FIXME( "iface %p, handle %p stub!\n", iface, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureStartUserRecord( IXAppCapture2 *iface, XUserHandle requestingUser, UINT32 localIdBufferLength, char *localIdBuffer )
{
    FIXME( "iface %p, requestingUser %p, localIdBufferLength %u, localIdBuffer %p stub!\n", iface, requestingUser, localIdBufferLength, localIdBuffer );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureStopUserRecord( IXAppCapture2 *iface, const char *localId, XAppCaptureUserRecordingResult *result )
{
    FIXME( "iface %p, localId %s, result %p stub!\n", iface, debugstr_a( localId ), result );
    return E_NOTIMPL;
}

static HRESULT WINAPI capture2_XAppCaptureCancelUserRecord( IXAppCapture2 *iface, const char *localId )
{
    FIXME( "iface %p, localId %s stub!\n", iface, debugstr_a( localId ) );
    return E_NOTIMPL;
}

static const struct IXAppCapture2Vtbl capture2_vtbl =
{
    capture2_QueryInterface,
    capture2_AddRef,
    capture2_Release,
    /* IXAppCapture2 methods */
    capture2_XAppCaptureTakeDiagnosticScreenshot,
    capture2_XAppCaptureRecordDiagnosticClip,
    capture2_XAppCaptureTakeScreenshot,
    capture2_XAppCaptureOpenScreenshotStream,
    capture2_XAppCaptureReadScreenshotStream,
    capture2_XAppCaptureCloseScreenshotStream,
    capture2_XAppCaptureEnableRecord,
    capture2_XAppCaptureDisableRecord,
    capture2_XAppCaptureGetVideoCaptureSettings,
    capture2_XAppCaptureRecordTimespan,
    capture2_XAppCaptureReadLocalStream,
    capture2_XAppCaptureCloseLocalStream,
    capture2_XAppCaptureStartUserRecord,
    capture2_XAppCaptureStopUserRecord,
    capture2_XAppCaptureCancelUserRecord,
};

static struct capture capture =
{
    {&capture_vtbl},
    {&capture2_vtbl},
    0,
};

IXAppCapture *capture_impl = &capture.IXAppCapture_iface;
IXAppCapture2 *capture2_impl = &capture.IXAppCapture2_iface;
