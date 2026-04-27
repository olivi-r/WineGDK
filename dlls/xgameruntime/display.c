/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XDisplay
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

#include <shellapi.h>

struct x_display
{
    IXDisplay IXDisplay_iface;
    LONG ref;
};

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

static inline struct x_display *impl_from_IXDisplay( IXDisplay *iface )
{
    return CONTAINING_RECORD( iface, struct x_display, IXDisplay_iface );
}

static HRESULT WINAPI x_display_QueryInterface( IXDisplay *iface, REFIID iid, void **out )
{
    struct x_display *impl = impl_from_IXDisplay( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown  ) ||
        IsEqualGUID( iid, &IID_IXDisplay ))
    {
        IXDisplay_AddRef( *out = &impl->IXDisplay_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_display_AddRef( IXDisplay *iface )
{
    struct x_display *impl = impl_from_IXDisplay( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_display_Release( IXDisplay *iface )
{
    struct x_display *impl = impl_from_IXDisplay( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI __PADDING__( IXDisplay *iface )
{
    FIXME( "padding function called\n" );
    return E_NOTIMPL;
}

static XDisplayHdrModeResult WINAPI x_display_XDisplayTryEnableHdrMode( IXDisplay *iface, XDisplayHdrModePreference displayModePreference, XDisplayHdrModeInfo *displayHdrModeInfo )
{
    FIXME( "iface %p, displayModePreference %d, displayHdrModeInfo %p stub!\n", iface, displayModePreference, displayHdrModeInfo );
    return XDisplayHdrModeResult_Unknown;
}

static const struct IXDisplayVtbl x_display_vtbl =
{
    x_display_QueryInterface,
    x_display_AddRef,
    x_display_Release,
    /* IXDisplay methods */
    __PADDING__,
    x_display_XDisplayTryEnableHdrMode,
};

static struct x_display x_display =
{
    {&x_display_vtbl},
    0,
};

IXDisplay *x_display_impl = &x_display.IXDisplay_iface;
