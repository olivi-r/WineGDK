/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XUser
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

WINE_DEFAULT_DEBUG_CHANNEL(gdkc);

struct x_user
{
    IUserImpl6 IUserImpl_iface;
    IUserGamertagImpl IUserGamertagImpl_iface;
    LONG ref;
};

static inline struct x_user *impl_from_IUserImpl6( IUserImpl6 *iface )
{
    return CONTAINING_RECORD( iface, struct x_user, IUserImpl_iface );
}

static HRESULT WINAPI x_user_QueryInterface( IUserImpl6 *iface, REFIID iid, void **out )
{
    struct x_user *impl = impl_from_IUserImpl6( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown   ) ||
        IsEqualGUID( iid, &IID_IUserImpl1 ) ||
        IsEqualGUID( iid, &IID_IUserImpl2 ) ||
        IsEqualGUID( iid, &IID_IUserImpl3 ) ||
        IsEqualGUID( iid, &IID_IUserImpl4 ) ||
        IsEqualGUID( iid, &IID_IUserImpl5 ) ||
        IsEqualGUID( iid, &IID_IUserImpl6 ))
    {
        IUserImpl6_AddRef( *out = &impl->IUserImpl_iface );
        return S_OK;
    }

    if (IsEqualGUID( iid, &IID_IUserGamertagImpl ))
    {
        IUserGamertagImpl_AddRef( *out = &impl->IUserGamertagImpl_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_user_AddRef( IUserImpl6 *iface )
{
    struct x_user *impl = impl_from_IUserImpl6( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_user_Release( IUserImpl6 *iface )
{
    struct x_user *impl = impl_from_IUserImpl6( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_user_XUserDuplicateHandle( IUserImpl6 *iface, XUserHandle handle, XUserHandle *duplicatedHandle )
{
    FIXME( "iface %p, handle %p, duplicatedHandle %p stub!\n", iface, handle, duplicatedHandle );
    return E_NOTIMPL;
}

static void WINAPI x_user_XUserCloseHandle( IUserImpl6 *iface, XUserHandle user )
{
    FIXME( "iface %p, user %p stub!\n", iface, user );
}

static INT32 WINAPI x_user_XUserCompare( IUserImpl6 *iface, XUserHandle user1, XUserHandle user2 )
{
    FIXME( "iface %p, user1 %p, user2 %p stub!\n", iface, user1, user2 );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMaxUsers( IUserImpl6 *iface, UINT32 *maxUsers )
{
    TRACE( "iface %p, maxUsers %p.\n", iface, maxUsers );
    *maxUsers = 1;
    return S_OK;
}

static HRESULT WINAPI x_user_XUserAddAsync( IUserImpl6 *iface, XUserAddOptions options, XAsyncBlock *async )
{
    FIXME( "iface %p, options %d, async %p stub!\n", iface, options, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserAddResult( IUserImpl6 *iface, XAsyncBlock *async, XUserHandle *newUser )
{
    FIXME( "iface %p, async %p, newUser %p stub!\n", iface, async, newUser );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetLocalId( IUserImpl6 *iface, XUserHandle user, XUserLocalId *userLocalId )
{
    FIXME( "iface %p, user %p, userLocalId %p stub!\n", iface, user, userLocalId );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserFindUserByLocalId( IUserImpl6 *iface, XUserLocalId userLocalId, XUserHandle *handle )
{
    FIXME( "iface %p, userLocalId %p, handle %p stub!\n", iface, &userLocalId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetId( IUserImpl6 *iface, XUserHandle user, UINT64 *userId )
{
    FIXME( "iface %p, user %p, userId %p stub!\n", iface, user, userId );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserFindUserById( IUserImpl6 *iface, UINT64 userId, XUserHandle *handle )
{
    FIXME( "iface %p, userId %llu, handle %p stub!\n", iface, userId, handle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetIsGuest( IUserImpl6 *iface, XUserHandle user, BOOLEAN *isGuest )
{
    FIXME( "iface %p, user %p, isGuest %p stub!\n", iface, user, isGuest );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetState( IUserImpl6 *iface, XUserHandle user, XUserState *state )
{
    FIXME( "iface %p, user %p, state %p stub!\n", iface, user, state );
    return E_NOTIMPL;
}

static HRESULT WINAPI __PADDING__( IUserImpl6 *iface )
{
    WARN( "iface %p padding function called! It's unknown what this function does.\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureAsync( IUserImpl6 *iface, XUserHandle user, XUserGamerPictureSize pictureSize, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, pictureSize %d, async %p stub!\n", iface, user, pictureSize, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResultSize( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetGamerPictureResult( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetAgeGroup( IUserImpl6 *iface, XUserHandle user, XUserAgeGroup *ageGroup )
{
    FIXME( "iface %p, user %p, ageGroup %p stub!\n", iface, user, ageGroup );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserCheckPrivilege( IUserImpl6 *iface, XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, BOOLEAN *hasPrivilege, XUserPrivilegeDenyReason *reason )
{
    FIXME( "iface %p, user %p, options %d, privilege %d, hasPrivilege %p, reason %p stub!\n", iface, user, options, privilege, hasPrivilege, reason );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolvePrivilegeWithUiAsync( IUserImpl6 *iface, XUserHandle user, XUserPrivilegeOptions options, XUserPrivilege privilege, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, privilege %d, async %p stub!\n", iface, user, options, privilege, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolvePrivilegeWithUiResult( IUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureAsync( IUserImpl6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const char *method, const char *url, SIZE_T headerCount, const XUserGetTokenAndSignatureHttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, method %s, url %s, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p stub!\n", iface, user, options, debugstr_a( method ), debugstr_a( url ), headerCount, headers, bodySize, bodyBuffer, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResultSize( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureResult( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureData **ptrToBuffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Async( IUserImpl6 *iface, XUserHandle user, XUserGetTokenAndSignatureOptions options, const WCHAR *method, const WCHAR *url, SIZE_T headerCount, const XUserGetTokenAndSignatureUtf16HttpHeader *headers, SIZE_T bodySize, const void *bodyBuffer, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %d, method %s, url %s, headerCount %Iu, headers %p, bodySize %Iu, bodyBuffer %p, async %p stub!\n", iface, user, options, debugstr_w( method ), debugstr_w( url ), headerCount, headers, bodySize, bodyBuffer, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16ResultSize( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T *bufferSize )
{
    FIXME( "iface %p, async %p, bufferSize %p stub!\n", iface, async, bufferSize );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetTokenAndSignatureUtf16Result( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XUserGetTokenAndSignatureUtf16Data **ptrToBuffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p, async %p, bufferSize %Iu, buffer %p, ptrToBuffer %p, bufferUsed %p stub!\n", iface, async, bufferSize, buffer, ptrToBuffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiAsync( IUserImpl6 *iface, XUserHandle user, const char *url, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, url %s, async %p stub!\n", iface, user, debugstr_a( url ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiResult( IUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiUtf16Async( IUserImpl6 *iface, XUserHandle user, const WCHAR *url, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, url %s, async %p stub!\n", iface, user, debugstr_w( url ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserResolveIssueWithUiUtf16Result( IUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserRegisterForChangeEvent( IUserImpl6 *iface, XTaskQueueHandle queue, void *context, XUserChangeEventCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, context %p, callback %p, token %p stub!\n", iface, queue, context, callback, token );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_user_XUserUnregisterForChangeEvent( IUserImpl6 *iface, XTaskQueueRegistrationToken token, BOOLEAN wait )
{
    FIXME( "iface %p, token %p, wait %d stub!\n", iface, &token, wait );
    return FALSE;
}

static HRESULT WINAPI x_user_XUserGetSignOutDeferral( IUserImpl6 *iface, XUserSignOutDeferralHandle *deferral )
{
    TRACE( "iface %p, deferral %p.\n", iface, deferral );
    *deferral = NULL;
    return E_GAMEUSER_DEFERRAL_NOT_AVAILABLE;
}

static void WINAPI x_user_XUserCloseSignOutDeferralHandle( IUserImpl6 *iface, XUserSignOutDeferralHandle deferral )
{
    TRACE( "iface %p, deferral %p.\n", iface, deferral );
}

static HRESULT WINAPI x_user_XUserAddByIdWithUiAsync( IUserImpl6 *iface, UINT64 userId, XAsyncBlock *async )
{
    FIXME( "iface %p, userId %llu, async %p stub!\n", iface, userId, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserAddByIdWithUiResult( IUserImpl6 *iface, XAsyncBlock *async, XUserHandle *newUser )
{
    FIXME( "iface %p, async %p, newUser %p stub!\n", iface, async, newUser );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyAsync( IUserImpl6 *iface, XUserHandle user, XUserGetMsaTokenSilentlyOptions options, const char *scope, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, options %u, scope %s, async %p stub!\n", iface, user, options, debugstr_a( scope ), async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResult( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T resultTokenSize, char *resultToken, SIZE_T *resultTokenUsed )
{
    FIXME( "iface %p, async %p, resultTokenSize %Iu, resultToken %p, resultTokenUsed %p stub!\n", iface, async, resultTokenSize, resultToken, resultTokenUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserGetMsaTokenSilentlyResultSize( IUserImpl6 *iface, XAsyncBlock *async, SIZE_T *tokenSize )
{
    FIXME( "iface %p, async %p, tokenSize %p stub!\n", iface, async, tokenSize );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_user_XUserIsStoreUser( IUserImpl6 *iface, XUserHandle user )
{
    FIXME( "iface %p, user %p stub!\n", iface, user );
    return TRUE;
}

static HRESULT WINAPI x_user_XUserPlatformRemoteConnectSetEventHandlers( IUserImpl6 *iface, XTaskQueueHandle queue, XUserPlatformRemoteConnectEventHandlers *handlers )
{
    FIXME( "iface %p, queue %p, handlers %p stub!\n", iface, queue, handlers );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformRemoteConnectCancelPrompt( IUserImpl6 *iface, XUserPlatformOperation operation )
{
    FIXME( "iface %p, operation %p stub!\n", iface, operation );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformSpopPromptSetEventHandlers( IUserImpl6 *iface, XTaskQueueHandle queue, XUserPlatformSpopPromptEventHandler *handler, void *context )
{
    FIXME( "iface %p, queue %p, handler %p, context %p stub!\n", iface, queue, handler, context );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserPlatformSpopPromptComplete( IUserImpl6 *iface, XUserPlatformOperation operation, XUserPlatformOperationResult result )
{
    FIXME( "iface %p, operation %p, result %d stub!\n", iface, operation, result );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_user_XUserIsSignOutPresent( IUserImpl6 *iface )
{
    TRACE( "iface %p.\n", iface );
    return FALSE;
}

static HRESULT WINAPI x_user_XUserSignOutAsync( IUserImpl6 *iface, XUserHandle user, XAsyncBlock *async )
{
    FIXME( "iface %p, user %p, async %p stub!\n", iface, user, async );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_user_XUserSignOutResult( IUserImpl6 *iface, XAsyncBlock *async )
{
    FIXME( "iface %p, async %p stub!\n", iface, async );
    return E_NOTIMPL;
}

static const struct IUserImpl6Vtbl x_user_vtbl =
{
    x_user_QueryInterface,
    x_user_AddRef,
    x_user_Release,
    /* IUserImpl1 methods */
    x_user_XUserDuplicateHandle,
    x_user_XUserCloseHandle,
    x_user_XUserCompare,
    x_user_XUserGetMaxUsers,
    x_user_XUserAddAsync,
    x_user_XUserAddResult,
    x_user_XUserGetLocalId,
    x_user_XUserFindUserByLocalId,
    x_user_XUserGetId,
    x_user_XUserFindUserById,
    x_user_XUserGetIsGuest,
    x_user_XUserGetState,
    __PADDING__,
    x_user_XUserGetGamerPictureAsync,
    x_user_XUserGetGamerPictureResultSize,
    x_user_XUserGetGamerPictureResult,
    x_user_XUserGetAgeGroup,
    x_user_XUserCheckPrivilege,
    x_user_XUserResolvePrivilegeWithUiAsync,
    x_user_XUserResolvePrivilegeWithUiResult,
    x_user_XUserGetTokenAndSignatureAsync,
    x_user_XUserGetTokenAndSignatureResultSize,
    x_user_XUserGetTokenAndSignatureResult,
    x_user_XUserGetTokenAndSignatureUtf16Async,
    x_user_XUserGetTokenAndSignatureUtf16ResultSize,
    x_user_XUserGetTokenAndSignatureUtf16Result,
    x_user_XUserResolveIssueWithUiAsync,
    x_user_XUserResolveIssueWithUiResult,
    x_user_XUserResolveIssueWithUiUtf16Async,
    x_user_XUserResolveIssueWithUiUtf16Result,
    x_user_XUserRegisterForChangeEvent,
    x_user_XUserUnregisterForChangeEvent,
    x_user_XUserGetSignOutDeferral,
    x_user_XUserCloseSignOutDeferralHandle,
    /* IUserImpl2 methods */
    x_user_XUserAddByIdWithUiAsync,
    x_user_XUserAddByIdWithUiResult,
    /* IUserImpl3 methods */
    x_user_XUserGetMsaTokenSilentlyAsync,
    x_user_XUserGetMsaTokenSilentlyResult,
    x_user_XUserGetMsaTokenSilentlyResultSize,
    /* IUserImpl4 methods */
    x_user_XUserIsStoreUser,
    /* IUserImpl5 methods */
    x_user_XUserPlatformRemoteConnectSetEventHandlers,
    x_user_XUserPlatformRemoteConnectCancelPrompt,
    x_user_XUserPlatformSpopPromptSetEventHandlers,
    x_user_XUserPlatformSpopPromptComplete,
    /* IUserImpl6 methods */
    x_user_XUserIsSignOutPresent,
    x_user_XUserSignOutAsync,
    x_user_XUserSignOutResult,
};

static inline struct x_user *impl_from_IUserGamertagImpl( IUserGamertagImpl *iface )
{
    return CONTAINING_RECORD( iface, struct x_user, IUserGamertagImpl_iface );
}

static HRESULT WINAPI x_user_gamertag_QueryInterface( IUserGamertagImpl *iface, REFIID riid, void **out )
{
    struct x_user *impl = impl_from_IUserGamertagImpl( iface );
    return IUserImpl6_QueryInterface( &impl->IUserImpl_iface, riid, out );
}

static ULONG WINAPI x_user_gamertag_AddRef( IUserGamertagImpl *iface )
{
    struct x_user *impl = impl_from_IUserGamertagImpl( iface );
    return IUserImpl6_AddRef( &impl->IUserImpl_iface );
}

static ULONG WINAPI x_user_gamertag_Release( IUserGamertagImpl *iface )
{
    struct x_user *impl = impl_from_IUserGamertagImpl( iface );
    return IUserImpl6_Release( &impl->IUserImpl_iface );
}

static HRESULT WINAPI x_user_gamertag_XUserGetGamertag( IUserGamertagImpl *iface, XUserHandle user, XUserGamertagComponent gamertagComponent, SIZE_T gamertagSize, char *gamertag, SIZE_T *gamertagUsed )
{
    FIXME( "iface %p, user %p, gamertagComponent %d, gamertagSize %Iu, gamertag %p, gamertagUsed %p stub!\n", iface, user, gamertagComponent, gamertagSize, gamertag, gamertagUsed );
    return E_NOTIMPL;
}

static const struct IUserGamertagImplVtbl x_user_gamertag_vtbl =
{
    x_user_gamertag_QueryInterface,
    x_user_gamertag_AddRef,
    x_user_gamertag_Release,
    /* IUserGamertagImpl methods */
    x_user_gamertag_XUserGetGamertag,
};

static struct x_user x_user =
{
    {&x_user_vtbl},
    {&x_user_gamertag_vtbl},
    0,
};

IUserImpl6 *x_user_impl = &x_user.IUserImpl_iface;
