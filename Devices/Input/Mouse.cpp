//===========
// Mouse.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Mouse.h"

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

Mouse::Mouse():
uFlags(MouseFlags::None)
{
auto hwnd=Window::Current->CoreWindow;
uPointerPressedToken=hwnd->PointerPressed+=ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Mouse::OnPointerPressed);
uPointerReleasedToken=hwnd->PointerPressed+=ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Mouse::OnPointerReleased);
uPointerWheelChangedToken=hwnd->PointerWheelChanged+=ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Mouse::OnPointerWheelChanged);
}


//==========================
// Con-/Destructors Private
//==========================

Mouse::~Mouse()
{
auto hwnd=Window::Current->CoreWindow;
hwnd->PointerPressed-=uPointerPressedToken;
hwnd->PointerReleased-=uPointerReleasedToken;
hwnd->PointerWheelChanged-=uPointerWheelChangedToken;
}


//================
// Common Private
//================

VOID Mouse::OnPointerPressed(CoreWindow^ hsender, PointerEventArgs^ hargs)
{
auto pos=hargs->CurrentPoint->Position;
auto hmouseargs=ref new MouseButtonEventArgs({ (LONG)pos.X, (LONG)pos.Y });
if(hargs->CurrentPoint->Properties->IsLeftButtonPressed)
	{
	SetFlag(uFlags, MouseFlags::LButton);
	LButtonDown(this, hmouseargs);
	return;
	}
if(hargs->CurrentPoint->Properties->IsMiddleButtonPressed)
	{
	SetFlag(uFlags, MouseFlags::MButton);
	MButtonDown(this, hmouseargs);
	return;
	}
if(hargs->CurrentPoint->Properties->IsRightButtonPressed)
	{
	SetFlag(uFlags, MouseFlags::RButton);
	RButtonDown(this, hmouseargs);
	return;
	}
}

VOID Mouse::OnPointerReleased(CoreWindow^ hsender, PointerEventArgs^ hargs)
{
auto pos=hargs->CurrentPoint->Position;
auto hmouseargs=ref new MouseButtonEventArgs({ (LONG)pos.X, (LONG)pos.Y });
if(GetFlag(uFlags, MouseFlags::LButton))
	{
	ClearFlag(uFlags, MouseFlags::LButton);
	LButtonUp(this, hmouseargs);
	return;
	}
if(hargs->CurrentPoint->Properties->IsMiddleButtonPressed)
	{
	ClearFlag(uFlags, MouseFlags::MButton);
	MButtonUp(this, hmouseargs);
	return;
	}
if(hargs->CurrentPoint->Properties->IsRightButtonPressed)
	{
	ClearFlag(uFlags, MouseFlags::RButton);
	RButtonUp(this, hmouseargs);
	return;
	}
}

VOID Mouse::OnPointerWheelChanged(CoreWindow^ hsender, PointerEventArgs^ hargs)
{
auto pos=hargs->CurrentPoint->Position;
auto hmouseargs=ref new MouseWheelEventArgs({ (LONG)pos.X, (LONG)pos.Y }, hargs->CurrentPoint->Properties->MouseWheelDelta);
WheelChanged(this, hmouseargs);
}

}}
