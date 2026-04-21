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

#ifndef __WINE_XGAMERUNTIMEFEATURE_H
#define __WINE_XGAMERUNTIMEFEATURE_H

typedef enum XGameRuntimeFeature XGameRuntimeFeature;

enum XGameRuntimeFeature
{
    XGameRuntimeFeature_XAccessibility,
    XGameRuntimeFeature_XAppCapture,
    XGameRuntimeFeature_XAsync,
    XGameRuntimeFeature_XAsyncProvider,
    XGameRuntimeFeature_XDisplay,
    XGameRuntimeFeature_XGame,
    XGameRuntimeFeature_XGameInvite,
    XGameRuntimeFeature_XGameSave,
    XGameRuntimeFeature_XGameUI,
    XGameRuntimeFeature_XLauncher,
    XGameRuntimeFeature_XNetworking,
    XGameRuntimeFeature_XPackage,
    XGameRuntimeFeature_XPersistentLocalStorage,
    XGameRuntimeFeature_XSpeechSynthesizer,
    XGameRuntimeFeature_XStore,
    XGameRuntimeFeature_XSystem,
    XGameRuntimeFeature_XTaskQueue,
    XGameRuntimeFeature_XThread,
    XGameRuntimeFeature_XUser,
    XGameRuntimeFeature_XError,
    XGameRuntimeFeature_XGameEvent,
    XGameRuntimeFeature_XGameStreaming,
};

#endif
