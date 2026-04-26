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

void WINAPI XTaskQueueCloseHandle( XTaskQueueHandle queue )
{
}

HRESULT WINAPI XTaskQueueCreate( XTaskQueueDispatchMode workDispatchMode, XTaskQueueDispatchMode completionDispatchMode, XTaskQueueHandle *queue )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XTaskQueueCreateComposite( XTaskQueuePortHandle workPort, XTaskQueuePortHandle completionPort, XTaskQueueHandle *queue )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XTaskQueueDispatch( XTaskQueueHandle queue, XTaskQueuePort port, UINT32 timeoutInMs )
{
    return FALSE;
}

HRESULT WINAPI XTaskQueueDuplicateHandle( XTaskQueueHandle queueHandle, XTaskQueueHandle *duplicatedHandle )
{
    return E_NOTIMPL;
}

BOOLEAN WINAPI XTaskQueueGetCurrentProcessTaskQueue( XTaskQueueHandle *queue )
{
    return FALSE;
}

HRESULT WINAPI XTaskQueueGetPort( XTaskQueueHandle queue, XTaskQueuePort port, XTaskQueuePortHandle *portHandle )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XTaskQueueRegisterMonitor( XTaskQueueHandle queue, void *callbackContext, XTaskQueueMonitorCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XTaskQueueRegisterWaiter( XTaskQueueHandle queue, XTaskQueuePort port, HANDLE waitHandle, void *callbackContext, XTaskQueueCallback *callback, XTaskQueueRegistrationToken *token )
{
    return E_NOTIMPL;
}

void WINAPI XTaskQueueSetCurrentProcessTaskQueue( XTaskQueueHandle queue )
{
}

HRESULT WINAPI XTaskQueueSubmitCallback( XTaskQueueHandle queue, XTaskQueuePort port, void *callbackContext, XTaskQueueCallback *callback )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XTaskQueueSubmitDelayedCallback( XTaskQueueHandle queue, XTaskQueuePort port, UINT32 delayMs, void *callbackContext, XTaskQueueCallback *callback )
{
    return E_NOTIMPL;
}

HRESULT WINAPI XTaskQueueTerminate( XTaskQueueHandle queue, BOOLEAN wait, void *callbackContext, XTaskQueueTerminatedCallback *callback )
{
    return E_NOTIMPL;
}

void WINAPI XTaskQueueUnregisterMonitor( XTaskQueueHandle queue, XTaskQueueRegistrationToken token )
{
}

void WINAPI XTaskQueueUnregisterWaiter( XTaskQueueHandle queue, XTaskQueueRegistrationToken token )
{
}
