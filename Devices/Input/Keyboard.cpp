//==============
// Keyboard.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Keyboard.h"

using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;


//===========
// Namespace
//===========

namespace Devices {
	namespace Input {


//==================
// Con-/Destructors
//==================

Keyboard::Keyboard()
{
auto hwnd=Window::Current->CoreWindow;
uKeyDownToken=hwnd->KeyDown+=ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &Keyboard::OnKeyDown);
uKeyUpToken=hwnd->KeyUp+=ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &Keyboard::OnKeyUp);
for(UINT u=0; u<256; u++)
	pKeys[u]=hwnd->GetKeyState((VirtualKey)u)==CoreVirtualKeyStates::Down;
}


//========
// Common
//========

BOOL Keyboard::IsKeyDown(BYTE ukey)
{
return pKeys[ukey];
}


//================
// Common Private
//================

Keyboard::~Keyboard()
{
auto hwnd=Window::Current->CoreWindow;
hwnd->KeyDown-=uKeyDownToken;
hwnd->KeyUp-=uKeyUpToken;
}

VOID Keyboard::OnKeyDown(CoreWindow^ hwnd, KeyEventArgs^ hargs)
{
UINT u=(UINT)hargs->VirtualKey;
if(u<256)
	pKeys[u]=true;
KeyDown(this, (BYTE)hargs->VirtualKey);
}

VOID Keyboard::OnKeyUp(CoreWindow^ hwnd, KeyEventArgs^ hargs)
{
UINT u=(UINT)hargs->VirtualKey;
if(u<256)
	pKeys[u]=false;
KeyUp(this, (BYTE)hargs->VirtualKey);
}

}}
