//================
// TimeHelper.cpp
//================

#include "pch.h"


//========
// Common
//========

VOID Sleep(UINT ms, volatile BOOL* pcancel)
{
if(!pcancel)
	{
	Sleep(ms);
	return;
	}
UINT count=ms/10;
for(UINT u=0; u<count; u++)
	{
	Sleep(10);
	if(*pcancel)
		return;
	}
}
