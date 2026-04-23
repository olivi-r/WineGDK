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

#ifndef __WINE_XTASKQUEUE_H
#define __WINE_XTASKQUEUE_H

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

DECLARE_ENUM_CLASS( XTaskQueueDispatchMode )
    ENUM_CLASS_MEMBER( XTaskQueueDispatchMode, Manual,               0 )
    ENUM_CLASS_MEMBER( XTaskQueueDispatchMode, ThreadPool,           1 )
    ENUM_CLASS_MEMBER( XTaskQueueDispatchMode, SerializedThreadPool, 2 )
    ENUM_CLASS_MEMBER( XTaskQueueDispatchMode, Immediate,            3 )
END_DECLARE_ENUM_CLASS

DECLARE_ENUM_CLASS( XTaskQueuePort )
    ENUM_CLASS_MEMBER( XTaskQueuePort, Work,       0 )
    ENUM_CLASS_MEMBER( XTaskQueuePort, Completion, 1 )
END_DECLARE_ENUM_CLASS

typedef struct XTaskQueueObject *XTaskQueueHandle;
typedef struct XTaskQueuePortObject *XTaskQueuePortHandle;

typedef struct XTaskQueueRegistrationToken XTaskQueueRegistrationToken;

typedef void __stdcall XTaskQueueCallback( void *context, BOOLEAN canceled );
typedef void __stdcall XTaskQueueMonitorCallback( void *context, XTaskQueueHandle queue, XTaskQueuePort port );
typedef void __stdcall XTaskQueueTerminatedCallback( void *context );

struct XTaskQueueRegistrationToken
{
    UINT64 token;
};

#ifdef __cplusplus
}
#endif

#endif
