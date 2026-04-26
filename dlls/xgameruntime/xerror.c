/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XError
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

struct x_error
{
    IXError IXError_iface;
    LONG ref;
};

static inline struct x_error *impl_from_IXError( IXError *iface )
{
    return CONTAINING_RECORD( iface, struct x_error, IXError_iface );
}

static HRESULT WINAPI x_error_QueryInterface( IXError *iface, REFIID iid, void **out )
{
    struct x_error *impl = impl_from_IXError( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown ) ||
        IsEqualGUID( iid, &IID_IXError  ))
    {
        IXError_AddRef( *out = &impl->IXError_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_error_AddRef( IXError *iface )
{
    struct x_error *impl = impl_from_IXError( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_error_Release( IXError *iface )
{
    struct x_error *impl = impl_from_IXError( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI __PADDING__( IXError *iface )
{
    WARN( "iface %p padding function called! It's unknown what this function does.\n", iface );
    return E_NOTIMPL;
}

static void WINAPI x_error_XErrorSetCallback( IXError *iface, XErrorCallback *callback, void *context )
{
    FIXME( "iface %p, callback %p, context %p stub!\n", iface, callback, context );
}

static void WINAPI x_error_XErrorSetOptions( IXError *iface, XErrorOptions optionsDebuggerPresent, XErrorOptions optionsDebuggerNotPresent )
{
    FIXME( "iface %p, optionsDebuggerPresent %#x, optionsDebuggerNotPresent %#x stub!\n", iface, optionsDebuggerPresent, optionsDebuggerNotPresent );
}

static const struct IXErrorVtbl x_error_vtbl =
{
    x_error_QueryInterface,
    x_error_AddRef,
    x_error_Release,
    /* IXError methods */
    __PADDING__,
    x_error_XErrorSetCallback,
    x_error_XErrorSetOptions,
};

static struct x_error x_error =
{
    {&x_error_vtbl},
    0,
};

IXError *x_error_impl = &x_error.IXError_iface;
