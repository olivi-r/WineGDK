/*
 * Xbox Game runtime Library
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

#include <wtypes.h>
#include <xgameruntime.h>

HRESULT WINAPI XPersistentLocalStorageGetPath( SIZE_T pathSize, char *path, SIZE_T *pathUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XPersistentLocalStorageGetPathSize( SIZE_T *pathSize )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XPersistentLocalStorageGetSpaceInfo( XPersistentLocalStorageSpaceInfo *info )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XPersistentLocalStorageMountForPackage( const char *packageIdentifier, XPackageMountHandle *mountHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XPersistentLocalStoragePromptUserForSpaceAsync( UINT64 requestedBytes, XAsyncBlock *asyncBlock )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XPersistentLocalStoragePromptUserForSpaceResult( XAsyncBlock *asyncBlock )
{
    return E_NOTIMPL;
}
