//==============
// TimeHelper.h
//==============

#pragma once


//=======
// Using
//=======

using TimeSpan=Windows::Foundation::TimeSpan;


//========
// Common
//========

VOID Sleep(UINT Milliseconds, volatile BOOL* Cancel);
