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

HRESULT WINAPI XUserAddAsync( XUserAddOptions options, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserAddByIdWithUiAsync( UINT64 userId, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserAddByIdWithUiResult( XAsyncBlock *async, XUserHandle *newUser )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserAddResult( XAsyncBlock *async, XUserHandle *newUser )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserCheckPrivilege( XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, BOOLEAN *hasPrivilege, XUserPrivilegeDenyReason *reason )
{
    return E_NOTIMPL;
}

void WINAPI XUserCloseHandle( XUserHandle user )
{
}

void WINAPI XUserCloseSignOutDeferralHandle( XUserSignOutDeferralHandle deferral )
{
}

INT32 WINAPI XUserCompare( XUserHandle user1, XUserHandle user2 )
{
    return 0;
}

HRESULT WINAPI XUserDuplicateHandle( XUserHandle handle, XUserHandle *duplicatedHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserFindUserById( UINT64 userId, XUserHandle *handle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserFindUserByLocalId( XUserLocalId userLocalId, XUserHandle *handle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetAgeGroup( XUserHandle user, XUserAgeGroup *ageGroup )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetGamerPictureAsync( XUserHandle user, XUserGamerPictureSize pictureSize, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetGamerPictureResult( XAsyncBlock *async, SIZE_T bufferSize, void *buffer, SIZE_T *bufferUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetGamerPictureResultSize( XAsyncBlock *async, SIZE_T *bufferSize )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetId( XUserHandle user, UINT64 *userId )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetIsGuest( XUserHandle user, BOOLEAN *isGuest )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetLocalId( XUserHandle user, XUserLocalId *userLocalId )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetMaxUsers( UINT32 *maxUsers )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetMsaTokenSilentlyAsync( XUserHandle user, XUserGetMsaTokenSilentlyOptions options, const char *scope, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetMsaTokenSilentlyResult( XAsyncBlock *async, SIZE_T resultTokenSize, char *resultToken, SIZE_T *resultTokenUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetMsaTokenSilentlyResultSize( XAsyncBlock *async, SIZE_T *tokenSize )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetSignOutDeferral( XUserSignOutDeferralHandle *deferral )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetState( XUserHandle user, XUserState *state )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetTokenAndSignatureAsync( XUserHandle user, XUserGetTokenAndSignatureOptions options, const char *method, const char *url, SIZE_T headerCount, const XUserGetTokenAndSignatureHttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetTokenAndSignatureResult( XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureData **ptrToBuffer, SIZE_T *bufferUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetTokenAndSignatureResultSize( XAsyncBlock *async, SIZE_T *bufferSize )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetTokenAndSignatureUtf16Async( XUserHandle user, XUserGetTokenAndSignatureOptions options, const WCHAR *method, const WCHAR *url, SIZE_T headerCount, const XUserGetTokenAndSignatureUtf16HttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetTokenAndSignatureUtf16Result( XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureUtf16Data **ptrToBuffer, SIZE_T *bufferUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserGetTokenAndSignatureUtf16ResultSize( XAsyncBlock *async, SIZE_T *bufferSize )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XUserIsSignOutPresent()
{
    return FALSE;
}

BOOLEAN WINAPI XUserIsStoreUser( XUserHandle user )
{
    return FALSE;
}

HRESULT WINAPI XUserPlatformRemoteConnectCancelPrompt( XUserPlatformOperation operation )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserPlatformRemoteConnectSetEventHandlers( XTaskQueueHandle queue, XUserPlatformRemoteConnectEventHandlers *handlers )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserPlatformSpopPromptComplete( XUserPlatformOperation operation, XUserPlatformOperationResult result )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserPlatformSpopPromptSetEventHandlers( XTaskQueueHandle queue, XUserPlatformSpopPromptEventHandler *handler, void *context )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserRegisterForChangeEvent( XTaskQueueHandle queue, void *context, XUserChangeEventCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserResolveIssueWithUiAsync( XUserHandle user, const char *url, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserResolveIssueWithUiResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserResolveIssueWithUiUtf16Async( XUserHandle user, const WCHAR *url, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserResolveIssueWithUiUtf16Result( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserResolvePrivilegeWithUiAsync( XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserResolvePrivilegeWithUiResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserSignOutAsync( XUserHandle user, XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XUserSignOutResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XUserUnregisterForChangeEvent( XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    return FALSE;
}
