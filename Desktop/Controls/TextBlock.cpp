//===============
// TextBlock.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "TextBlock.h"

using namespace Windows::UI::Xaml::Media;

//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

TextBlock::TextBlock():
Font(this),
FontSize(this, 15),
Text(this)
{
UITextBlock=ref new Windows::UI::Xaml::Controls::TextBlock();
UITextBlock->FontSize=15;
UIControl=UITextBlock;
Font.Changed.Add(this, &TextBlock::OnFontChanged);
FontSize.Changed.Add(this, &TextBlock::OnFontSizeChanged);
Text.Changed.Add(this, &TextBlock::OnTextChanged);
}


//================
// Common Private
//================

VOID TextBlock::OnFontChanged(Handle<String> hfont)
{
if(!hfont)
	{
	UITextBlock->FontFamily=nullptr;
	return;
	}
UITextBlock->FontFamily=ref new FontFamily(Platform::StringReference(hfont->Begin()));
}

VOID TextBlock::OnFontSizeChanged(UINT usize)
{
UITextBlock->FontSize=usize;
}

VOID TextBlock::OnTextChanged(Handle<String> htext)
{
if(!htext)
	{
	UITextBlock->Text=nullptr;
	return;
	}
auto hres=GetResourceString(htext);
if(hres)
	htext=hres;
UITextBlock->Text=ref new Platform::String(htext->Begin());
}

}}