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

#ifndef __WINE_XGAMERUNTIME_PRIVATE_H
#define __WINE_XGAMERUNTIME_PRIVATE_H

#define COBJMACROS

#include <stdlib.h>
#include <windows.h>
#include <wine/debug.h>
#include <xgameruntime.h>

extern IXAccessibility *x_accessibility_impl;
extern IXAppCapture *capture_impl;
extern IXAppCapture5 *capture5_impl;
extern IXDisplay *x_display_impl;
extern IXError *x_error_impl;
extern IXGame3 *x_game_impl;
extern IXGameActivation *x_game_activation_impl;
extern IXGameEvent *x_game_event_impl;
extern IXGameInvite2 *x_game_invite_impl;
extern IXGameProtocol *x_game_protocol_impl;
extern IXGameRuntimeFeature *x_game_runtime_feature_impl;
extern IXGameSave3 *x_game_save_impl;
extern IXGameStreaming3 *x_game_streaming_impl;
extern IXGameUi4 *x_game_ui_impl;
extern IXLauncher *x_launcher_impl;
extern IXPackage3 *x_package_impl;
extern IXPersistentLocalStorage3 *x_persistent_local_storage_impl;
extern IXThreading *x_threading_impl;
extern IXUser6 *x_user_impl;
extern IXUserDevice2 *x_user_device_impl;

/* Deference is for other modules to communicate with eachother through the same binary. */
HRESULT WINAPI QueryApiImpl( const GUID *classId, REFIID interfaceId, void **out );

HRESULT WINAPI GDKC_InitAPI( ULONG gdkVer, ULONG gsVer, char mode, const XGameRuntimeOptions *options );

#endif
