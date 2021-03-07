//=============
// WebView.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "WebView.h"

using namespace Windows::UI::Xaml::Controls;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

WebView::WebView():
hCallback(ref new Callback(this))
{
UIWebView=ref new Windows::UI::Xaml::Controls::WebView();
UIWebView->NavigationCompleted+=ref new TypedEventHandler<Windows::UI::Xaml::Controls::WebView^, WebViewNavigationCompletedEventArgs^>(hCallback, &Callback::OnNavigationCompleted);
UIControl=UIWebView;
}


//========
// Common
//========

VOID WebView::Abort()
{
UIWebView->Stop();
}

VOID WebView::Navigate(Handle<String> hurl)
{
auto huri=ref new Windows::Foundation::Uri(Platform::StringReference(hurl->Begin()));
UIWebView->Navigate(huri);
}


//==================
// Callback Private
//==================

WebView::Callback::Callback(WebView* pwebview):
pWebView(pwebview)
{}

VOID WebView::Callback::OnNavigationCompleted(Windows::UI::Xaml::Controls::WebView^ hsender, WebViewNavigationCompletedEventArgs^ hargs)
{
pWebView->NavigationCompleted(pWebView, pWebView, hargs->IsSuccess);
}

}}