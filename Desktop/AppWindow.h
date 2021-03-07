//=============
// AppWindow.h
//=============

#pragma once


//=======
// Using
//=======

#include "Controls/Panel.h"


//===========
// Namespace
//===========

namespace Desktop {


//============
// App-Window
//============

class AppWindow: public Desktop::Controls::Panel
{
private:
	// Using
	using WindowActivatedEventArgs=Windows::UI::Core::WindowActivatedEventArgs;
	using WindowSizeChangedEventArgs=Windows::UI::Core::WindowSizeChangedEventArgs;

protected:
	// Con-/Destructors
	AppWindow();

	// Common
	Event<AppWindow> Activated;
	Windows::UI::Xaml::Controls::Canvas^ Canvas;

private:
	// Callback
	ref class Callback
		{
		internal:
			// Con-/Destructors
			Callback(AppWindow* AppWindow);

		private:
			// Common
			VOID OnActivated(Platform::Object^ Sender, WindowActivatedEventArgs^ Args);
			VOID OnSizeChanged(Platform::Object^ Sender, WindowSizeChangedEventArgs^ Args);
			AppWindow* pAppWindow;
		};
	Callback^ hCallback;
};

}