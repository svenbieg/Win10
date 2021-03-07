//========
// Page.h
//========

#pragma once


//=======
// Using
//=======

#include "Control.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//======
// Page
//======

class Page: public Control
{
private:
	// Using
	using RoutedEventArgs=Windows::UI::Xaml::RoutedEventArgs;

public:
	// Common
	VariableHandle<Page, Control> Content;
	Event<Page, Handle<Page>> Loaded;
	Windows::UI::Xaml::Controls::Page^ UIPage;
	Event<Page, Handle<Page>> Unloaded;

protected:
	// Con-/Destructors
	Page();

private:
	// Common
	VOID OnContentChanged(Handle<Control> Content);
	Handle<Control> hContent;

	// Callback
	ref class Callback
		{
		internal:
			// Con-/Destructors
			Callback(Page* Page);

			// Common
			VOID OnLoaded(Platform::Object^ Sender, RoutedEventArgs^ Args);
			VOID OnUnloaded(Platform::Object^ Sender, RoutedEventArgs^ Args);
			Page* pPage;
		};
	Callback^ hCallback;
};

}}