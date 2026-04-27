/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XDisplay and XLauncher
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

struct x_launcher
{
    IXLauncher IXLauncher_iface;
    LONG ref;
};

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

static inline struct x_launcher *impl_from_IXLauncher( IXLauncher *iface )
{
    return CONTAINING_RECORD( iface, struct x_launcher, IXLauncher_iface );
}

static HRESULT WINAPI x_launcher_QueryInterface( IXLauncher *iface, REFIID iid, void **out )
{
    struct x_launcher *impl = impl_from_IXLauncher( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown   ) ||
        IsEqualGUID( iid, &IID_IXLauncher ))
    {
        IXLauncher_AddRef( *out = &impl->IXLauncher_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_launcher_AddRef( IXLauncher *iface )
{
    struct x_launcher *impl = impl_from_IXLauncher( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_launcher_Release( IXLauncher *iface )
{
    struct x_launcher *impl = impl_from_IXLauncher( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_launcher_XLaunchUri( IXLauncher *iface, XUserHandle user, const char *uri )
{
    TRACE( "iface %p, user %p uri %s.\n", iface, user, debugstr_a( uri ) );
    return (SIZE_T)ShellExecuteA( NULL, "open", uri, NULL, NULL, SW_SHOW ) > 32 ? S_OK : E_GAMEPACKAGE_NO_PACKAGE_IDENTIFIER;
}

static HRESULT WINAPI x_launcher_XDisplayAcquireTimeoutDeferral( IXLauncher *iface, XDisplayTimeoutDeferralHandle *handle )
{
    FIXME( "iface %p, handle %p stub!\n", iface, handle );
    return E_NOTIMPL;
}

static void WINAPI x_launcher_XDisplayCloseTimeoutDeferralHandle( IXLauncher *iface, XDisplayTimeoutDeferralHandle handle )
{
    FIXME( "iface %p, handle %p stub!\n", iface, handle );
}

static const struct IXLauncherVtbl x_launcher_vtbl =
{
    x_launcher_QueryInterface,
    x_launcher_AddRef,
    x_launcher_Release,
    /* IXLauncher methods */
    x_launcher_XLaunchUri,
    x_launcher_XDisplayAcquireTimeoutDeferral,
    x_launcher_XDisplayCloseTimeoutDeferralHandle,
};

static struct x_launcher x_launcher =
{
    {&x_launcher_vtbl},
    0,
};

IXLauncher *x_launcher_impl = &x_launcher.IXLauncher_iface;
