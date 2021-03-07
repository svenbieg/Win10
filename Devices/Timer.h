//=========
// Timer.h
//=========

#pragma once


//===========
// Namespace
//===========

namespace Devices {


//=======
// Timer
//=======

class Timer: public Object
{
private:
	// Using
	using ThreadPoolTimer=Windows::System::Threading::ThreadPoolTimer;

public:
	// Con-/Destructors
	Timer();

	// Common
	VOID Start(UINT Micros);
	VOID StartPeriodic(UINT Micros);
	VOID Stop();
	Event<Timer, Handle<Timer>> Triggered;

private:
	// Common
	ThreadPoolTimer^ hTimer;
};

}