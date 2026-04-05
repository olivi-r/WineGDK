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

typedef enum XNetworkingConfigurationSetting XNetworkingConfigurationSetting;
typedef enum XNetworkingConnectivityCostHint XNetworkingConnectivityCostHint;
typedef enum XNetworkingConnectivityLevelHint XNetworkingConnectivityLevelHint;
typedef enum XNetworkingStatisticsType XNetworkingStatisticsType;
typedef enum XNetworkingThumbprintType XNetworkingThumbprintType;

typedef struct XNetworkingConnectivityHint XNetworkingConnectivityHint;
typedef struct XNetworkingSecurityInformation XNetworkingSecurityInformation;
typedef struct XNetworkingTcpQueuedReceivedBufferUsageStatistics XNetworkingTcpQueuedReceivedBufferUsageStatistics;
typedef struct XNetworkingThumbprint XNetworkingThumbprint;
typedef union XNetworkingStatisticsBuffer XNetworkingStatisticsBuffer;

typedef void XNetworkingConnectivityHintChangedCallback( void *context, const XNetworkingConnectivityHint *connectivityHint );
typedef void XNetworkingPreferredLocalUdpMultiplayerPortChangedCallback( void *context, UINT64 preferredLocalUdpMultiplayerPort );

enum XNetworkingConfigurationSetting
{
    XNetworkingConfigurationSetting_MaxTitleTcpQueuedReceiveBufferSize,
    XNetworkingConfigurationSetting_MaxSystemTcpQueuedReceiveBufferSize,
    XNetworkingConfigurationSetting_MaxToolsTcpQueuedReceiveBufferSize,
};

enum XNetworkingConnectivityCostHint
{
    XNetworkingConnectivityCostHint_Unknown,
    XNetworkingConnectivityCostHint_Unrestricted,
    XNetworkingConnectivityCostHint_Fixed,
    XNetworkingConnectivityCostHint_Varialbe,
};

enum XNetworkingConnectivityLevelHint
{
    XNetworkingConnectivityLevelHint_Unknown,
    XNetworkingConnectivityLevelHint_None,
    XNetworkingConnectivityLevelHint_LocalAccess,
    XNetworkingConnectivityLevelHint_InternetAccess,
    XNetworkingConnectivityLevelHint_ConstrainedInternetAccess,
};

enum XNetworkingStatisticsType
{
    XNetworkingStatisticsType_TitleTcpQueuedReceivedBufferUsage,
    XNetworkingStatisticsType_SystemTcpQueuedReceivedBufferUsage,
    XNetworkingStatisticsType_ToolsTcpQueuedReceivedBufferUsage,
};

enum XNetworkingThumbprintType
{
    XNetworkingThumbprintType_Leaf,
    XNetworkingThumbprintType_Issuer,
    XNetworkingThumbprintType_Root,
};

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

#endif
