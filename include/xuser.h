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

#ifndef __WINE_XUSER_H
#define __WINE_XUSER_H

typedef enum XUserAddOptions XUserAddOptions;
typedef enum XUserAgeGroup XUserAgeGroup;
typedef enum XUserChangeEvent XUserChangeEvent;
typedef enum XUserDefaultAudioEndpointKind XUserDefaultAudioEndpointKind;
typedef enum XUserGamerPictureSize XUserGamerPictureSize;
typedef enum XUserGamertagComponent XUserGamertagComponent;
typedef enum XUserGetMsaTokenSilentlyOptions XUserGetMsaTokenSilentlyOptions;
typedef enum XUserGetTokenAndSignatureOptions XUserGetTokenAndSignatureOptions;
typedef enum XUserPlatformOperationResult XUserPlatformOperationResult;
typedef enum XUserPlatformSpopOperationResult XUserPlatformSpopOperationResult;
typedef enum XUserPrivilege XUserPrivilege;
typedef enum XUserPrivilegeDenyReason XUserPrivilegeDenyReason;
typedef enum XUserPrivilegeOptions XUserPrivilegeOptions;
typedef enum XUserState XUserState;

typedef struct XUser *XUserHandle;
typedef struct XUserPlatformOperationToken *XUserPlatformOperation;
typedef struct XUserSignOutDeferral *XUserSignOutDeferralHandle;

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
typedef void XUserPlatformRemoteConnectShowPromptEventHandler( void *context, UINT32 userIdentifier, XUserPlatformOperation operation, const char *url, const char *code, SIZE_T qrCodeSize, const void *qrCode );
typedef void XUserPlatformSpopPromptEventHandler( void *context, UINT32 userIdentifier, XUserPlatformOperation operation, const char *modernGamertag, const char *modernGamertagSuffix );

enum XUserAddOptions
{
    XUserAddOptions_None                        = 0x00,
    XUserAddOptions_AddDefaultUserSilently      = 0x01,
    XUserAddOptions_AllowGuests                 = 0x02,
    XUserAddOptions_AddDefaultUserAllowingUI    = 0x04,
};

enum XUserAgeGroup
{
    XUserAgeGroup_Unknown,
    XUserAgeGroup_Child,
    XUserAgeGroup_Teen,
    XUserAgeGroup_Adult,
};

enum XUserChangeEvent
{
    XUserChangeEvent_SignedInAgain,
    XUserChangeEvent_SigningOut,
    XUserChangeEvent_SignedOut,
    XUserChangeEvent_Gamertag,
    XUserChangeEvent_GamerPicture,
    XUserChangeEvent_Privileges,
};

enum XUserDefaultAudioEndpointKind
{
    XUserDefaultAudioEndpointKind_CommunicationRender,
    XUserDefaultAudioEndpointKind_CommunicationCapture,
};

enum XUserGamerPictureSize
{
    XUserGamerPictureSize_Small,
    XUserGamerPictureSize_Medium,
    XUserGamerPictureSize_Large,
    XUserGamerPictureSize_ExtraLarge,
};

enum XUserGamertagComponent
{
    XUserGamertagComponent_Classic,
    XUserGamertagComponent_Modern,
    XUserGamertagComponent_ModernSuffix,
    XUserGamertagComponent_UniqueModern,
};

enum XUserGetMsaTokenSilentlyOptions
{
    XUserGetMsaTokenSilentlyOptions_None,
};

enum XUserGetTokenAndSignatureOptions
{
    XUserGetTokenAndSignatureOptions_None           = 0x00,
    XUserGetTokenAndSignatureOptions_ForceRefresh   = 0x01,
    XUserGetTokenAndSignatureOptions_AllUsers       = 0x02,
};

enum XUserPlatformOperationResult
{
    XUserPlatformOperationResult_Success,
    XUserPlatformOperationResult_Failure,
    XUserPlatformOperationResult_Canceled,
};

enum XUserPlatformSpopOperationResult
{
    XUserPlatformSpopOperationResult_SignInHere,
    XUserPlatformSpopOperationResult_SwitchAccount,
    XUserPlatformSpopOperationResult_Failure,
    XUserPlatformSpopOperationResult_Canceled,
};

enum XUserPrivilege
{
    XUserPrivilege_CrossPlay            = 185,
    XUserPrivilege_Clubs                = 188,
    XUserPrivilege_Sessions             = 189,
    XUserPrivilege_Broadcast            = 190,
    XUserPrivilege_ManageProfilePrivacy = 196,
    XUserPrivilege_GameDvr              = 198,
    XUserPrivilege_MultiplayerParties   = 203,
    XUserPrivilege_CloudManageSession   = 207,
    XUserPrivilege_CloudJoinSession     = 208,
    XUserPrivilege_CloudSavedGames      = 209,
    XUserPrivilege_SocialNetworkSharing = 220,
    XUserPrivilege_UserGeneratedContent = 247,
    XUserPrivilege_Communications       = 252,
    XUserPrivilege_Multiplayer          = 254,
    XUserPrivilege_AddFriends           = 255,
};

enum XUserPrivilegeDenyReason
{
    XUserPrivilegeDenyReason_None,
    XUserPrivilegeDenyReason_PurchaseRequired,
    XUserPrivilegeDenyReason_Restricted,
    XUserPrivilegeDenyReason_Banned,
    XUserPrivilegeDenyReason_Unknown = -1,
};

enum XUserPrivilegeOptions
{
    XUserPrivilegeOptions_None      = 0x00,
    XUserPrivilegeOptions_AllUsers  = 0x01,
};

enum XUserState
{
    XUserState_SignedIn,
    XUserState_SigningOut,
    XUserState_SignedOut,
};

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
    const char *token;
    const char *signature;
};

struct XUserGetTokenAndSignatureHttpHeader
{
    const char *name;
    const char *value;
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

#endif
