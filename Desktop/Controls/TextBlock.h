//=============
// TextBlock.h
//=============

#pragma once


//=======
// Using
//=======

#include "Graphics/Color.h"
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
	Property<TextBlock, Graphics::COLOR> Color;
	VariableHandle<TextBlock, String> Font;
	Property<TextBlock, UINT> FontSize;
	Property<TextBlock, UINT> FontWeight;
	VariableHandle<TextBlock, String> Text;
	Windows::UI::Xaml::Controls::TextBlock^ UITextBlock;

private:
	// Common
	VOID OnColorChanged(Graphics::COLOR Color);
	VOID OnFontChanged(Handle<String> Font);
	VOID OnFontSizeChanged(UINT Size);
	VOID OnFontWeightChanged(UINT Weight);
	VOID OnTextChanged(Handle<String> Text);
};

}}