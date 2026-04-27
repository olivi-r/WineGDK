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

HRESULT WINAPI XClosedCaptionGetProperties( XClosedCaptionProperties *properties )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XClosedCaptionSetEnabled( BOOLEAN enabled )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XHighContrastGetMode( XHighContrastMode *mode )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechToTextBeginHypothesisString( const char *speakerName, const char *content, XSpeechToTextType type, UINT32 *hypothesisId )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechToTextCancelHypothesisString( UINT32 hypothesisId )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechToTextFinalizeHypothesisString( UINT32 hypothesisId, const char *content )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechToTextSendString( const char *speakerName, const char *content, XSpeechToTextType type )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechToTextSetPositionHint( XSpeechToTextPositionHint position )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechToTextUpdateHypothesisString( UINT32 hypothesisId, const char *content )
{
    return E_NOTIMPL;
}
