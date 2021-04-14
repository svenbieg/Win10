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
DoLoop();
}


//============================
// Con-/Destructors Protected
//============================

Application::Application()
{
Suspending+=ref new SuspendingEventHandler(this, &Application::OnSuspending);
UnhandledException+=ref new UnhandledExceptionEventHandler(this, &Application::OnUnhandledException);
}


//================
// Common Private
//================

VOID Application::DoLoop()
{
create_task(CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]()
	{
	ScopedLock lock(cCriticalSection);
	auto happ=Desktop::Application::Current;
	happ->Loop(happ);
	}))).then([this]()
	{
	DoLoop();
	});
}

VOID Application::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
auto happ=Desktop::Application::Current;
happ->Destroyed(happ);
ExitProcess(0);
}

VOID Application::OnUnhandledException(Platform::Object^ sender, UnhandledExceptionEventArgs^ args)
{
args->Handled=true;
}

}