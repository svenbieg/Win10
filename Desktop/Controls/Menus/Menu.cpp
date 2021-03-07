//==========
// Menu.cpp
//==========

#include "pch.h"


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


//============================
// Con-/Destructors Protected
//============================

Menu::Menu(UIElement^ hparent):
Parent(hparent)
{
Items=new MenuItemMap();
}

}}}