//===============
// AppWindow.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "AppWindow.h"

using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;


//===========
// Namespace
//===========

namespace Desktop {


//==================
// Con-/Destructors
//==================

AppWindow::AppWindow():
hCallback(ref new Callback(this))
{
Canvas=ref new Windows::UI::Xaml::Controls::Canvas();
Color c;
c.R=0xF0;
c.G=0xF0;
c.B=0xF0;
c.A=0xFF;
Canvas->Background=ref new SolidColorBrush(c);
Canvas->Height=Window::Current->Bounds.Height;
Canvas->Width=Window::Current->Bounds.Width;
UIControl=Canvas;
UIPanel=Canvas;
Window::Current->Content=Canvas;
Window::Current->Activate();
}


//==================
// Callback Private
//==================

AppWindow::Callback::Callback(AppWindow* pappwnd):
pAppWindow(pappwnd)
{
Window::Current->Activated+=ref new WindowActivatedEventHandler(this, &Callback::OnActivated);
Window::Current->SizeChanged+=ref new WindowSizeChangedEventHandler(this, &Callback::OnSizeChanged);
}

VOID AppWindow::Callback::OnActivated(Platform::Object^ hsender, WindowActivatedEventArgs^ hargs)
{
pAppWindow->Activated(pAppWindow);
}

VOID AppWindow::Callback::OnSizeChanged(Platform::Object^ hsender, WindowSizeChangedEventArgs^ hargs)
{
pAppWindow->Canvas->Width=hargs->Size.Width;
pAppWindow->Canvas->Height=hargs->Size.Height;
Graphics::RECT rc({ 0, 0, (INT)hargs->Size.Width, (INT)hargs->Size.Height });
pAppWindow->SizeChanged(pAppWindow, pAppWindow, rc);
}

}