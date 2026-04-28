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

HRESULT WINAPI XGameUiSetAchievementsUiResponse( XGameUiCallbackHandle callbackHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetErrorDialogUiResponse( XGameUiCallbackHandle callbackHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetMessageDialogUiResponse( XGameUiCallbackHandle callbackHandle, XGameUiMessageDialogButton response )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetMultiplayerActivityGameInviteUiResponse( XGameUiCallbackHandle callbackHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetNotificationPositionHint( XGameUiNotificationPositionHint position )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetPlayerPickerUiResponse( XGameUiCallbackHandle callbackHandle, UINT32 playerCount, const UINT64 *players )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetPlayerProfileCardUiResponse( XGameUiCallbackHandle callbackHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetSendGameInviteUiResponse( XGameUiCallbackHandle callbackHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetTextEntryUiResponse( XGameUiCallbackHandle callbackHandle, const char *response )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiSetUiCallbacks( const XGameUiUiCallbacks *callbacks, BOOLEAN useSystemUiIfAvailable )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowAchievementsAsync( XAsyncBlock *async, XUserHandle requestingUser, UINT32 titleId )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowAchievementsResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowErrorDialogAsync( XAsyncBlock *async, HRESULT errorCode, const char *context )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowErrorDialogResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowMessageDialogAsync( XAsyncBlock *async, const char *titleText, const char *contentText, const char *firstButtonText, const char *secondButtonText, const char *thirdButtonText, XGameUiMessageDialogButton defaultButton, XGameUiMessageDialogButton cancelButton )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowMessageDialogResult( XAsyncBlock *async, XGameUiMessageDialogButton *resultButton )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowMultiplayerActivityGameInviteAsync( XAsyncBlock *async, XUserHandle requestingUser )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowMultiplayerActivityGameInviteResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowPlayerPickerAsync( XAsyncBlock *async, XUserHandle requestingUser, const char *promptText, UINT32 selectFromPlayersCount, const UINT64 *selectFromPlayers, UINT32 preSelectedPlayersCount, UINT64 *preSelectedPlayers, UINT32 minSelectionCount, UINT32 maxSelectionCount )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowPlayerPickerResult( XAsyncBlock *async, UINT32 resultPlayersCount, UINT64 *resultPlayers, UINT32 *resultPlayersUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowPlayerPickerResultCount( XAsyncBlock *async, UINT32 *resultPlayersCount )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowPlayerProfileCardAsync( XAsyncBlock *async, XUserHandle requestingUser, UINT64 targetPlayer )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowPlayerProfileCardResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowSendGameInviteAsync( XAsyncBlock *async, XUserHandle requestingUser, const char *sessionConfigurationId, const char *sessionTemplateName, const char *sessionId, const char *invitationText, const char *customActivationContext )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowSendGameInviteResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowStateShareAsync( XAsyncBlock *async, XUserHandle requestingUser, const char *linkToken )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowStateShareResult( XAsyncBlock *async )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowTextEntryAsync( XAsyncBlock *async, const char *titleText, const char *descriptionText, const char *defaultText, XGameUiTextEntryInputScope inputScope, UINT32 maxTextLength )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowTextEntryResult( XAsyncBlock *async, UINT32 resultTextBufferSize, char *resultTextBuffer, UINT32 *resultTextBufferUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowTextEntryResultSize( XAsyncBlock *async, UINT32 *resultTextBufferSize )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowWebAuthenticationAsync( XAsyncBlock *async, XUserHandle requestingUser, const char *requestUri, const char *completionUri )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowWebAuthenticationResult( XAsyncBlock *async, SIZE_T bufferSize, void *buffer, XGameUiWebAuthenticationResultData **ptrToBuffer, SIZE_T *bufferUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowWebAuthenticationResultSize( XAsyncBlock *async, SIZE_T *bufferSize )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiShowWebAuthenticationWithOptionsAsync( XAsyncBlock *async, XUserHandle requestingUser, const char *requestUri, const char *completionUri, XGameUiWebAuthenticationOptions options )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiTextEntryClose( XGameUiTextEntryHandle handle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiTextEntryGetExtents( XGameUiTextEntryHandle handle, XGameUiTextEntryExtents *extents )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiTextEntryGetState( XGameUiTextEntryHandle handle, XGameUiTextEntryChangeTypeFlags *changeType, UINT32 *cursorIndex, UINT32 *imeClauseStartIndex, UINT32 *imeClauseEndIndex, UINT32 bufferSize, char *buffer )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiTextEntryOpen( const XGameUiTextEntryOptions *options, UINT32 maxLength, const char *initialText, UINT32 initialCursorIndex, XGameUiTextEntryHandle *handle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiTextEntryUpdatePositionHint( XGameUiTextEntryHandle handle, XGameUiTextEntryPositionHint positionHint )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XGameUiTextEntryUpdateVisibility( XGameUiTextEntryHandle handle, XGameUiTextEntryVisibilityFlags visibilityFlags )
{
    return E_NOTIMPL;
}
