//==========
// Page.cpp
//==========

#include "pch.h"


//=======
// Using
//=======

#include "Page.h"

using namespace Windows::UI::Xaml;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

Page::Page():
Content(this)
{
Content.Changed.Add(this, &Page::OnContentChanged);
hCallback=ref new Callback(this);
UIPage=ref new Windows::UI::Xaml::Controls::Page();
UIPage->Loaded+=ref new RoutedEventHandler(hCallback, &Callback::OnLoaded);
UIPage->Unloaded+=ref new RoutedEventHandler(hCallback, &Callback::OnUnloaded);
UIControl=UIPage;
}


//================
// Common Private
//================

VOID Page::OnContentChanged(Handle<Control> hctrl)
{
hContent=hctrl;
if(!hctrl)
	{
	UIPage->Content=nullptr;
	return;
	}
UIPage->Content=hctrl->UIControl;
}


//==================
// Callback Private
//==================

Page::Callback::Callback(Page* ppage):
pPage(ppage)
{}

VOID Page::Callback::OnLoaded(Platform::Object^ hsender, RoutedEventArgs^ hargs)
{
pPage->Loaded(pPage);
}

VOID Page::Callback::OnUnloaded(Platform::Object^ hsender, RoutedEventArgs^ hargs)
{
pPage->Unloaded(pPage);
}

}}