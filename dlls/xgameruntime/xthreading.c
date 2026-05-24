/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XAsync, XTaskQueue and XThread
 *
 * Written by Weather
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

struct x_threading
{
    IXThreading IXThreading_iface;
    LONG ref;
};

static inline struct x_threading *impl_from_IXThreading( IXThreading *iface )
{
    return CONTAINING_RECORD( iface, struct x_threading, IXThreading_iface );
}

static HRESULT WINAPI x_threading_QueryInterface( IXThreading *iface, REFIID iid, void **out )
{
    struct x_threading *impl = impl_from_IXThreading( iface );

    TRACE( "iface %p, iid %s, out %p.\n", iface, debugstr_guid( iid ), out );

    if (IsEqualGUID( iid, &IID_IUnknown    ) ||
        IsEqualGUID( iid, &IID_IXThreading ))
    {
        IXThreading_AddRef( *out = &impl->IXThreading_iface );
        return S_OK;
    }

    FIXME( "%s not implemented, returning E_NOINTERFACE.\n", debugstr_guid( iid ) );
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI x_threading_AddRef( IXThreading *iface )
{
    struct x_threading *impl = impl_from_IXThreading( iface );
    ULONG ref = InterlockedIncrement( &impl->ref );
    TRACE( "iface %p increasing refcount to %lu.\n", iface, ref );
    return ref;
}

static ULONG WINAPI x_threading_Release( IXThreading *iface )
{
    struct x_threading *impl = impl_from_IXThreading( iface );
    ULONG ref = InterlockedDecrement( &impl->ref );
    TRACE( "iface %p decreasing refcount to %lu.\n", iface, ref );
    return ref;
}

static HRESULT WINAPI x_threading_XAsyncGetStatus( IXThreading *iface, XAsyncBlock *asyncBlock, BOOLEAN wait )
{
    FIXME( "iface %p, asyncBlock %p, wait %d stub!\n", iface, asyncBlock, wait );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XAsyncGetResultSize( IXThreading *iface, XAsyncBlock *asyncBlock, SIZE_T *bufferSize )
{
    FIXME( "iface %p, asyncBlock %p, bufferSize %p stub!\n", iface, asyncBlock, bufferSize );
    return E_NOTIMPL;
}

static VOID WINAPI x_threading_XAsyncCancel( IXThreading *iface, XAsyncBlock *asyncBlock )
{
    FIXME( "iface %p, asyncBlock %p stub!\n", iface, asyncBlock );
}

static HRESULT WINAPI x_threading_XAsyncRun( IXThreading *iface, XAsyncBlock *asyncBlock, XAsyncWork *work )
{
    FIXME( "iface %p, asyncBlock %p, work %p stub!\n", iface, asyncBlock, work );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XAsyncBegin( IXThreading *iface, XAsyncBlock *asyncBlock, void *context, const void *identity, const char *identityName, XAsyncProvider *provider )
{
    FIXME( "iface %p, asyncBlock %p, context %p, identity %p, identityName %s, provider %p stub!\n", iface, asyncBlock, context, identity, identityName, provider );
    return E_NOTIMPL;
}

static HRESULT WINAPI __PADDING__( IXThreading *iface )
{
    WARN( "iface %p padding function called! It's unknown what this function does.\n", iface );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XAsyncSchedule( IXThreading *iface, XAsyncBlock *asyncBlock, UINT32 delayInMs )
{
    FIXME( "iface %p, asyncBlock %p, delayInMs %d stub!\n", iface, asyncBlock, delayInMs );
    return E_NOTIMPL;
}

static VOID WINAPI x_threading_XAsyncComplete( IXThreading *iface, XAsyncBlock *asyncBlock, HRESULT result, SIZE_T requiredBufferSize )
{
    FIXME( "iface %p, asyncBlock %p, result %#lx, requiredBufferSize %Iu stub!\n", iface, asyncBlock, result, requiredBufferSize );
}

static HRESULT WINAPI x_threading_XAsyncGetResult( IXThreading *iface, XAsyncBlock *asyncBlock, const void *identity, SIZE_T bufferSize, void *buffer, SIZE_T *bufferUsed )
{
    FIXME( "iface %p asyncBlock %p, identity %p, bufferSize %Iu, buffer %p, bufferUsed %p stub!\n", iface, asyncBlock, identity, bufferSize, buffer, bufferUsed );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XTaskQueueCreate( IXThreading *iface, XTaskQueueDispatchMode workDispatchMode, XTaskQueueDispatchMode completionDispatchMode, XTaskQueueHandle *queue )
{
    FIXME( "iface %p, workDispatchMode %d, completionDispatchMode %d, queue %p stub!\n", iface, workDispatchMode, completionDispatchMode, queue );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XTaskQueueCreateComposite( IXThreading *iface, XTaskQueuePortHandle workPort, XTaskQueuePortHandle completionPort, XTaskQueueHandle *queue )
{
    FIXME( "iface %p, workPort %p, completionPort %p, queue %p stub!\n", iface, workPort, completionPort, queue );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XTaskQueueGetPort( IXThreading *iface, XTaskQueueHandle queue, XTaskQueuePort port, XTaskQueuePortHandle *portHandle )
{
    FIXME( "iface %p, queue %p, port %d, portHandle %p stub!\n", iface, queue, port, portHandle );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XTaskQueueDuplicateHandle( IXThreading *iface, XTaskQueueHandle queueHandle, XTaskQueueHandle *duplicatedHandle )
{
    FIXME( "iface %p, queueHandle %p, duplicatedHandle %p stub!\n", iface, queueHandle, duplicatedHandle );
    return E_NOTIMPL;
}

static BOOLEAN WINAPI x_threading_XTaskQueueDispatch( IXThreading *iface, XTaskQueueHandle queue, XTaskQueuePort port, UINT32 timeoutInMs )
{
    FIXME( "iface %p, queue %p, port %d, timeoutInMs %d stub!\n", iface, queue, port, timeoutInMs );
    return FALSE;
}

static VOID WINAPI x_threading_XTaskQueueCloseHandle( IXThreading *iface, XTaskQueueHandle queue )
{
    FIXME( "iface %p, queue %p stub!\n", iface, queue );
}

static HRESULT WINAPI x_threading_XTaskQueueSubmitCallback( IXThreading *iface, XTaskQueueHandle queue, XTaskQueuePort port, void *callbackContext, XTaskQueueCallback *callback )
{
    FIXME( "iface %p, queue %p, port %d, callbackContext %p, callback %p stub!\n", iface, queue, port, callbackContext, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XTaskQueueSubmitDelayedCallback( IXThreading *iface, XTaskQueueHandle queue, XTaskQueuePort port, UINT32 delayMs, void *callbackContext, XTaskQueueCallback *callback )
{
    FIXME( "iface %p, queue %p, port %d, delayMs %d, callbackContext %p, callback %p stub!\n", iface, queue, port, delayMs, callbackContext, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XTaskQueueRegisterWaiter( IXThreading *iface, XTaskQueueHandle queue, XTaskQueuePort port, HANDLE waitHandle, void *callbackContext, XTaskQueueCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, port %d, waitHandle %p, callbackContext %p, callback %p, token %p stub!\n", iface, queue, port, waitHandle, callbackContext, callback, token );
    return E_NOTIMPL;
}

static VOID WINAPI x_threading_XTaskQueueUnregisterWaiter( IXThreading *iface, XTaskQueueHandle queue, XTaskQueueRegistrationToken token )
{
    FIXME( "iface %p, queue %p, token %p stub!\n", iface, queue, &token );
}

static HRESULT WINAPI x_threading_XTaskQueueTerminate( IXThreading *iface, XTaskQueueHandle queue, BOOLEAN wait, void *callbackContext, XTaskQueueTerminatedCallback *callback )
{
    FIXME( "iface %p, queue %p, wait %d, callbackContext %p, callback %p stub!\n", iface, queue, wait, callbackContext, callback );
    return E_NOTIMPL;
}

static HRESULT WINAPI x_threading_XTaskQueueRegisterMonitor( IXThreading *iface, XTaskQueueHandle queue, void *callbackContext, XTaskQueueMonitorCallback *callback, XTaskQueueRegistrationToken *token )
{
    FIXME( "iface %p, queue %p, callbackContext %p, callback %p, token %p stub!\n", iface, queue, callbackContext, callback, token );
    return E_NOTIMPL;
}

static VOID WINAPI x_threading_XTaskQueueUnregisterMonitor( IXThreading *iface, XTaskQueueHandle queue, XTaskQueueRegistrationToken token )
{
    FIXME( "iface %p, queue %p, token %p stub!\n", iface, queue, &token );
}

static BOOLEAN WINAPI x_threading_XTaskQueueGetCurrentProcessTaskQueue( IXThreading *iface, XTaskQueueHandle *queue )
{
    FIXME( "iface %p, queue %p stub!\n", iface, queue );
    return FALSE;
}

static VOID WINAPI x_threading_XTaskQueueSetCurrentProcessTaskQueue( IXThreading *iface, XTaskQueueHandle queue )
{
    FIXME( "iface %p, queue %p stub!\n", iface, queue );
}

static HRESULT WINAPI x_threading_XThreadSetTimeSensitive( IXThreading *iface, BOOLEAN isTimeSensitiveThread )
{
    TRACE( "iface %p, isTimeSensitiveThread %d.\n", iface, isTimeSensitiveThread );

    if (tlsIndex == TLS_OUT_OF_INDEXES) return E_FAIL;
    if (!TlsSetValue( tlsIndex, (void *)(UINT_PTR)isTimeSensitiveThread ))
        return HRESULT_FROM_WIN32( GetLastError() );
    return S_OK;
}

static VOID WINAPI x_threading_XThreadAssertNotTimeSensitive( IXThreading *iface )
{
    TRACE( "iface %p.\n", iface );

    if (!IXThreading_XThreadIsTimeSensitive( iface )) return;
    if (IsDebuggerPresent()) DebugBreak();
}

static BOOLEAN WINAPI x_threading_XThreadIsTimeSensitive( IXThreading *iface )
{
    TRACE( "iface %p.\n", iface );

    if (tlsIndex == TLS_OUT_OF_INDEXES) return FALSE;
    return (UINT_PTR)TlsGetValue( tlsIndex );
}

static const struct IXThreadingVtbl x_threading_vtbl =
{
    x_threading_QueryInterface,
    x_threading_AddRef,
    x_threading_Release,
    /* IXThreading methods */
    x_threading_XAsyncGetStatus,
    x_threading_XAsyncGetResultSize,
    x_threading_XAsyncCancel,
    x_threading_XAsyncRun,
    x_threading_XAsyncBegin,
    __PADDING__,
    x_threading_XAsyncSchedule,
    x_threading_XAsyncComplete,
    x_threading_XAsyncGetResult,
    x_threading_XTaskQueueCreate,
    x_threading_XTaskQueueCreateComposite,
    x_threading_XTaskQueueGetPort,
    x_threading_XTaskQueueDuplicateHandle,
    x_threading_XTaskQueueDispatch,
    x_threading_XTaskQueueCloseHandle,
    x_threading_XTaskQueueSubmitCallback,
    x_threading_XTaskQueueSubmitDelayedCallback,
    x_threading_XTaskQueueRegisterWaiter,
    x_threading_XTaskQueueUnregisterWaiter,
    x_threading_XTaskQueueTerminate,
    x_threading_XTaskQueueRegisterMonitor,
    x_threading_XTaskQueueUnregisterMonitor,
    x_threading_XTaskQueueGetCurrentProcessTaskQueue,
    x_threading_XTaskQueueSetCurrentProcessTaskQueue,
    x_threading_XThreadSetTimeSensitive,
    __PADDING__,
    x_threading_XThreadAssertNotTimeSensitive,
    x_threading_XThreadIsTimeSensitive
};

static struct x_threading x_threading =
{
    {&x_threading_vtbl},
    0,
};

IXThreading *x_threading_impl = &x_threading.IXThreading_iface;
