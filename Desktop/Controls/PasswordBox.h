//===============
// PasswordBox.h
//===============

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


//==============
// Password-Box
//==============

class PasswordBox: public Control
{
public:
	// Con-/Destructors
	PasswordBox();

	// Common
	VariableHandle<PasswordBox, String> Font;
	Property<PasswordBox, UINT> FontSize;
	VariableHandle<PasswordBox, String> Text;
	Event<PasswordBox> TextChanged;
	Windows::UI::Xaml::Controls::PasswordBox^ UIPasswordBox;

private:
	// Common
	VOID OnFontChanged(Handle<String> Font);
	VOID OnFontSizeChanged(UINT Size);
	VOID OnTextChanged(Handle<String> Text);

	// Callback
	ref class Callback sealed
		{
		internal:
			// Con-/Destructors
			Callback(PasswordBox* PasswordBox): pPasswordBox(PasswordBox) {}

			// Common
			VOID OnPasswordChanged(Platform::Object^ Sender, Windows::UI::Xaml::RoutedEventArgs^ Args);
			PasswordBox* pPasswordBox;
		};
	Callback^ hCallback;
};

}}