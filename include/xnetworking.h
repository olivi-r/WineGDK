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

#ifndef __WINE_XNETWORKING_H
#define __WINE_XNETWORKING_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DECLARE_ENUM_CLASS
#ifdef __cplusplus
#define _DECLARE_ENUM_CLASS(e,t) enum class e : t {
#define END_DECLARE_ENUM_CLASS };
#define _ENUM_CLASS_MEMBER(e,t,m,v) m,
#else
#define _DECLARE_ENUM_CLASS(e,t) typedef t e;
#define END_DECLARE_ENUM_CLASS
#define _ENUM_CLASS_MEMBER(e,t,m,v) static const t e##_##m = v;
#endif
#define DECLARE_ENUM_CLASS(e) _DECLARE_ENUM_CLASS(e,UINT32)
#define ENUM_CLASS_MEMBER(e,m,v) _ENUM_CLASS_MEMBER(e,UINT32,m,v)
#endif

DECLARE_ENUM_CLASS( XNetworkingConfigurationSetting )
    ENUM_CLASS_MEMBER( XNetworkingConfigurationSetting, MaxTitleTcpQueuedReceiveBufferSize,  0 )
    ENUM_CLASS_MEMBER( XNetworkingConfigurationSetting, MaxSystemTcpQueuedReceiveBufferSize, 1 )
    ENUM_CLASS_MEMBER( XNetworkingConfigurationSetting, MaxToolsTcpQueuedReceiveBufferSize,  2 )
END_DECLARE_ENUM_CLASS

DECLARE_ENUM_CLASS( XNetworkingConnectivityCostHint )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityCostHint, Unknown,      0 )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityCostHint, Unrestricted, 1 )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityCostHint, Fixed,        2 )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityCostHint, Varialbe,     3 )
END_DECLARE_ENUM_CLASS

DECLARE_ENUM_CLASS( XNetworkingConnectivityLevelHint )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityLevelHint, Unknown,                   0 )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityLevelHint, None,                      1 )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityLevelHint, LocalAccess,               2 )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityLevelHint, InternetAccess,            3 )
    ENUM_CLASS_MEMBER( XNetworkingConnectivityLevelHint, ConstrainedInternetAccess, 4 )
END_DECLARE_ENUM_CLASS

DECLARE_ENUM_CLASS( XNetworkingStatisticsType )
    ENUM_CLASS_MEMBER( XNetworkingStatisticsType, TitleTcpQueuedReceivedBufferUsage,  0 )
    ENUM_CLASS_MEMBER( XNetworkingStatisticsType, SystemTcpQueuedReceivedBufferUsage, 1 )
    ENUM_CLASS_MEMBER( XNetworkingStatisticsType, ToolsTcpQueuedReceivedBufferUsage,  2 )
END_DECLARE_ENUM_CLASS

DECLARE_ENUM_CLASS( XNetworkingThumbprintType )
    ENUM_CLASS_MEMBER( XNetworkingThumbprintType, Leaf,   0 )
    ENUM_CLASS_MEMBER( XNetworkingThumbprintType, Issuer, 1 )
    ENUM_CLASS_MEMBER( XNetworkingThumbprintType, Root,   2 )
END_DECLARE_ENUM_CLASS

typedef struct XNetworkingConnectivityHint XNetworkingConnectivityHint;
typedef struct XNetworkingSecurityInformation XNetworkingSecurityInformation;
typedef struct XNetworkingTcpQueuedReceivedBufferUsageStatistics XNetworkingTcpQueuedReceivedBufferUsageStatistics;
typedef struct XNetworkingThumbprint XNetworkingThumbprint;

typedef union XNetworkingStatisticsBuffer XNetworkingStatisticsBuffer;

typedef void __stdcall XNetworkingConnectivityHintChangedCallback( void *context, const XNetworkingConnectivityHint *connectivityHint );
typedef void __stdcall XNetworkingPreferredLocalUdpMultiplayerPortChangedCallback( void *context, UINT64 preferredLocalUdpMultiplayerPort );

struct XNetworkingConnectivityHint
{
    XNetworkingConnectivityLevelHint connectivityLevel;
    XNetworkingConnectivityCostHint connectivityCost;
    UINT32 ianaInterfaceType;
    BOOLEAN networkInitialized;
    BOOLEAN approachingDataLimit;
    BOOLEAN overDataLimit;
    BOOLEAN roaming;
};

struct XNetworkingSecurityInformation
{
    UINT32 enabledHttpSecurityProtocolFlags;
    SIZE_T thumbprintCount;
    XNetworkingThumbprint *thumbprints;
};

struct XNetworkingTcpQueuedReceivedBufferUsageStatistics
{
    UINT64 numBytesCurrentlyQueued;
    UINT64 peakNumBytesEverQueued;
    UINT64 totalNumBytesQueued;
    UINT64 numBytesDroppedForExceedingConfiguredMax;
    UINT64 numBytesDroppedDueToAnyFailure;
};

struct XNetworkingThumbprint
{
    XNetworkingThumbprintType thumbprintType;
    SIZE_T thumbprintBufferByteCount;
    UINT8 *thumbprintBuffer;
};

union XNetworkingStatisticsBuffer
{
    XNetworkingTcpQueuedReceivedBufferUsageStatistics tcpQueuedReceiveBufferUsage;
};

#ifdef __cplusplus
}
#endif

#endif
