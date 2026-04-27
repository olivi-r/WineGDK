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

HRESULT WINAPI XSpeechSynthesizerCloseHandle( XSpeechSynthesizerHandle speechSynthesizer )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerCloseStreamHandle( XSpeechSynthesizerStreamHandle speechSynthesisStream )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerCreate( XSpeechSynthesizerHandle *speechSynthesizer )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerCreateStreamFromSsml( XSpeechSynthesizerHandle speechSynthesizer, const char *ssml, XSpeechSynthesizerStreamHandle *speechSynthesisStream )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerCreateStreamFromText( XSpeechSynthesizerHandle speechSynthesizer, const char *text, XSpeechSynthesizerStreamHandle *speechSynthesisStream )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerEnumerateInstalledVoices( void *context, XSpeechSynthesizerInstalledVoicesCallback *callback )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerGetStreamData( XSpeechSynthesizerStreamHandle speechSynthesisStream, SIZE_T bufferSize, void *buffer, SIZE_T *bufferUsed )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerGetStreamDataSize( XSpeechSynthesizerStreamHandle speechSynthesisStream, SIZE_T *bufferSize )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerSetCustomVoice( XSpeechSynthesizerHandle speechSynthesizer, const char *voiceId )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XSpeechSynthesizerSetDefaultVoice( XSpeechSynthesizerHandle speechSynthesizer )
{
    return E_NOTIMPL;
}
