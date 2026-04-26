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

#ifndef __WINE_XPACKAGE_H
#define __WINE_XPACKAGE_H

#include <xgameruntimetypes.h>

typedef enum XPackageChunkAvailability XPackageChunkAvailability;
typedef enum XPackageChunkSelectorType XPackageChunkSelectorType;
typedef enum XPackageEnumerationScope XPackageEnumerationScope;
typedef enum XPackageKind XPackageKind;

typedef struct XPackageInstallationMonitor *XPackageInstallationMonitorHandle;
typedef struct XPackageMountInstance *XPackageMountHandle;

typedef struct XPackageChunkSelector XPackageChunkSelector;
typedef struct XPackageDetails XPackageDetails;
typedef struct XPackageFeature XPackageFeature;
typedef struct XPackageInstallationProgress XPackageInstallationProgress;
typedef struct XPackageWriteStats XPackageWriteStats;

typedef BOOLEAN __stdcall XPackageChunkAvailabilityCallback( void *context, const XPackageChunkSelector *selector, XPackageChunkAvailability availability );
typedef BOOLEAN __stdcall XPackageEnumerationCallback( void *context, const XPackageDetails *details );
typedef BOOLEAN __stdcall XPackageFeatureEnumerationCallback( void *context, const XPackageFeature *details );
typedef void    __stdcall XPackageInstallationProgressCallback( void *context, XPackageInstallationMonitorHandle monitor );
typedef void    __stdcall XPackageInstalledCallback( void *context, const XPackageDetails *details );

enum XPackageChunkAvailability
{
    XPackageChunkAvailability_Ready,
    XPackageChunkAvailability_Pending,
    XPackageChunkAvailability_Installable,
    XPackageChunkAvailability_Unavailable,
};

enum XPackageChunkSelectorType
{
    XPackageChunkSelectorType_Language,
    XPackageChunkSelectorType_Tag,
    XPackageChunkSelectorType_Chunk,
    XPackageChunkSelectorType_Feature,
};

enum XPackageEnumerationScope
{
    XPackageEnumerationScope_ThisOnly,
    XPackageEnumerationScope_ThisAndRelated,
    XPackageEnumerationScope_ThisPublisher,
};

enum XPackageKind
{
    XPackageKind_Game,
    XPackageKind_Content,
};

struct XPackageChunkSelector
{
    XPackageChunkSelectorType type;
    union
    {
        const char *language;
        const char *tag;
        const char *feature;
        UINT32 chunkId;
    };
};

struct XPackageDetails
{
    const char *packageIdentifier;
    XVersion version;
    XPackageKind kind;
    const char *displayName;
    const char *description;
    const char *publisher;
    const char *storeId;
    BOOLEAN installing;
    UINT32 index;
    UINT32 count;
    BOOLEAN ageRestricted;
    const char *titleID;
};

struct XPackageFeature
{
    const char *id;
    const char *displayName;
    const char *tags;
    BOOLEAN hidden;
    UINT32 storeIdCount;
    const char **storeIds;
};

struct XPackageInstallationProgress
{
    UINT64 totalBytes;
    UINT64 installedBytes;
    UINT64 launchBytes;
    BOOLEAN launchable;
    BOOLEAN completed;
};

struct XPackageWriteStats
{
    UINT64 interval;
    UINT64 budget;
    UINT64 elapsed;
    UINT64 bytesWritten;
};

#endif
