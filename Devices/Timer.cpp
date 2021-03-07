//===========
// Timer.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Timer.h"

using namespace Windows::System::Threading;


//===========
// Namespace
//===========

namespace Devices {


//==================
// Con-/Destructors
//==================

Timer::Timer()
{}


//========
// Common
//========

VOID Timer::Start(UINT uus)
{
Stop();
Handle<Timer> hthis=this;
TimeSpan time;
time.Duration=uus*10;
hTimer=ThreadPoolTimer::CreateTimer(ref new TimerElapsedHandler([hthis](ThreadPoolTimer^ htimer)
	{
	hthis->Triggered(hthis, hthis);
	}), time);
}

VOID Timer::StartPeriodic(UINT uus)
{
Stop();
Handle<Timer> hthis=this;
TimeSpan time;
time.Duration=uus*10;
hTimer=ThreadPoolTimer::CreatePeriodicTimer(ref new TimerElapsedHandler([hthis](ThreadPoolTimer^ htimer)
	{
	hthis->Triggered(hthis, hthis);
	}), time);
}

VOID Timer::Stop()
{
if(hTimer)
	{
	hTimer->Cancel();
	hTimer=nullptr;
	}
}

}