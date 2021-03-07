//============
// Button.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Button.h"

using namespace Windows::UI::Xaml::Controls;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

Button::Button():
Text(this),
hCallback(ref new Callback(this))
{
UIButton=ref new Windows::UI::Xaml::Controls::Button();
UIButton->Click+=ref new Windows::UI::Xaml::RoutedEventHandler(hCallback, &Callback::OnClick);
UIControl=UIButton;
Text.Changed.Add(this, &Button::OnTextChanged);
}


//================
// Common Private
//================

VOID Button::OnTextChanged(Handle<String> htext)
{
if(!htext)
	{
	UIButton->Content=nullptr;
	return;
	}
auto hres=GetResourceString(htext);
if(hres)
	htext=hres;
auto htextblock=ref new TextBlock();
htextblock->Text=ref new Platform::String(htext->Begin());
UIButton->Content=htextblock;
}


//==================
// Callback Private
//==================

VOID Button::Callback::OnClick(Platform::Object^ hsender, RoutedEventArgs^ hargs)
{
pButton->Clicked(pButton, pButton);
}

}}