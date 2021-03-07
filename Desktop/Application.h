//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Core/Application.h"


//===========
// Namespace
//===========

namespace Desktop {


//=============
// Application
//=============

class Application: public ::Core::Application
{
private:
	// Using
	using CoreApplication=Windows::ApplicationModel::Core::CoreApplication;
	using CoreDispatcherPriority=Windows::UI::Core::CoreDispatcherPriority;
	using DispatchedHandler=Windows::UI::Core::DispatchedHandler;
	using Window=Windows::UI::Xaml::Window;

public:
	// Con-/Destructors
	Application(Handle<String> Name);

	// Common
	static Handle<Application> Current;
	template <class _owner_t> VOID Dispatch(_owner_t* Owner, VOID (_owner_t::*Procedure)())
		{
		Handle<_owner_t> howner=Owner;
		CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([howner, Procedure]()
			{
			(howner->*Procedure)();
			}));
		}
};

}