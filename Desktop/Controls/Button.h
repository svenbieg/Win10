//==========
// Button.h
//==========

#pragma once


//=======
// Using
//=======

#include "Control.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//========
// Button
//========

class Button: public Control
{
public:
	// Con-/Destructors
	Button();

	// Common
	Event<Button, Handle<Button>> Clicked;
	VariableHandle<Button, String> Text;
	Windows::UI::Xaml::Controls::Button^ UIButton;

private:
	// Common
	VOID OnTextChanged(Handle<String> Text);

	// Callback
	ref class Callback sealed
		{
		internal:
			// Using
			using RoutedEventArgs=Windows::UI::Xaml::RoutedEventArgs;

			// Con-/Destructors
			Callback(Button* Button): pButton(Button) {}

			// Common
			VOID OnClick(Platform::Object^ Sender, RoutedEventArgs^ Args);
			Button* pButton;
		};
	Callback^ hCallback;
};

}}