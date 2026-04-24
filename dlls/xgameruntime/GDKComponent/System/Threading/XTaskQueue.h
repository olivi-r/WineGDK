/*
 * Xbox Game runtime Library
 *  GDK Component: System API -> XTask
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

#ifndef XTASKQUEUE_H
#define XTASKQUEUE_H

#include "../../../private.h"

#include "XOSThreading.h"
#include "AtomicVector.h"
#include "ThreadPool.h"

static const UINT32 TASK_QUEUE_SIGNATURE = 0x41515545;
static const UINT32 TASK_QUEUE_PORT_SIGNATURE = 0x41515553;

typedef enum TerminationLevel
{
    TerminationLevel_None,
    TerminationLevel_Work,
    TerminationLevel_Completion
} TerminationLevel;

typedef struct XMonitor
{
    PVOID context;
    UINT64 token;
    XTaskQueueMonitorCallback *callback;
    struct XMonitor *next;
} XMonitor;

typedef struct XQueue
{
    IXTaskQueuePortContext* portContext;
    PVOID callbackContext;
    XTaskQueueCallback* callback;
    UINT64 enqueueTime;
    UINT64 id;
    struct XQueue* next;
} XQueue;

typedef struct XTerminateForPort
{
    IXTaskQueuePortContext* portContext;
    PVOID callbackContext;
    XTaskQueueTerminatedCallback* callback;
    UINT64 node;
    struct XTerminateForPort* next;
} XTerminateForPort;

typedef struct XTerminate
{
    IXTaskQueue* owner;
    TerminationLevel level;
    PVOID completionPortToken;
    PVOID context;
    XTaskQueueTerminatedCallback* callback;
    struct XTerminate* next;
} XTerminate;

typedef struct XWait
{
    UINT64 Token;
    UINT64 PortToken;
    XTaskQueuePort Port; 
} XWait;

typedef struct XTerminateData
{
    BOOLEAN allowed;
    BOOLEAN terminated;
    CRITICAL_SECTION cs;
    CONDITION_VARIABLE cv;
} XTerminateData;

// Backwards decleration of XTaskQueueObject
typedef struct XTaskQueueObject
{
    UINT32 signature;
    IXTaskQueue *headQueue;
} XTaskQueueObject;

// Backwards decleration of XTaskQueuePortObject
typedef struct XTaskQueuePortObject
{
    UINT32 signature;
    IXTaskQueuePort *headPort;
    IXTaskQueue *headQueue;
} XTaskQueuePortObject;

struct x_task_queue_monitor_callback
{
    IXTaskQueueMonitorCallback IXTaskQueueMonitorCallback_iface;
    UINT32 monitors_size;
    CRITICAL_SECTION cs;
    XMonitor *monitors_tail, *monitors_head;
    XTaskQueueHandle queue;
    LONG ref;
};

struct x_task_queue_port
{
    IXTaskQueuePort IXTaskQueuePort_iface;
    XTaskQueuePortObject portHeader;
    XTaskQueueDispatchMode dispatchMode;
    IAtomicVector *attachedContexts;
    LONG processingCallback;
    CONDITION_VARIABLE cv;
    CONDITION_VARIABLE cvAny;
    CRITICAL_SECTION cs;
    XQueue *queueList_tail, *queueList_head;
    XQueue *pendingQueueList_tail, *pendingQueueList_head;
    XTerminateForPort *terminateList_tail, *terminateList_head;
    XTerminateForPort *pendingTerminateList_tail, *pendingTerminateList_head;
    IXWaitTimer *timer;
    IThreadPool *threadPool;
    LONG64 timerDue;
    LONG nextId;
    BOOLEAN signaled;
    BOOL suspended;
    LONG ref;
};

struct x_task_queue_port_context
{
    IXTaskQueuePortContext IXTaskQueuePortContext_iface;
    IXTaskQueuePort *port;
    IXTaskQueue *source;

    XTaskQueuePort type;
    XTaskQueuePortStatus status;
    IXTaskQueue *queue;
    IXTaskQueueMonitorCallback *callbackSubmitted;
    LONG suspendCount;
    LONG ref;
};

struct x_task_queue
{
    IXTaskQueue IXTaskQueue_iface;

    XTaskQueueObject queueHeader;
    IXTaskQueueMonitorCallback *callbackSubmitted;
    IXTaskQueueWaitCallback *waitRegistry;
    XTerminateData terminationData;
    IXTaskQueuePortContext *workPort;
    IXTaskQueuePortContext *completionPort;
    BOOLEAN allowClose;
    LONG ref;
};

struct x_task_queue_wait_callback
{
    IXTaskQueueWaitCallback IXTaskQueueWaitCallback_iface;
    UINT64 nextToken;
    XWait callbacks[120];
    CRITICAL_SECTION cs;
    LONG ref;
};

HRESULT XTaskQueueCreate( XTaskQueueDispatchMode workDispatchMode, XTaskQueueDispatchMode completionDispatchMode, XTaskQueueHandle* queue );
HRESULT XTaskQueueGetPort( XTaskQueueHandle queue, XTaskQueuePort port, XTaskQueuePortHandle* portHandle );
HRESULT XTaskQueueCreateComposite( XTaskQueuePortHandle workPort, XTaskQueuePortHandle completionPort, XTaskQueueHandle* queue );
BOOLEAN XTaskQueueDispatch( XTaskQueueHandle queue, XTaskQueuePort port, UINT32 timeoutInMs );
VOID XTaskQueueCloseHandle( XTaskQueueHandle queue );
HRESULT XTaskQueueTerminate( XTaskQueueHandle queue, BOOLEAN wait, PVOID callbackContext, XTaskQueueTerminatedCallback* callback );
HRESULT XTaskQueueSubmitDelayedCallback( XTaskQueueHandle queue, XTaskQueuePort port, UINT32 delayMs, PVOID callbackContext, XTaskQueueCallback* callback );
HRESULT XTaskQueueDuplicateHandle( XTaskQueueHandle queue, XTaskQueueHandle* duplicatedHandle );
HRESULT XTaskQueueRegisterMonitor( XTaskQueueHandle queue, PVOID callbackContext, XTaskQueueMonitorCallback* callback, XTaskQueueRegistrationToken* token );
VOID XTaskQueueResumeTermination( XTaskQueueHandle queue );

#endif