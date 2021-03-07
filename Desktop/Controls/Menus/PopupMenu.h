//=============
// PopupMenu.h
//=============

#pragma once


//=======
// Using
//=======

#include "Menu.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//============
// Popup-Menu
//============

class PopupMenu: public Menu
{
private:
	// Using
	using AccessKeyInvokedEventArgs=Windows::UI::Xaml::Input::AccessKeyInvokedEventArgs;
	using MenuFlyoutItem=Windows::UI::Xaml::Controls::MenuFlyoutItem;
	using RoutedEventArgs=Windows::UI::Xaml::RoutedEventArgs;

public:
	// Con-/Destructors
	PopupMenu(UIElement^ Parent);

	// Common
	Handle<MenuItem> Add(Handle<String> Text)override;
	Windows::UI::Xaml::Controls::MenuFlyout^ MenuFlyout;

private:
	// Common
	VOID HandleItem(MenuFlyoutItem^ Item);

	// Callback
	ref class Callback
		{
		internal:
			// Con-/Destructors
			Callback(PopupMenu* PopupMenu);

			// Common
			VOID OnButtonAccessKeyInvoked(UIElement^ Sender, AccessKeyInvokedEventArgs^ Args);
			VOID OnButtonClick(Platform::Object^ Sender, RoutedEventArgs^ Args);
			PopupMenu* pPopupMenu;
		};
	Callback^ hCallback;
};

}}}