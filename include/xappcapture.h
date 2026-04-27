/*
 * Copyright (C) the Wine project
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

#ifndef __WINE_XAPPCAPTURE_H
#define __WINE_XAPPCAPTURE_H

typedef enum XAppCaptureMetadataPriority XAppCaptureMetadataPriority;
typedef enum XAppCaptureScreenshotFormatFlag XAppCaptureScreenshotFormatFlag;
typedef enum XAppCaptureVideoColorFormat XAppCaptureVideoColorFormat;
typedef enum XAppCaptureVideoEncoding XAppCaptureVideoEncoding;

typedef struct XAppCaptureLocalStream *XAppCaptureLocalStreamHandle;
typedef struct XAppCaptureScreenshotStream *XAppCaptureScreenshotStreamHandle;

typedef struct XAppBroadcastStatus XAppBroadcastStatus;
typedef struct XAppCaptureDiagnosticScreenshotResult XAppCaptureDiagnosticScreenshotResult;
typedef struct XAppCaptureLocalResult XAppCaptureLocalResult;
typedef struct XAppCaptureRecordClipResult XAppCaptureRecordClipResult;
typedef struct XAppCaptureScreenshotFile XAppCaptureScreenshotFile;
typedef struct XAppCaptureScreenshotStream XAppCaptureScreenshotStream;
typedef struct XAppCaptureTakeScreenshotResult XAppCaptureTakeScreenshotResult;
typedef struct XAppCaptureUserRecordingResult XAppCaptureUserRecordingResult;
typedef struct XAppCaptureVideoCaptureSettings XAppCaptureVideoCaptureSettings;

typedef void __stdcall XAppBroadcastMonitorCallback( void *context );
typedef void __stdcall XAppCaptureMetadataPurgedCallback( void *context );

enum XAppCaptureMetadataPriority
{
    XAppCaptureMetadataPriority_Informational,
    XAppCaptureMetadataPriority_Important,
};

enum XAppCaptureScreenshotFormatFlag
{
    XAppCaptureScreenshotFormatFlag_SDR = 1,
    XAppCaptureScreenshotFormatFlag_HDR = 2,
};

enum XAppCaptureVideoColorFormat
{
    XAppCaptureVideoColorFormat_SDR,
    XAppCaptureVideoColorFormat_HDR,
};

enum XAppCaptureVideoEncoding
{
    XAppCaptureVideoEncoding_H264,
    XAppCaptureVideoEncoding_HEVC,
};

struct XAppBroadcastStatus
{
    BOOLEAN canStartBroadcast;
    BOOLEAN isAnyAppBroadcasting;
    BOOLEAN isCaptureResourceUnavailable;
    BOOLEAN isGameStreamInProgress;
    BOOLEAN isGpuConstrained;
    BOOLEAN isAppInactive;
    BOOLEAN isBlockedForApp;
    BOOLEAN isDisabledByUser;
    BOOLEAN isDisabledBySystem;
};

struct XAppCaptureScreenshotFile
{
    char path[260];
    SIZE_T fileSize;
    UINT32 width;
    UINT32 height;
};

struct XAppCaptureDiagnosticScreenshotResult
{
    SIZE_T fileCount;
    XAppCaptureScreenshotFile files[10];
};

struct XAppCaptureLocalResult
{
    XAppCaptureLocalStreamHandle clipHandle;
    SIZE_T fileSizeInBytes;
    SYSTEMTIME clipStartTimestamp;
    UINT64 durationInMilliseconds;
    UINT32 width;
    UINT32 height;
    XAppCaptureVideoEncoding encoding;
    XAppCaptureVideoColorFormat colorFormat;
};

struct XAppCaptureRecordClipResult
{
    char path[260];
    SIZE_T fileSize;
    time_t startTime;
    UINT32 durationInMs;
    UINT32 width;
    UINT32 height;
    XAppCaptureVideoEncoding encoding;
};

struct XAppCaptureScreenshotStream {};

struct XAppCaptureTakeScreenshotResult
{
    char localId[250];
    XAppCaptureScreenshotFormatFlag availableScreenshotFormats;
};

struct XAppCaptureUserRecordingResult
{
    SIZE_T fileSizeInBytes;
    SYSTEMTIME clipStartTimestamp;
    UINT64 durationInMilliseconds;
    UINT32 width;
    UINT32 height;
    XAppCaptureVideoEncoding encoding;
    XAppCaptureVideoColorFormat colorFormat;
};

struct XAppCaptureVideoCaptureSettings
{
    UINT32 width;
    UINT32 height;
    UINT64 maxRecordTimespanDurationInMs;
    XAppCaptureVideoEncoding encoding;
    XAppCaptureVideoColorFormat colorFormat;
    BOOLEAN isCaptureByGamesAllowed;
};

#endif
