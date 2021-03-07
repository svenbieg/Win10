//=================
// HamburgerMenu.h
//=================

#pragma once


//=======
// Using
//=======

#include "Collections/Cluster.h"
#include "Desktop/Controls/Panel.h"
#include "Menu.h"
#include "Symbols.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//================
// Hamburger-Menu
//================

class HamburgerMenu: public Object
{
private:
	// Using
	using ItemList=Collections::Cluster<Handle<Control>>;
	using RoutedEventArgs=Windows::UI::Xaml::RoutedEventArgs;

public:
	// Con-/Destructors
	HamburgerMenu(Handle<Panel> Parent);

	// Common
	VOID Add(Handle<String> Text, Symbols Symbol, Handle<Control> Control);

private:
	// Common
	VOID OnParentSizeChanged(Handle<Control> Parent, Graphics::RECT& Rect);
	Windows::UI::Xaml::Controls::Button^ hButton;
	Windows::UI::Xaml::Media::FontFamily^ hIconFont;
	Handle<ItemList> hItems;
	Windows::UI::Xaml::Controls::ListBox^ hListBox;
	Handle<Panel> hParent;
	Windows::UI::Xaml::Controls::SplitView^ hSplitView;
	Windows::UI::Xaml::Controls::StackPanel^ hStackPanel;

	// Callback
	ref class Callback
		{
		internal:
			// Con-/Destructors
			Callback(HamburgerMenu* Menu);

			// Common
			VOID OnButtonClick(Platform::Object^ Sender, RoutedEventArgs^ Args);
			VOID OnListBoxSelectionChanged(Platform::Object^ Sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ Args);
			VOID OnSplitViewLayoutUpdated(Platform::Object^ Sender, Platform::Object^ Args);
			HamburgerMenu* pMenu;
		};
	Callback^ hCallback;
};

}}}