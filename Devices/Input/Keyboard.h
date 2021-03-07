//============
// Keyboard.h
//============

#pragma once


//===========
// Namespace
//===========

namespace Devices {
	namespace Input {


//======================
// Forward-Declarations
//======================

ref class Keyboard;


//========
// Events
//========

delegate VOID KeyboardKeyDownHandler(Keyboard^ Sender, BYTE Key);
delegate VOID KeyboardKeyUpHandler(Keyboard^ Sender, BYTE Key);


//==========
// Keyboard
//==========

ref class Keyboard sealed
{
private:
	// Using
	using CoreWindow=Windows::UI::Core::CoreWindow;
	using KeyEventArgs=Windows::UI::Core::KeyEventArgs;

internal:
	// Con-/Destructors
	Keyboard();

	// Common
	BOOL IsKeyDown(BYTE Key);
	event KeyboardKeyDownHandler^ KeyDown;
	event KeyboardKeyUpHandler^ KeyUp;

private:
	// Con-/Destructors
	~Keyboard();

	// Common
	VOID OnKeyDown(CoreWindow^ Window, KeyEventArgs^ Args);
	VOID OnKeyUp(CoreWindow^ Window, KeyEventArgs^ Args);
	BYTE pKeys[256];
	EventToken uKeyDownToken;
	EventToken uKeyUpToken;
};

}}
