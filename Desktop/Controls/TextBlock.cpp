//===============
// TextBlock.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "TextBlock.h"

using namespace Graphics;
using namespace Windows::UI::Text;
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
Color(this, Colors::Black),
Font(this),
FontSize(this, 15),
FontWeight(this, 300),
Text(this)
{
UITextBlock=ref new Windows::UI::Xaml::Controls::TextBlock();
UITextBlock->FontSize=15;
UIControl=UITextBlock;
Color.Changed.Add(this, &TextBlock::OnColorChanged);
Font.Changed.Add(this, &TextBlock::OnFontChanged);
FontSize.Changed.Add(this, &TextBlock::OnFontSizeChanged);
FontWeight.Changed.Add(this, &TextBlock::OnFontWeightChanged);
Text.Changed.Add(this, &TextBlock::OnTextChanged);
}


//================
// Common Private
//================

VOID TextBlock::OnColorChanged(COLOR c)
{
auto cui=ColorToUIColor(c);
UITextBlock->Foreground=ref new SolidColorBrush(cui);
}

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

VOID TextBlock::OnFontWeightChanged(UINT weight)
{
auto w=FontWeights::Normal;
w.Weight=weight;
UITextBlock->FontWeight=w;
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