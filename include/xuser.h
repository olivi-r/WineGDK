/*
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

typedef struct XUser *XUserHandle;
typedef struct XUserPlatformOperationToken *XUserPlatformOperation;
typedef struct XUserSignOutDeferral *XUserSignOutDeferralHandle;

#ifdef __cplusplus
#define DECLARE_ENUM_CLASS(e) enum class e : uint32_t
#define ENUM_CLASS_MEMBER(e,m) m
#else
#define DECLARE_ENUM_CLASS(e) typedef enum e e; enum e
#define ENUM_CLASS_MEMBER(e,m) e##_##m
#endif

DECLARE_ENUM_CLASS(XUserAddOptions)
{
    ENUM_CLASS_MEMBER(XUserAddOptions, None)                        = 0,
    ENUM_CLASS_MEMBER(XUserAddOptions, AddDefaultUserSilently)      = 1,
    ENUM_CLASS_MEMBER(XUserAddOptions, AllowGuests)                 = 2,
    ENUM_CLASS_MEMBER(XUserAddOptions, AddDefaultUserAllowingUI)    = 4,
};

DECLARE_ENUM_CLASS(XUserAgeGroup)
{
    ENUM_CLASS_MEMBER(XUserAgeGroup, Unknown)   = 0,
    ENUM_CLASS_MEMBER(XUserAgeGroup, Child)     = 1,
    ENUM_CLASS_MEMBER(XUserAgeGroup, Teen)      = 2,
    ENUM_CLASS_MEMBER(XUserAgeGroup, Adult)     = 3,
};

DECLARE_ENUM_CLASS(XUserChangeEvent)
{
    ENUM_CLASS_MEMBER(XUserChangeEvent, SignedInAgain)  = 0,
    ENUM_CLASS_MEMBER(XUserChangeEvent, SigningOut)     = 1,
    ENUM_CLASS_MEMBER(XUserChangeEvent, SignedOut)      = 2,
    ENUM_CLASS_MEMBER(XUserChangeEvent, Gamertag)       = 3,
    ENUM_CLASS_MEMBER(XUserChangeEvent, GamerPicture)   = 4,
    ENUM_CLASS_MEMBER(XUserChangeEvent, Privileges)     = 5,
};

DECLARE_ENUM_CLASS(XUserDefaultAudioEndpointKind)
{
    ENUM_CLASS_MEMBER(XUserDefaultAudioEndpointKind, CommunicationRender)   = 0,
    ENUM_CLASS_MEMBER(XUserDefaultAudioEndpointKind, CommunicationCapture)  = 1,
};

DECLARE_ENUM_CLASS(XUserGamerPictureSize)
{
    ENUM_CLASS_MEMBER(XUserGamerPictureSize, Small)         = 0,
    ENUM_CLASS_MEMBER(XUserGamerPictureSize, Medium)        = 1,
    ENUM_CLASS_MEMBER(XUserGamerPictureSize, Large)         = 2,
    ENUM_CLASS_MEMBER(XUserGamerPictureSize, ExtraLarge)    = 3,
};

DECLARE_ENUM_CLASS(XUserGamertagComponent)
{
    ENUM_CLASS_MEMBER(XUserGamertagComponent, Classic)      = 0,
    ENUM_CLASS_MEMBER(XUserGamertagComponent, Modern)       = 1,
    ENUM_CLASS_MEMBER(XUserGamertagComponent, ModernSuffix) = 2,
    ENUM_CLASS_MEMBER(XUserGamertagComponent, UniqueModern) = 3,
};

DECLARE_ENUM_CLASS(XUserGetMsaTokenSilentlyOptions)
{
    ENUM_CLASS_MEMBER(XUserGetMsaTokenSilentlyOptions, None)    = 0,
};

DECLARE_ENUM_CLASS(XUserGetTokenAndSignatureOptions)
{
    ENUM_CLASS_MEMBER(XUserGetTokenAndSignatureOptions, None)           = 0,
    ENUM_CLASS_MEMBER(XUserGetTokenAndSignatureOptions, ForceRefresh)   = 1,
    ENUM_CLASS_MEMBER(XUserGetTokenAndSignatureOptions, AllUsers)       = 2,
};

DECLARE_ENUM_CLASS(XUserPlatformOperationResult)
{
    ENUM_CLASS_MEMBER(XUserPlatformOperationResult, Success)    = 0,
    ENUM_CLASS_MEMBER(XUserPlatformOperationResult, Failure)    = 1,
    ENUM_CLASS_MEMBER(XUserPlatformOperationResult, Canceled)   = 2,
};

DECLARE_ENUM_CLASS(XUserPlatformSpopOperationResult)
{
    ENUM_CLASS_MEMBER(XUserPlatformSpopOperationResult, SignInHere)     = 0,
    ENUM_CLASS_MEMBER(XUserPlatformSpopOperationResult, SwitchAccount)  = 1,
    ENUM_CLASS_MEMBER(XUserPlatformSpopOperationResult, Failure)        = 2,
    ENUM_CLASS_MEMBER(XUserPlatformSpopOperationResult, Canceled)       = 3
};

DECLARE_ENUM_CLASS(XUserPrivilege)
{
    ENUM_CLASS_MEMBER(XUserPrivilege, CrossPlay)            = 185,
    ENUM_CLASS_MEMBER(XUserPrivilege, Clubs)                = 188,
    ENUM_CLASS_MEMBER(XUserPrivilege, Sessions)             = 189,
    ENUM_CLASS_MEMBER(XUserPrivilege, Broadcast)            = 190,
    ENUM_CLASS_MEMBER(XUserPrivilege, ManageProfilePrivacy) = 196,
    ENUM_CLASS_MEMBER(XUserPrivilege, GameDvr)              = 198,
    ENUM_CLASS_MEMBER(XUserPrivilege, MultiplayerParties)   = 203,
    ENUM_CLASS_MEMBER(XUserPrivilege, CloudManageSession)   = 207,
    ENUM_CLASS_MEMBER(XUserPrivilege, CloudJoinSession)     = 208,
    ENUM_CLASS_MEMBER(XUserPrivilege, CloudSavedGames)      = 209,
    ENUM_CLASS_MEMBER(XUserPrivilege, SocialNetworkSharing) = 220,
    ENUM_CLASS_MEMBER(XUserPrivilege, UserGeneratedContent) = 247,
    ENUM_CLASS_MEMBER(XUserPrivilege, Communications)       = 252,
    ENUM_CLASS_MEMBER(XUserPrivilege, Multiplayer)          = 254,
    ENUM_CLASS_MEMBER(XUserPrivilege, AddFriends)           = 255,
};

DECLARE_ENUM_CLASS(XUserPrivilegeDenyReason)
{
    ENUM_CLASS_MEMBER(XUserPrivilegeDenyReason, None)               = 0,
    ENUM_CLASS_MEMBER(XUserPrivilegeDenyReason, PurchaseRequired)   = 1,
    ENUM_CLASS_MEMBER(XUserPrivilegeDenyReason, Restricted)         = 2,
    ENUM_CLASS_MEMBER(XUserPrivilegeDenyReason, Banned)             = 3,
    ENUM_CLASS_MEMBER(XUserPrivilegeDenyReason, Unknown)            = -1,
};

DECLARE_ENUM_CLASS(XUserPrivilegeOptions)
{
    ENUM_CLASS_MEMBER(XUserPrivilegeOptions, None)      = 0,
    ENUM_CLASS_MEMBER(XUserPrivilegeOptions, AllUsers)  = 1
};

DECLARE_ENUM_CLASS(XUserState)
{
    ENUM_CLASS_MEMBER(XUserState, SignedIn)     = 0,
    ENUM_CLASS_MEMBER(XUserState, SigningOut)   = 1,
    ENUM_CLASS_MEMBER(XUserState, SignedOut)    = 2,
};

typedef struct XUserDeviceAssociationChange XUserDeviceAssociationChange;
typedef struct XUserGetTokenAndSignatureData XUserGetTokenAndSignatureData;
typedef struct XUserGetTokenAndSignatureHttpHeader XUserGetTokenAndSignatureHttpHeader;
typedef struct XUserGetTokenAndSignatureUtf16Data XUserGetTokenAndSignatureUtf16Data;
typedef struct XUserGetTokenAndSignatureUtf16HttpHeader XUserGetTokenAndSignatureUtf16HttpHeader;
typedef struct XUserLocalId XUserLocalId;
typedef struct XUserPlatformRemoteConnectEventHandlers XUserPlatformRemoteConnectEventHandlers;

typedef void __stdcall XUserChangeEventCallback( void *context, XUserLocalId userLocalId, XUserChangeEvent event );
typedef void __stdcall XUserDefaultAudioEndpointUtf16ChangedCallback( void *context, XUserLocalId user, XUserDefaultAudioEndpointKind defaultAudioEndpointKind, const WCHAR *endpointIdUtf16 );
typedef void __stdcall XUserDeviceAssociationChangedCallback( void *context, const XUserDeviceAssociationChange *change );
typedef void __stdcall XUserFindControllerForUserUiCallback( void *context, XUserHandle user );
typedef void XUserPlatformRemoteConnectClosePromptEventHandler( void *context, UINT32 userIdentifier, XUserPlatformOperation operation );
typedef void XUserPlatformRemoteConnectShowPromptEventHandler( void *context, UINT32 userIdentifier, XUserPlatformOperation operation, const CHAR *url, const CHAR *code, SIZE_T qrCodeSize, const void *qrCode );
typedef void XUserPlatformSpopPromptEventHandler( void *context, UINT32 userIdentifier, XUserPlatformOperation operation, const CHAR *modernGamertag, const CHAR *modernGamertagSuffix );

struct XUserLocalId
{
    UINT64 value;
};

struct XUserDeviceAssociationChange
{
    APP_LOCAL_DEVICE_ID deviceId;
    XUserLocalId oldUser;
    XUserLocalId newUser;
};

struct XUserGetTokenAndSignatureData
{
    SIZE_T tokenSize;
    SIZE_T signatureSize;
    const CHAR *token;
    const CHAR *signature;
};

struct XUserGetTokenAndSignatureHttpHeader
{
    const CHAR *name;
    const CHAR *value;
};

struct XUserGetTokenAndSignatureUtf16Data
{
    SIZE_T tokenCount;
    SIZE_T signatureCount;
    const WCHAR *token;
    const WCHAR *signature;
};

struct XUserGetTokenAndSignatureUtf16HttpHeader
{
    const WCHAR *name;
    const WCHAR *value;
};

struct XUserPlatformRemoteConnectEventHandlers
{
    XUserPlatformRemoteConnectShowPromptEventHandler *show;
    XUserPlatformRemoteConnectClosePromptEventHandler *close;
    void *context;
};

#ifndef __WIDL__
const SIZE_T XUserAudioEndpointMaxUtf16Count            = 56;
const SIZE_T XUserGamertagComponentClassicMaxBytes      = 16;
const SIZE_T XUserGamertagComponentModernMaxBytes       = 97;
const SIZE_T XUserGamertagComponentModernSuffixMaxBytes = 15;
const SIZE_T XUserGamertagComponentUniqueModernMaxBytes = 101;
const APP_LOCAL_DEVICE_ID XUserNullDeviceId             = {};
const XUserLocalId XUserNullUserLocalId                 = {};
#endif
