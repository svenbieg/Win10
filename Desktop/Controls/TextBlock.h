//=============
// TextBlock.h
//=============

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


//============
// Text-Block
//============

class TextBlock: public Control
{
public:
	// Con-/Destructors
	TextBlock();

	// Common
	VariableHandle<TextBlock, String> Font;
	Property<TextBlock, UINT> FontSize;
	VariableHandle<TextBlock, String> Text;
	Windows::UI::Xaml::Controls::TextBlock^ UITextBlock;

private:
	// Common
	VOID OnFontChanged(Handle<String> Font);
	VOID OnFontSizeChanged(UINT Size);
	VOID OnTextChanged(Handle<String> Text);
};

}}