//==============
// MainMenu.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "MainMenu.h"
#include "PopupMenu.h"

using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//==================
// Con-/Destructors
//==================

MainMenu::MainMenu(Handle<Panel> hparent):
Menu(hparent->UIControl),
hParent(hparent)
{
hCallback=ref new Callback(this);
StackPanel=ref new Windows::UI::Xaml::Controls::StackPanel();
StackPanel->Background=ref new SolidColorBrush(Colors::Transparent);
hParent->UIPanel->Children->Append(StackPanel);
}


//========
// Common
//========

Handle<MenuItem> MainMenu::Add(Handle<String> htext)
{
Handle<MenuItem> hitem=new MenuItem(this, htext);
auto hbtn=ref new Button();
hbtn->AccessKey=hitem->AccessKey;
hbtn->AccessKeyInvoked+=ref new TypedEventHandler<UIElement^, AccessKeyInvokedEventArgs^>(hCallback, &Callback::OnButtonAccessKeyInvoked);
hbtn->Background=StackPanel->Background;
hbtn->Click+=ref new RoutedEventHandler(hCallback, &Callback::OnButtonClick);
hbtn->Content=ref new Platform::String(hitem->Text->Begin());
StackPanel->Children->Append(hbtn);
return hitem;
}


//================
// Common Private
//================

VOID MainMenu::OnParentSizeChanged(Handle<Control> hparent, Graphics::RECT& rc)
{
StackPanel->SetValue(Canvas::LeftProperty, rc.Left);
StackPanel->SetValue(Canvas::TopProperty, rc.Top);
StackPanel->Width=rc.Right-rc.Left;
StackPanel->Height=StackPanel->DesiredSize.Height;
rc.Top+=(INT)StackPanel->Height;
}

VOID MainMenu::ShowMenu(Button^ hbtn)
{
auto hstr=dynamic_cast<Platform::String^>(hbtn->Content);
auto hitem=Items->Get(hstr->Begin());
auto hmenu=hitem->SubMenu;
if(!hmenu)
	return;
Windows::Foundation::Point pt;
pt.X=hbtn->ActualOffset.x;
pt.Y=StackPanel->DesiredSize.Height;
hmenu->MenuFlyout->ShowAt(Parent, pt);
}


//==================
// Callback Private
//==================

MainMenu::Callback::Callback(MainMenu* pmm):
pMainMenu(pmm)
{}

VOID MainMenu::Callback::OnButtonAccessKeyInvoked(UIElement^ hsender, AccessKeyInvokedEventArgs^ hargs)
{
auto hbtn=dynamic_cast<Button^>(hsender);
pMainMenu->ShowMenu(hbtn);
}

VOID MainMenu::Callback::OnButtonClick(Platform::Object^ hsender, RoutedEventArgs^ hargs)
{
auto hbtn=dynamic_cast<Button^>(hsender);
pMainMenu->ShowMenu(hbtn);
}

}}}