//=============
// EditBox.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "EditBox.h"

using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

EditBox::EditBox():
Font(this),
FontSize(this, 15),
Text(this),
hCallback(ref new Callback(this))
{
UITextBox=ref new Windows::UI::Xaml::Controls::TextBox();
UITextBox->TextChanged+=ref new Windows::UI::Xaml::Controls::TextChangedEventHandler(hCallback, &Callback::OnTextChanged);
UITextBox->FontSize=15;
Initialize(UITextBox);
Font.Changed.Add(this, &EditBox::OnFontChanged);
FontSize.Changed.Add(this, &EditBox::OnFontSizeChanged);
Text.Changed.Add(this, &EditBox::OnTextChanged);
}


//================
// Common Private
//================

VOID EditBox::OnFontChanged(Handle<String> hfont)
{
if(!hfont)
	{
	UITextBox->FontFamily=nullptr;
	return;
	}
UITextBox->FontFamily=ref new FontFamily(Platform::StringReference(hfont->Begin()));
}

VOID EditBox::OnFontSizeChanged(UINT usize)
{
UITextBox->FontSize=usize;
}

VOID EditBox::OnTextChanged(Handle<String> htext)
{
if(!htext)
	{
	UITextBox->Text=nullptr;
	return;
	}
UITextBox->Text=ref new Platform::String(htext->Begin());
}


//==================
// Callback Private
//==================

VOID EditBox::Callback::OnTextChanged(Platform::Object^ sender, TextChangedEventArgs^ args)
{
auto text=pEditBox->UITextBox->Text->Begin();
pEditBox->Text.SetInternal(text);
pEditBox->Changed(pEditBox);
}

}}