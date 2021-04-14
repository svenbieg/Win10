//=================
// PasswordBox.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "PasswordBox.h"

using namespace Windows::UI::Xaml;
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

PasswordBox::PasswordBox():
Font(this),
FontSize(this, 15),
Text(this),
hCallback(ref new Callback(this))
{
UIPasswordBox=ref new Windows::UI::Xaml::Controls::PasswordBox();
UIPasswordBox->PasswordChanged+=ref new Windows::UI::Xaml::RoutedEventHandler(hCallback, &Callback::OnPasswordChanged);
UIPasswordBox->FontSize=15;
Initialize(UIPasswordBox);
Font.Changed.Add(this, &PasswordBox::OnFontChanged);
FontSize.Changed.Add(this, &PasswordBox::OnFontSizeChanged);
Text.Changed.Add(this, &PasswordBox::OnTextChanged);
}


//================
// Common Private
//================

VOID PasswordBox::OnFontChanged(Handle<String> hfont)
{
if(!hfont)
	{
	UIPasswordBox->FontFamily=nullptr;
	return;
	}
UIPasswordBox->FontFamily=ref new FontFamily(Platform::StringReference(hfont->Begin()));
}

VOID PasswordBox::OnFontSizeChanged(UINT usize)
{
UIPasswordBox->FontSize=usize;
}

VOID PasswordBox::OnTextChanged(Handle<String> htext)
{
if(!htext)
	{
	UIPasswordBox->Password=nullptr;
	return;
	}
UIPasswordBox->Password=ref new Platform::String(htext->Begin());
}


//==================
// Callback Private
//==================

VOID PasswordBox::Callback::OnPasswordChanged(Platform::Object^ sender, RoutedEventArgs^ args)
{
auto text=pPasswordBox->UIPasswordBox->Password->Begin();
pPasswordBox->Text.SetInternal(text);
pPasswordBox->TextChanged(pPasswordBox);
}

}}