/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XGameSave and XGameSaveFiles
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

struct x_game_save
{
    IXGameSave IXGameSave_iface;
    LONG ref;
};

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

static inline struct x_game_save *impl_from_IXGameSave( IXGameSave *iface )
{
    return CONTAINING_RECORD( iface, struct x_game_save, IXGameSave_iface );
}

static HRESULT WINAPI x_game_save_QueryInterface( IXGameSave *iface, REFIID iid, void **out )
{
    struct x_game_save *impl = impl_from_IXGameSave( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown        ) ||
        IsEqualGUID( iid, &IID_IXGameSave ))
    {
        IXGameSave_AddRef( *out = &impl->IXGameSave_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_game_save_AddRef( IXGameSave *iface )
{
    struct x_game_save *impl = impl_from_IXGameSave( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_game_save_Release( IXGameSave *iface )
{
    struct x_game_save *impl = impl_from_IXGameSave( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_game_save_XGameSaveInitializeProvider( IXGameSave *iface, XUserHandle requestingUser, const char *configurationId, BOOLEAN syncOnDemand, XGameSaveProviderHandle *provider )
{
    FIXME( "iface %p, requestingUser %p, configurationId %s, syncOnDemand %d, provider %p stub!\n", iface, requestingUser, debugstr_a( configurationId ), syncOnDemand, provider );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveInitializeProviderAsync( IXGameSave *iface, XUserHandle requestingUser, const char *configurationId, BOOLEAN syncOnDemand, XAsyncBlock *async )
{
    FIXME( "iface %p, requestingUser %p, configurationId %s, syncOnDemand %d, async %p stub!\n", iface, requestingUser, debugstr_a( configurationId ), syncOnDemand, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveInitializeProviderResult( IXGameSave *iface, XAsyncBlock *async, XGameSaveProviderHandle *provider )
{
    FIXME( "iface %p, async %p, provider %p stub!\n", iface, async, provider );
    return E_NOTIMPL;
}

static void WINAPI x_game_save_XGameSaveCloseProvider( IXGameSave *iface, XGameSaveProviderHandle provider )
{
    FIXME( "iface %p, provider %p stub!\n", iface, provider );
}

static HRESULT WINAPI x_game_save_XGameSaveGetRemainingQuota( IXGameSave *iface, XGameSaveProviderHandle provider, INT64 *remainingQuota )
{
    FIXME( "iface %p, provider %p, remainingQuota %p stub!\n", iface, provider, remainingQuota );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveGetRemainingQuotaAsync( IXGameSave *iface, XGameSaveProviderHandle provider, XAsyncBlock *async )
{
    FIXME( "iface %p, provider %p, async %p stub!\n", iface, provider, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveGetRemainingQuotaResult( IXGameSave *iface, XAsyncBlock *async, INT64 *remainingQuota )
{
    FIXME( "iface %p, async %p, remainingQuota %p stub!\n", iface, async, remainingQuota );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveDeleteContainer( IXGameSave *iface, XGameSaveProviderHandle provider, const char *containerName )
{
    FIXME( "iface %p, provider %p, containerName %s stub!\n", iface, provider, debugstr_a( containerName ) );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveDeleteContainerAsync( IXGameSave *iface, XGameSaveProviderHandle provider, const char *containerName, XAsyncBlock *async )
{
    FIXME( "iface %p, provider %p, containerName %s, async %p stub!\n", iface, provider, debugstr_a( containerName ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveDeleteContainerResult( IXGameSave *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveGetContainerInfo( IXGameSave *iface, XGameSaveProviderHandle provider, const char *containerName, void *context, XGameSaveContainerInfoCallback *callback )
{
    FIXME( "iface %p, provider %p, containerName %s, context %p, callback %p stub!\n", iface, provider, debugstr_a( containerName ), context, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveEnumerateContainerInfo( IXGameSave *iface, XGameSaveProviderHandle provider, void *context, XGameSaveContainerInfoCallback *callback )
{
    FIXME( "iface %p, provider %p, context %p, callback %p stub!\n", iface, provider, context, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveEnumerateContainerInfoByName( IXGameSave *iface, XGameSaveProviderHandle provider, const char *containerNamePrefix, void *context, XGameSaveContainerInfoCallback *callback )
{
    FIXME( "iface %p, provider %p, containerNamePrefix %s, context %p, callback %p stub!\n", iface, provider, debugstr_a( containerNamePrefix ), context, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveCreateContainer( IXGameSave *iface, XGameSaveProviderHandle provider, const char *containerName, XGameSaveContainerHandle *containerContext )
{
    FIXME( "iface %p, provider %p, containerName %s, containerContext %p stub!\n", iface, provider, debugstr_a( containerName ), containerContext );
    return E_NOTIMPL;
}

static void WINAPI x_game_save_XGameSaveCloseContainer( IXGameSave *iface, XGameSaveContainerHandle context )
{
    FIXME( "iface %p, context %p stub!\n", iface, context );
}

static HRESULT WINAPI x_game_save_XGameSaveEnumerateBlobInfo( IXGameSave *iface, XGameSaveContainerHandle container, void *context, XGameSaveBlobInfoCallback *callback )
{
    FIXME( "iface %p, container %p, context %p, callback %p stub!\n", iface, container, context, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveEnumerateBlobInfoByName( IXGameSave *iface, XGameSaveContainerHandle container, const char *blobNamePrefix, void *context, XGameSaveBlobInfoCallback *callback )
{
    FIXME( "iface %p, container %p, blobNamePrefix %s, context %p, callback %p stub!\n", iface, container, debugstr_a( blobNamePrefix ), context, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveReadBlobData( IXGameSave *iface, XGameSaveContainerHandle container, const char **blobNames, UINT32 *countOfBlobs, SIZE_T blobsSize, XGameSaveBlob *blobData )
{
    FIXME( "iface %p, container %p, blobNames %p, countOfBlobs %p, blobsSize %Iu, provider %p stub!\n", iface, container, blobNames, countOfBlobs, blobsSize, blobData );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveReadBlobDataAsync( IXGameSave *iface, XGameSaveContainerHandle container, const char **blobNames, UINT32 countOfBlobs, XAsyncBlock *async )
{
    FIXME( "iface %p, container %p, blobNames %p, countOfBlobs %u, async %p stub!\n", iface, container, blobNames, countOfBlobs, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveReadBlobDataResult( IXGameSave *iface, XAsyncBlock *async, SIZE_T blobsSize, XGameSaveBlob *blobData, UINT32 *countOfBlobs )
{
    FIXME( "iface %p, async %p, blobsSize %Iu, blobData %p, countOfBlobs %p stub!\n", iface, async, blobsSize, blobData, countOfBlobs );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveCreateUpdate( IXGameSave *iface, XGameSaveContainerHandle container, const char *containerDisplayName, XGameSaveUpdateHandle *updateContext )
{
    FIXME( "iface %p, container %p, containerDisplayName %s, updateContext %p stub!\n", iface, container, debugstr_a( containerDisplayName ), updateContext );
    return E_NOTIMPL;
}

static void WINAPI x_game_save_XGameSaveCloseUpdate( IXGameSave *iface, XGameSaveUpdateHandle context )
{
    FIXME( "iface %p, context %p stub!\n", iface, context );
}

static HRESULT WINAPI x_game_save_XGameSaveSubmitBlobWrite( IXGameSave *iface, XGameSaveUpdateHandle updateContext, const char *blobName, UINT8 *data, SIZE_T byteCount )
{
    FIXME( "iface %p, updateContext %p, blobName %s, data %p, byteCount %Iu stub!\n", iface, updateContext, debugstr_a( blobName ), data, byteCount );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveSubmitBlobDelete( IXGameSave *iface, XGameSaveUpdateHandle updateContext, const char *blobName )
{
    FIXME( "iface %p, updateContext %p, blobName %s stub!\n", iface, updateContext, debugstr_a( blobName ) );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveSubmitUpdate( IXGameSave *iface, XGameSaveUpdateHandle updateContext )
{
    FIXME( "iface %p, updateContext %p stub!\n", iface, updateContext );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveSubmitUpdateAsync( IXGameSave *iface, XGameSaveUpdateHandle updateContext, XAsyncBlock *async )
{
    FIXME( "iface %p, updateContext %p, async %p stub!\n", iface, updateContext, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveSubmitUpdateResult( IXGameSave *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveFilesGetFolderWithUiAsync( IXGameSave *iface, XUserHandle requestingUser, const char *configurationId, XAsyncBlock *async )
{
    FIXME( "iface %p, requestingUser %p, configurationId %s, async %p stub!\n", iface, requestingUser, debugstr_a( configurationId ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveFilesGetFolderWithUiResult( IXGameSave *iface, XAsyncBlock *async, SIZE_T folderSize, char *folderResult )
{
    FIXME( "iface %p, async %p, folderSize %Iu, folderResult %p stub!\n", iface, async, folderSize, folderResult );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_game_save_XGameSaveFilesGetRemainingQuota( IXGameSave *iface, XUserHandle userContext, const char *configurationId, INT64 *remainingQuota )
{
    FIXME( "iface %p, userContext %p, configurationId %s, remainingQuota %p stub!\n", iface, userContext, debugstr_a( configurationId ), remainingQuota );
    return E_NOTIMPL;
}

static const struct IXGameSaveVtbl x_game_save_vtbl =
{
    x_game_save_QueryInterface,
    x_game_save_AddRef,
    x_game_save_Release,
    /* IXGameSave methods */
    x_game_save_XGameSaveInitializeProvider,
    x_game_save_XGameSaveInitializeProviderAsync,
    x_game_save_XGameSaveInitializeProviderResult,
    x_game_save_XGameSaveCloseProvider,
    x_game_save_XGameSaveGetRemainingQuota,
    x_game_save_XGameSaveGetRemainingQuotaAsync,
    x_game_save_XGameSaveGetRemainingQuotaResult,
    x_game_save_XGameSaveDeleteContainer,
    x_game_save_XGameSaveDeleteContainerAsync,
    x_game_save_XGameSaveDeleteContainerResult,
    x_game_save_XGameSaveGetContainerInfo,
    x_game_save_XGameSaveEnumerateContainerInfo,
    x_game_save_XGameSaveEnumerateContainerInfoByName,
    x_game_save_XGameSaveCreateContainer,
    x_game_save_XGameSaveCloseContainer,
    x_game_save_XGameSaveEnumerateBlobInfo,
    x_game_save_XGameSaveEnumerateBlobInfoByName,
    x_game_save_XGameSaveReadBlobData,
    x_game_save_XGameSaveReadBlobDataAsync,
    x_game_save_XGameSaveReadBlobDataResult,
    x_game_save_XGameSaveCreateUpdate,
    x_game_save_XGameSaveCloseUpdate,
    x_game_save_XGameSaveSubmitBlobWrite,
    x_game_save_XGameSaveSubmitBlobDelete,
    x_game_save_XGameSaveSubmitUpdate,
    x_game_save_XGameSaveSubmitUpdateAsync,
    x_game_save_XGameSaveSubmitUpdateResult,
    x_game_save_XGameSaveFilesGetFolderWithUiAsync,
    x_game_save_XGameSaveFilesGetFolderWithUiResult,
    x_game_save_XGameSaveFilesGetRemainingQuota,
};

static struct x_game_save x_game_save =
{
    {&x_game_save_vtbl},
    0,
};

IXGameSave *x_game_save_impl = &x_game_save.IXGameSave_iface;
