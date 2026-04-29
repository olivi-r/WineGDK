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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DECLARE_ENUM_CLASS
#ifdef __cplusplus
#define _DECLARE_ENUM_CLASS(e,t) enum class e : t {
#define END_DECLARE_ENUM_CLASS };
#define _ENUM_CLASS_MEMBER(e,t,m,v) m,
#else
#define _DECLARE_ENUM_CLASS(e,t) typedef t e;
#define END_DECLARE_ENUM_CLASS
#define _ENUM_CLASS_MEMBER(e,t,m,v) static const t e##_##m = v;
#endif
#define DECLARE_ENUM_CLASS(e) _DECLARE_ENUM_CLASS(e,UINT32)
#define ENUM_CLASS_MEMBER(e,m,v) _ENUM_CLASS_MEMBER(e,UINT32,m,v)
#endif

DECLARE_ENUM_CLASS( XSystemDeviceType )
    ENUM_CLASS_MEMBER( XSystemDeviceType, Unknown,              0 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, Pc,                   1 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, XboxOne,              2 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, XboxOneS,             3 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, XboxOneX,             4 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, XboxOneXDevkit,       5 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, XboxScarlettLockhart, 6 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, XboxScarlettAnaconda, 7 )
    ENUM_CLASS_MEMBER( XSystemDeviceType, XboxScarlettDevkit,   8 )
END_DECLARE_ENUM_CLASS

DECLARE_ENUM_CLASS( XSystemHandleCallbackReason )
    ENUM_CLASS_MEMBER( XSystemHandleCallbackReason, Created,   0 )
    ENUM_CLASS_MEMBER( XSystemHandleCallbackReason, Destroyed, 1 )
END_DECLARE_ENUM_CLASS

DECLARE_ENUM_CLASS( XSystemHandleType )
    ENUM_CLASS_MEMBER( XSystemHandleType, AppCaptureScreenshotStream,    0 )
    ENUM_CLASS_MEMBER( XSystemHandleType, DisplayTimeoutDeferral,        1 )
    ENUM_CLASS_MEMBER( XSystemHandleType, GameSaveContainer,             2 )
    ENUM_CLASS_MEMBER( XSystemHandleType, GameSaveProvider,              3 )
    ENUM_CLASS_MEMBER( XSystemHandleType, GameSaveUpdate,                4 )
    ENUM_CLASS_MEMBER( XSystemHandleType, PackageInstallationMonitor,    5 )
    ENUM_CLASS_MEMBER( XSystemHandleType, PackageMount,                  6 )
    ENUM_CLASS_MEMBER( XSystemHandleType, SpeechSynthesizer,             7 )
    ENUM_CLASS_MEMBER( XSystemHandleType, SpeechSynthesizerStream,       8 )
    ENUM_CLASS_MEMBER( XSystemHandleType, StoreContext,                  9 )
    ENUM_CLASS_MEMBER( XSystemHandleType, StoreLicense,                 10 )
    ENUM_CLASS_MEMBER( XSystemHandleType, StoreProductQuery,            11 )
    ENUM_CLASS_MEMBER( XSystemHandleType, TaskQueue,                    12 )
    ENUM_CLASS_MEMBER( XSystemHandleType, User,                         13 )
    ENUM_CLASS_MEMBER( XSystemHandleType, UserSignOutDeferral,          14 )
    ENUM_CLASS_MEMBER( XSystemHandleType, GameUiTextEntry,              15 )
END_DECLARE_ENUM_CLASS

typedef void *XSystemHandle;

typedef struct XSystemAnalyticsInfo XSystemAnalyticsInfo;
typedef struct XSystemRuntimeInfo XSystemRuntimeInfo;

typedef void __stdcall XSystemHandleCallback( XSystemHandle handle, XSystemHandleType type, XSystemHandleCallbackReason reason, void *context );

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

#ifdef __cplusplus
}
#endif

#endif
