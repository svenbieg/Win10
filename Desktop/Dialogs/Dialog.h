//==========
// Dialog.h
//==========

#pragma once


//=======
// Using
//=======

#include "Desktop/Controls/Control.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Dialogs {


//========
// Dialog
//========

class Dialog: public Controls::Control
{
private:
	// Using
	using Control=Desktop::Controls::Control;

public:
	// Common
	VariableHandle<Dialog, Control> Content;
	VOID Hide(BOOL Result=false);
	Event<Dialog> Primary;
	VariableHandle<Dialog, String> PrimaryText;
	Event<Dialog> Secondary;
	VariableHandle<Dialog, String> SecondaryText;
	VOID Show(Procedure Primary=[](){}, Procedure Secondary=[](){});
	VariableHandle<Dialog, String> Title;
	Windows::UI::Xaml::Controls::ContentDialog^ UIContentDialog;

protected:
	// Con-/Destructors
	Dialog();

private:
	// Common
	VOID OnContentChanged(Handle<Control> Content);
	VOID OnPrimaryTextChanged(Handle<String> Text);
	VOID OnSecondaryTextChanged(Handle<String> Text);
	VOID OnTitleChanged(Handle<String> Text);
	BOOL bResult;
	Handle<Control> hContent;
};

}}