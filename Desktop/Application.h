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
	using CoreDispatcher=Windows::UI::Core::CoreDispatcher;
	using CoreDispatcherPriority=Windows::UI::Core::CoreDispatcherPriority;
	using DispatchedHandler=Windows::UI::Core::DispatchedHandler;
	using Window=Windows::UI::Xaml::Window;

public:
	// Con-/Destructors
	Application(Handle<String> Name);

	// Common
	static Handle<Application> Current;
	template <class _owner_t, class... _args_t> VOID Dispatch(_owner_t* Owner, VOID (_owner_t::*Procedure)(_args_t...), _args_t... Arguments)
		{
		CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([Owner, Procedure, Arguments...]()
			{
			(Owner->*Procedure)(Arguments...);
			}));
		}
};

}