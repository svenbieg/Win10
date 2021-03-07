//=========
// Mouse.h
//=========

#pragma once


//===========
// Namespace
//===========

namespace Devices {
	namespace Input {


//======================
// Forward-Declarations
//======================

ref class Mouse;


//====================
// Mouse-Button-Event
//====================

ref class MouseButtonEventArgs
{
internal:
	// Con-/Destructors
	MouseButtonEventArgs(const POINT& Point) : Point(Point) {}

	// Common
	const POINT& Point;
};

delegate VOID MouseButtonHandler(Mouse^ Sender, MouseButtonEventArgs^ Args);


//===================
// Mouse-Wheel-Event
//===================

ref class MouseWheelEventArgs
{
internal:
	// Con-/Destructors
	MouseWheelEventArgs(const POINT& Point, INT Delta) : Delta(Delta), Point(Point) {}

	// Common
	const INT Delta;
	const POINT& Point;
};

delegate VOID MouseWheelHandler(Mouse^ Sender, MouseWheelEventArgs^ Args);


//=======
// Mouse
//=======

ref class Mouse sealed
{
private:
	// Using
	using CoreWindow=Windows::UI::Core::CoreWindow;
	using PointerEventArgs=Windows::UI::Core::PointerEventArgs;

internal:
	// Con-/Destructors
	Mouse();

	// Common
	property BOOL IsLButtonDown { inline BOOL get() { return GetFlag(uFlags, MouseFlags::LButton); }}
	property BOOL IsMButtonDown { inline BOOL get() { return GetFlag(uFlags, MouseFlags::MButton); }}
	property BOOL IsRButtonDown { inline BOOL get() { return GetFlag(uFlags, MouseFlags::RButton); }}
	event MouseButtonHandler^ LButtonDown;
	event MouseButtonHandler^ LButtonUp;
	event MouseButtonHandler^ MButtonDown;
	event MouseButtonHandler^ MButtonUp;
	event MouseButtonHandler^ RButtonDown;
	event MouseButtonHandler^ RButtonUp;
	event MouseWheelHandler^ WheelChanged;

private:
	// Flags
	enum class MouseFlags: UINT
		{
		None=0,
		LButton=1,
		MButton=2,
		RButton=4
		};

	// Con-/Destructors
	~Mouse();

	// Common
	VOID OnPointerPressed(CoreWindow^ Sender, PointerEventArgs^ Args);
	VOID OnPointerReleased(CoreWindow^ Sender, PointerEventArgs^ Args);
	VOID OnPointerWheelChanged(CoreWindow^ Sender, PointerEventArgs^ Args);
	MouseFlags uFlags;
	EventToken uPointerPressedToken;
	EventToken uPointerReleasedToken;
	EventToken uPointerWheelChangedToken;
};

}}
