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

#ifndef __WINE_XASYNCPROVIDER_H
#define __WINE_XASYNCPROVIDER_H

#include <xasync.h>

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

DECLARE_ENUM_CLASS( XAsyncOp )
    ENUM_CLASS_MEMBER( XAsyncOp, Begin,     0 )
    ENUM_CLASS_MEMBER( XAsyncOp, DoWork,    1 )
    ENUM_CLASS_MEMBER( XAsyncOp, GetResult, 2 )
    ENUM_CLASS_MEMBER( XAsyncOp, Cancel,    3 )
    ENUM_CLASS_MEMBER( XAsyncOp, Cleanup,   4 )
END_DECLARE_ENUM_CLASS

typedef struct XAsyncProviderData XAsyncProviderData;

typedef HRESULT __stdcall XAsyncProviderCallback( XAsyncOp op, const XAsyncProviderData *data );

struct XAsyncProviderData
{
    XAsyncBlock *async;
    SIZE_T bufferSize;
    void *buffer;
    void *context;
};

#ifdef __cplusplus
}
#endif

#endif
