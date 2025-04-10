/// Routines for synchronizing threads.
///
/// The implementation for this primitive does not come with base Nachos.
/// It is left to the student.
///
/// When implementing this module, keep in mind that any implementation of a
/// synchronization routine needs some primitive atomic operation.  The
/// semaphore implementation, for example, disables interrupts in order to
/// achieve this; another way could be leveraging an already existing
/// primitive.
///
/// Copyright (c) 1992-1993 The Regents of the University of California.
///               2016-2021 Docentes de la Universidad Nacional de Rosario.
/// All rights reserved.  See `copyright.h` for copyright notice and
/// limitation of liability and disclaimer of warranty provisions.


#include "lock.hh"  

#include<stdio.h>


/// Dummy functions -- so we can compile our later assignments.

Lock::Lock(const char *debugName)
{
    lock = new Semaphore(debugName, 1);
}

Lock::~Lock()
{
    delete lock;
}

const char *
Lock::GetName() const
{
    return name;
}

void
Lock::Acquire()
{
    if (!IsHeldByCurrentThread()) 
    {
        lock->P();
        currentPid = getpid();
        DEBUG('t', "Lock acquired by %d\n", currentPid);

    }
}

void
Lock::Release()
{
    if (IsHeldByCurrentThread()) 
    {

        lock->V();
        currentPid = -1;

    }
}

bool
Lock::IsHeldByCurrentThread() const
{
    return currentPid == getpid();
}
