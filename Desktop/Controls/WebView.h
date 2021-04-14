//===========
// WebView.h
//===========

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


//==========
// Web-View
//==========

class WebView: public Control
{
private:
	// Using
	using WebViewNavigationCompletedEventArgs=Windows::UI::Xaml::Controls::WebViewNavigationCompletedEventArgs;
	using WebViewNavigationFailedEventArgs=Windows::UI::Xaml::Controls::WebViewNavigationFailedEventArgs;

public:
	// Con-/Destructors
	WebView();

	// Common
	VOID Abort();
	VOID Navigate(Handle<String> Url);
	Event<WebView> NavigationCompleted;
	Event<WebView> NavigationFailed;
	Windows::UI::Xaml::Controls::WebView^ UIWebView;

private:
	// Callback
	ref class Callback
		{
		internal:
			// Con-/Destructors
			Callback(WebView* WebView);

			// Common
			VOID OnNavigationCompleted(Windows::UI::Xaml::Controls::WebView^ Sender, WebViewNavigationCompletedEventArgs^ Args);
			WebView* pWebView;
		};
	Callback^ hCallback;
};

}}