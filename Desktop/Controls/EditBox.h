//===========
// EditBox.h
//===========

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


//==========
// Edit-Box
//==========

class EditBox: public Control
{
public:
	// Con-/Destructors
	EditBox();

	// Common
	Event<EditBox> Changed;
	VariableHandle<EditBox, String> Font;
	Property<EditBox, UINT> FontSize;
	VariableHandle<EditBox, String> Text;
	Windows::UI::Xaml::Controls::TextBox^ UITextBox;

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
			Callback(EditBox* EditBox): pEditBox(EditBox) {}

			// Common
			VOID OnTextChanged(Platform::Object^ Sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ Args);
			EditBox* pEditBox;
		};
	Callback^ hCallback;
};

}}