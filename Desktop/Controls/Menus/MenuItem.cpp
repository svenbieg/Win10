//==============
// MenuItem.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "MenuHelper.h"
#include "MenuItem.h"
#include "PopupMenu.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//==================
// Con-/Destructors
//==================

MenuItem::MenuItem(Handle<Menu> hparent, Handle<String> htext):
hParent(hparent)
{
Handle<String> hacc;
GetMenuString(&htext, &hacc);
if(hacc)
	AccessKey=ref new Platform::String(hacc->Begin());
Text=htext;
hParent->Items->Add(Text, this);
}


//========
// Common
//========

Handle<MenuItem> MenuItem::Add(Handle<String> htext)
{
if(!SubMenu)
	SubMenu=new PopupMenu(hParent->Parent);
return SubMenu->Add(htext);
}

}}}