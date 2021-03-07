//============
// MenuItem.h
//============

#pragma once


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//======================
// Forward-Declarations
//======================

class Menu;
class PopupMenu;


//===========
// Menu-Item
//===========

class MenuItem: public Object
{
public:
	// Con-/Destructors
	MenuItem(Handle<Menu> Parent, Handle<String> Text);

	// Common
	Platform::String^ AccessKey;
	Handle<MenuItem> Add(Handle<String> Text);
	Handle<PopupMenu> SubMenu;
	Handle<String> Text;

private:
	// Common
	Handle<Menu> hParent;
};

}}}