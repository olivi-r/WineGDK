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

#ifndef __WINE_XGAMESAVE_H
#define __WINE_XGAMESAVE_H

typedef struct XGameSaveContainer *XGameSaveContainerHandle;
typedef struct XGameSaveProvider *XGameSaveProviderHandle;
typedef struct XGameSaveUpdate *XGameSaveUpdateHandle;

typedef struct XGameSaveBlob XGameSaveBlob;
typedef struct XGameSaveBlobInfo XGameSaveBlobInfo;
typedef struct XGameSaveContainerInfo XGameSaveContainerInfo;

typedef BOOLEAN __stdcall XGameSaveBlobInfoCallback( const XGameSaveBlobInfo *info, void *context );
typedef BOOLEAN __stdcall XGameSaveContainerInfoCallback( const XGameSaveContainerInfo *info, void *context );

struct XGameSaveBlobInfo
{
    const char *name;
    UINT32 size;
};

struct XGameSaveBlob
{
    XGameSaveBlobInfo info;
    UINT8 *data;
};

struct XGameSaveContainerInfo
{
    const char *name;
    const char *displayName;
    UINT32 blobCount;
    UINT64 totalSize;
    time_t lastModifiedTime;
    BOOLEAN needsSync;
};

#endif
