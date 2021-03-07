//========
// Menu.h
//========

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "MenuItem.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//======
// Menu
//======

class Menu: public Object
{
protected:
	// Using
	using MenuItemMap=Collections::Map<Handle<String>, Handle<MenuItem>>;
	using UIElement=Windows::UI::Xaml::UIElement;

public:
	// Common
	virtual Handle<MenuItem> Add(Handle<String> Text)=0;
	Handle<MenuItemMap> Items;
	UIElement^ Parent;

protected:
	// Con-/Destructors
	Menu(UIElement^ Parent);
};

}}}