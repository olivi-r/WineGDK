/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XGame
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

#include "private.h"

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

struct x_game
{
    IXGame IXGame_iface;
    LONG ref;
};

static inline struct x_game *impl_from_IXGame( IXGame *iface )
{
    return CONTAINING_RECORD( iface, struct x_game, IXGame_iface );
}

static HRESULT WINAPI x_game_QueryInterface( IXGame *iface, REFIID iid, void **out )
{
    struct x_game *impl = impl_from_IXGame( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IXGame   ))
    {
        IXGame_AddRef( *out = &impl->IXGame_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_game_AddRef( IXGame *iface )
{
    struct x_game *impl = impl_from_IXGame( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_game_Release( IXGame *iface )
{
    struct x_game *impl = impl_from_IXGame( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_game_XGameGetXboxTitleId( IXGame *iface, UINT32 *titleId )
{
    FIXME( "iface %p, titleId %p stub!\n", iface, titleId );
    return E_NOTIMPL;
}

static void WINAPI x_game_XLaunchNewGame( IXGame *iface, const char *exePath, const char *args, XUserHandle defaultUser )
{
    FIXME( "iface %p exePath %s, args %s, defaultUser %p stub!\n", iface, debugstr_a( exePath ), debugstr_a( args ), defaultUser );
}

static HRESULT WINAPI x_game_XLaunchRestartOnCrash( IXGame *iface, const char *args, UINT32 reserved )
{
    FIXME( "iface %p, args %s, reserved %u stub!\n", iface, debugstr_a( args ), reserved );
    return E_NOTIMPL;
}

static const struct IXGameVtbl x_game_vtbl =
{
    x_game_QueryInterface,
    x_game_AddRef,
    x_game_Release,
    /* IXGame methods */
    x_game_XGameGetXboxTitleId,
    x_game_XLaunchNewGame,
    x_game_XLaunchRestartOnCrash,
};

static struct x_game x_game =
{
    {&x_game_vtbl},
    0,
};

IXGame *x_game_impl = &x_game.IXGame_iface;
