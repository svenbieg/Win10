//===============
// PopupMenu.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "PopupMenu.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//==================
// Con-/Destructors
//==================

PopupMenu::PopupMenu(UIElement^ hparent):
Menu(hparent)
{
hCallback=ref new Callback(this);
MenuFlyout=ref new Windows::UI::Xaml::Controls::MenuFlyout();
}


//========
// Common
//========

Handle<MenuItem> PopupMenu::Add(Handle<String> htext)
{
Handle<MenuItem> hitem=new MenuItem(this, htext);
auto hbtn=ref new MenuFlyoutItem();
hbtn->AccessKey=hitem->AccessKey;
hbtn->AccessKeyInvoked+=ref new TypedEventHandler<UIElement^, AccessKeyInvokedEventArgs^>(hCallback, &Callback::OnButtonAccessKeyInvoked);
hbtn->Click+=ref new RoutedEventHandler(hCallback, &Callback::OnButtonClick);
hbtn->Text=ref new Platform::String(hitem->Text->Begin());
MenuFlyout->Items->Append(hbtn);
return hitem;
}


//================
// Common Private
//================

VOID PopupMenu::HandleItem(MenuFlyoutItem^ hbtn)
{
auto hitem=Items->Get(hbtn->Text->Begin());
auto hmenu=hitem->SubMenu;
if(!hmenu)
	return;
Windows::Foundation::Point pt;
pt.X=hbtn->ActualOffset.x+(FLOAT)hbtn->ActualWidth;
pt.Y=hbtn->ActualOffset.y;
hmenu->MenuFlyout->ShowAt(Parent, pt);
}


//==================
// Callback Private
//==================

PopupMenu::Callback::Callback(PopupMenu* pmenu):
pPopupMenu(pmenu)
{}

VOID PopupMenu::Callback::OnButtonAccessKeyInvoked(UIElement^ hsender, AccessKeyInvokedEventArgs^ hargs)
{
auto hbtn=dynamic_cast<MenuFlyoutItem^>(hsender);
pPopupMenu->HandleItem(hbtn);
}

VOID PopupMenu::Callback::OnButtonClick(Platform::Object^ hsender, RoutedEventArgs^ hargs)
{
auto hbtn=dynamic_cast<MenuFlyoutItem^>(hsender);
pPopupMenu->HandleItem(hbtn);
}

}}}