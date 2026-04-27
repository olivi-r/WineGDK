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

HRESULT WINAPI XAppBroadcastGetStatus( XUserHandle requestingUser, XAppBroadcastStatus *appBroadcastStatus )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XAppBroadcastIsAppBroadcasting()
{
    return FALSE;
}

HRESULT WINAPI XAppBroadcastRegisterIsAppBroadcastingChanged( XTaskQueueHandle queue, void *context, XAppBroadcastMonitorCallback *appBroadcastMonitorCallback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppBroadcastShowUI( XUserHandle requestingUser )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XAppBroadcastUnregisterIsAppBroadcastingChanged( XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}

HRESULT WINAPI XAppCaptureCancelUserRecord( const char *localId )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureCloseLocalStream( XAppCaptureLocalStreamHandle handle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureCloseScreenshotStream( XAppCaptureScreenshotStreamHandle handle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureDisableRecord()
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureEnableRecord()
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureGetVideoCaptureSettings( XAppCaptureVideoCaptureSettings *userCaptureSettings )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataAddDoubleEvent( const char *name, double value, XAppCaptureMetadataPriority priority )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataAddInt32Event( const char *name, INT32 value, XAppCaptureMetadataPriority priority )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataAddStringEvent( const char *name, const char *value, XAppCaptureMetadataPriority priority )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataRemainingStorageBytesAvailable( UINT64 *value )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataStartDoubleState( const char *name, double value, XAppCaptureMetadataPriority priority )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataStartInt32State( const char *name, INT32 value, XAppCaptureMetadataPriority priority )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataStartStringState( const char *name, const char *value, XAppCaptureMetadataPriority priority )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataStopAllStates()
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureMetadataStopState( const char *name )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureOpenScreenshotStream( const char *localId, XAppCaptureScreenshotFormatFlag screenshotFormat, XAppCaptureScreenshotStreamHandle *handle, UINT64 *totalBytes )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureReadLocalStream( XAppCaptureLocalStreamHandle handle, SIZE_T startPosition, UINT32 bytesToRead, UINT8 *buffer, UINT32 *bytesWritten )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureReadScreenshotStream( XAppCaptureScreenshotStreamHandle handle, UINT64 startPosition, UINT32 bytesToRead, UINT8 *buffer, UINT32 *bytesWritten )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureRecordDiagnosticClip( time_t startTime, UINT32 durationInMs, const char *filenamePrefix, XAppCaptureRecordClipResult *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureRecordTimespan( const SYSTEMTIME *startTimestamp, UINT64 durationInMilliseconds, XAppCaptureLocalResult *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureRegisterMetadataPurged( XTaskQueueHandle queue, void *context, XAppCaptureMetadataPurgedCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureStartUserRecord( XUserHandle requestingUser, UINT32 localIdBufferLength, char *localIdBuffer )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureStopUserRecord( const char *localId, XAppCaptureUserRecordingResult *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureTakeDiagnosticScreenshot( BOOLEAN gamescreenOnly, XAppCaptureScreenshotFormatFlag captureFlags, const char *filenamePrefix, XAppCaptureDiagnosticScreenshotResult *result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XAppCaptureTakeScreenshot( XUserHandle requestingUser, XAppCaptureTakeScreenshotResult *result )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XAppCaptureUnRegisterMetadataPurged( XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}
