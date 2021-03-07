//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Desktop/Application.h"
#include "Application.h"

using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;

extern VOID Initialize();


//================
// Einstiegspunkt
//================

/*[Platform::MTAThread]
INT main(Platform::Array<Platform::String^>^ hargs)
{
auto hviewsource=ref new Xaml::FrameworkViewSource();
CoreApplication::Run(hviewsource);
return 0;
}*/


//===========
// Namespace
//===========

namespace Framework {


//=====================
// FrameworkViewSource
//=====================

Windows::ApplicationModel::Core::IFrameworkView^ FrameworkViewSource::CreateView()
{
return ref new FrameworkView();
}


//===============
// FrameworkView
//===============

VOID FrameworkView::Initialize(CoreApplicationView^ hview)
{
CoreApplication::Suspending+=ref new Windows::Foundation::EventHandler<SuspendingEventArgs^>(this, &FrameworkView::OnSuspending);
}

VOID FrameworkView::Load(Platform::String^ hentrypoint)
{
}

VOID FrameworkView::Run()
{
auto happ=Desktop::Application::Current;
auto hwnd=CoreWindow::GetForCurrentThread();
while(1)
	{
	hwnd->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
	happ->Loop(happ);
	}
}

VOID FrameworkView::SetWindow(CoreWindow^ hwnd)
{
hwnd->Activate();
}

VOID FrameworkView::Uninitialize()
{
}


//========================
// FrameworkView Internal
//========================

VOID FrameworkView::OnSuspending(Platform::Object^ hsender, SuspendingEventArgs^ hargs)
{
auto happ=Desktop::Application::Current;
happ->Destroyed(happ);
ExitProcess(0);
}

}