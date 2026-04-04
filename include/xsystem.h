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

#ifndef __WINE_XSYSTEM_H
#define __WINE_XSYSTEM_H

#include <xgameruntimetypes.h>

typedef void *XSystemHandle;

typedef enum XSystemDeviceType XSystemDeviceType;
typedef enum XSystemHandleCallbackReason XSystemHandleCallbackReason;
typedef enum XSystemHandleType XSystemHandleType;

typedef struct XSystemAnalyticsInfo XSystemAnalyticsInfo;
typedef struct XSystemRuntimeInfo XSystemRuntimeInfo;

typedef void __stdcall XSystemHandleCallback( XSystemHandle handle, XSystemHandleType type, XSystemHandleCallbackReason reason, void *context );

enum XSystemDeviceType
{
    XSystemDeviceType_Unknown,
    XSystemDeviceType_Pc,
    XSystemDeviceType_XboxOne,
    XSystemDeviceType_XboxOneS,
    XSystemDeviceType_XboxOneX,
    XSystemDeviceType_XboxOneXDevkit,
    XSystemDeviceType_XboxScarlettLockhart,
    XSystemDeviceType_XboxScarlettAnaconda,
    XSystemDeviceType_XboxScarlettDevkit,
};

enum XSystemHandleCallbackReason
{
    XSystemHandleCallbackReason_Created,
    XSystemHandleCallbackReason_Destroyed,
};

enum XSystemHandleType
{
    XSystemHandleType_AppCaptureScreenshotStream,
    XSystemHandleType_DisplayTimeoutDeferral,
    XSystemHandleType_GameSaveContainer,
    XSystemHandleType_GameSaveProvider,
    XSystemHandleType_GameSaveUpdate,
    XSystemHandleType_PackageInstallationMonitor,
    XSystemHandleType_PackageMount,
    XSystemHandleType_SpeechSynthesizer,
    XSystemHandleType_SpeechSynthesizerStream,
    XSystemHandleType_StoreContext,
    XSystemHandleType_StoreLicense,
    XSystemHandleType_StoreProductQuery,
    XSystemHandleType_TaskQueue,
    XSystemHandleType_User,
    XSystemHandleType_UserSignOutDeferral,
    XSystemHandleType_GameUiTextEntry,
};

struct XSystemAnalyticsInfo
{
    XVersion osVersion;
    XVersion hostingOsVersion;
    char family[64];
    char form[64];
};

struct XSystemRuntimeInfo
{
    XVersion runtimeVersion;
    XVersion availableVersion;
};

#endif
