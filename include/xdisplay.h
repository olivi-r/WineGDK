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

#ifndef __WINE_XDISPLAY_H
#define __WINE_XDISPLAY_H

typedef enum XDisplayHdrModePreference XDisplayHdrModePreference;
typedef enum XDisplayHdrModeResult XDisplayHdrModeResult;

typedef struct XDisplayTimeoutDeferral *XDisplayTimeoutDeferralHandle;

typedef struct XDisplayHdrModeInfo XDisplayHdrModeInfo;

enum XDisplayHdrModePreference
{
    XDisplayHdrModePreference_PreferHdr,
    XDisplayHdrModePreference_PreferRefreshRate,
};

enum XDisplayHdrModeResult
{
    XDisplayHdrModeResult_Unknown,
    XDisplayHdrModeResult_Enabled,
    XDisplayHdrModeResult_Disabled,
};

struct XDisplayHdrModeInfo
{
    float minToneMapLuminance;
    float maxToneMapLuminance;
    float maxFullFrameToneMapLuminance;
};

#endif
