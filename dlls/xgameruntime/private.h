/*
 * Xbox Game runtime Library
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

#ifndef __WINE_XGAMERUNTIME_PRIVATE_H
#define __WINE_XGAMERUNTIME_PRIVATE_H

#define COBJMACROS

#include <roapi.h>
#include <stdlib.h>
#include <windows.h>
#include <wine/debug.h>
#include <winstring.h>
#include <xgameerr.h>
#include <xgameruntimeinit.h>

#include "provider.h"

#define WIDL_using_Windows_Foundation
#define WIDL_using_Windows_Foundation_Collections
#include <windows.foundation.h>
#define WIDL_using_Windows_Globalization
#include <windows.globalization.h>
#define WIDL_using_Windows_System_Profile
#include <windows.system.profile.h>

/* April 2026 Release of GDK */
#define GDKC_VERSION 10002L
#define GAMING_SERVICES_VERSION 7822L

extern IXAccessibility *x_accessibility_impl;
extern IXAppCapture *capture_impl;
extern IXAppCapture2 *capture2_impl;
extern IXDisplay *x_display_impl;
extern IErrorImpl1 *x_error_impl;
extern IXGame *x_game_impl;
extern IGameActivationImpl1 *x_game_activation_impl;
extern IXGameEvent *x_game_event_impl;
extern IXGameInvite *x_game_invite_impl;
extern IGameProtocolImpl1 *x_game_protocol_impl;
extern IXGameRuntimeFeature *x_game_runtime_feature_impl;
extern IXGameSave *x_game_save_impl;
extern IXLauncher *x_launcher_impl;
extern IXPackage *x_package_impl;
extern IXPersistentLocalStorage *x_persistent_local_storage_impl;
extern IStoreImpl6 *x_store_impl;
extern IXSystem *x_system_impl;
extern IXSystemAnalytics *analytics_impl;

/* Deference is for other modules to communicate with eachother through the same binary. */
HRESULT WINAPI QueryApiImpl( const GUID *runtimeClassId, REFIID interfaceId, void **out );

HRESULT WINAPI GDKC_InitAPI( ULONG gdkVer, ULONG gsVer, char mode, const XGameRuntimeOptions *options );

#endif
