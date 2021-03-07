//============
// MainMenu.h
//============

#pragma once


//=======
// Using
//=======

#include "Desktop/Controls/Panel.h"
#include "Menu.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//===========
// Main-Menu
//===========

class MainMenu: public Menu
{
private:
	// Using
	using AccessKeyInvokedEventArgs=Windows::UI::Xaml::Input::AccessKeyInvokedEventArgs;
	using Button=Windows::UI::Xaml::Controls::Button;
	using RoutedEventArgs=Windows::UI::Xaml::RoutedEventArgs;
	using SolidColorBrush=Windows::UI::Xaml::Media::SolidColorBrush;
	using UIElement=Windows::UI::Xaml::UIElement;

public:
	// Con-/Destructors
	MainMenu(Handle<Panel> Parent);

	// Common
	Handle<MenuItem> Add(Handle<String> Text)override;
	Windows::UI::Xaml::Controls::StackPanel^ StackPanel;

private:
	// Common
	VOID OnParentSizeChanged(Handle<Control> Parent, Graphics::RECT& Rect);
	VOID ShowMenu(Button^ Button);
	Handle<Panel> hParent;

	// Callback
	ref class Callback
		{
		internal:
			// Con-/Destructors
			Callback(MainMenu* MainMenu);

			// Common
			VOID OnButtonAccessKeyInvoked(UIElement^ Sender, AccessKeyInvokedEventArgs^ Args);
			VOID OnButtonClick(Platform::Object^ Sender, RoutedEventArgs^ Args);
			MainMenu* pMainMenu;
		};
	Callback^ hCallback;
};

}}}