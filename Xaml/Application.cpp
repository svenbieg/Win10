//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Desktop/Application.h"
#include "Application.h"

using namespace Concurrency;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;

extern VOID Initialize();


//================
// Einstiegspunkt
//================

[Platform::MTAThread]
INT main(Platform::Array<Platform::String^>^ hargs)
{
Application::Start(ref new ApplicationInitializationCallback([](ApplicationInitializationCallbackParams^ hparams)
	{
	ref new Xaml::Application();
	}));
return 0;
}


//===========
// Namespace
//===========

namespace Xaml {


//========
// Common
//========

VOID Application::OnLaunched(LaunchActivatedEventArgs^ hargs)
{
}

VOID Application::OnWindowCreated(WindowCreatedEventArgs^ hargs)
{
Initialize();
create_task([this]()
	{
	while(1)
		{
		CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([]()
			{
			auto happ=Desktop::Application::Current;
			happ->Loop(happ);
			}));
		Sleep(10);
		}
	});
}


//============================
// Con-/Destructors Protected
//============================

Application::Application()
{
Suspending+=ref new Windows::UI::Xaml::SuspendingEventHandler(this, &Xaml::Application::OnSuspending);
}


//================
// Common Private
//================

VOID Application::OnSuspending(Platform::Object^ hsender, SuspendingEventArgs^ hargs)
{
auto happ=Desktop::Application::Current;
happ->Destroyed(happ);
ExitProcess(0);
}

}