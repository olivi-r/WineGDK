/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XGameRuntimeFeature
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

#include "private.h"

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

struct x_game_runtime_feature
{
    IXGameRuntimeFeature IXGameRuntimeFeature_iface;
    LONG ref;
};

static inline struct x_game_runtime_feature *impl_from_IXGameRuntimeFeature( IXGameRuntimeFeature *iface )
{
    return CONTAINING_RECORD( iface, struct x_game_runtime_feature, IXGameRuntimeFeature_iface );
}

static HRESULT WINAPI x_game_runtime_feature_QueryInterface( IXGameRuntimeFeature *iface, REFIID iid, void **out )
{
    struct x_game_runtime_feature *impl = impl_from_IXGameRuntimeFeature( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown             ) ||
        IsEqualGUID( iid, &IID_IXGameRuntimeFeature ))
    {
        IXGameRuntimeFeature_AddRef( *out = &impl->IXGameRuntimeFeature_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_game_runtime_feature_AddRef( IXGameRuntimeFeature *iface )
{
    struct x_game_runtime_feature *impl = impl_from_IXGameRuntimeFeature( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_game_runtime_feature_Release( IXGameRuntimeFeature *iface )
{
    struct x_game_runtime_feature *impl = impl_from_IXGameRuntimeFeature( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static BOOLEAN WINAPI x_game_runtime_feature_XGameRuntimeIsFeatureAvailable( IXGameRuntimeFeature *iface, XGameRuntimeFeature feature )
{
    /* Always assume the feature is available, regardless of what game it is, for compatibility reasons. */
    TRACE( "iface %p feature %d.\n", iface, feature );
    return TRUE;
}

static const struct IXGameRuntimeFeatureVtbl x_game_runtime_feature_vtbl =
{
    x_game_runtime_feature_QueryInterface,
    x_game_runtime_feature_AddRef,
    x_game_runtime_feature_Release,
    /* IXGameRuntimeFeature methods */
    x_game_runtime_feature_XGameRuntimeIsFeatureAvailable,
};

static struct x_game_runtime_feature x_game_runtime_feature =
{
    {&x_game_runtime_feature_vtbl},
    0,
};

IXGameRuntimeFeature *x_game_runtime_feature_impl = &x_game_runtime_feature.IXGameRuntimeFeature_iface;
