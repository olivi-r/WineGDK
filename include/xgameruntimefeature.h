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

DECLARE_ENUM_CLASS( XGameRuntimeFeature )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XAccessibility,              0 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XAppCapture,                 1 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XAsync,                      2 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XAsyncProvider,              3 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XDisplay,                    4 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XGame,                       5 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XGameInvite,                 6 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XGameSave,                   7 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XGameUI,                     8 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XLauncher,                   9 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XNetworking,                10 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XPackage,                   11 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XPersistentLocalStorage,    12 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XSpeechSynthesizer,         13 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XStore,                     13 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XSystem,                    15 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XTaskQueue,                 16 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XThread,                    17 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XUser,                      18 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XError,                     19 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XGameEvent,                 20 )
    ENUM_CLASS_MEMBER( XGameRuntimeFeature, XGameStreaming,             21 )
END_DECLARE_ENUM_CLASS

#ifdef __cplusplus
}
#endif

#endif
