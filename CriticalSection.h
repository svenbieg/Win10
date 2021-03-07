//===================
// CriticalSection.h
//===================

#pragma once


//=======
// Using
//=======

#include <concrt.h>


//==================
// Critical Section
//==================

class CriticalSection
{
public:
	// Con-/Destructors
	CriticalSection() {}

	// Common
	VOID Lock() { cCriticalSection.lock(); }
	BOOL TryLock() { return cCriticalSection.try_lock(); }
	VOID Unlock() { cCriticalSection.unlock(); }

private:
	// Common
	Concurrency::critical_section cCriticalSection;
};
