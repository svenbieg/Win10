//============
// Dialog.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include "Graphics/Color.h"
#include "Dialog.h"

using namespace Concurrency;
using namespace Graphics;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Dialogs {


//========
// Common
//========

VOID Dialog::Hide(BOOL result)
{
bResult=result;
UIContentDialog->Hide();
}

VOID Dialog::Show(Procedure primary, Procedure secondary)
{
bResult=false;
create_task(UIContentDialog->ShowAsync()).then([this, primary, secondary](ContentDialogResult result)
	{
	if(result==ContentDialogResult::Primary)
		bResult=true;
	if(bResult)
		{
		Primary(this);
		primary();
		}
	else
		{
		Secondary(this);
		secondary();
		}
	});
}


//============================
// Con-/Destructors Protected
//============================

Dialog::Dialog():
Content(this),
PrimaryText(this),
SecondaryText(this),
Title(this),
bResult(false)
{
Content.Changed.Add(this, &Dialog::OnContentChanged);
PrimaryText.Changed.Add(this, &Dialog::OnPrimaryTextChanged);
SecondaryText.Changed.Add(this, &Dialog::OnSecondaryTextChanged);
Title.Changed.Add(this, &Dialog::OnTitleChanged);
UIContentDialog=ref new ContentDialog();
UIControl=UIContentDialog;
}


//================
// Common Private
//================

VOID Dialog::OnContentChanged(Handle<Control> hctrl)
{
hContent=hctrl;
if(!hctrl)
	{
	UIContentDialog->Content=nullptr;
	return;
	}
UIContentDialog->Content=hctrl->UIControl;
}

VOID Dialog::OnPrimaryTextChanged(Handle<String> htext)
{
if(!htext)
	{
	UIContentDialog->PrimaryButtonText=nullptr;
	return;
	}
auto hres=GetResourceString(htext);
if(hres)
	htext=hres;
UIContentDialog->PrimaryButtonText=ref new Platform::String(htext->Begin());
}

VOID Dialog::OnSecondaryTextChanged(Handle<String> htext)
{
if(!htext)
	{
	UIContentDialog->SecondaryButtonText=nullptr;
	return;
	}
auto hres=GetResourceString(htext);
if(hres)
	htext=hres;
UIContentDialog->SecondaryButtonText=ref new Platform::String(htext->Begin());
}

VOID Dialog::OnTitleChanged(Handle<String> htext)
{
if(!htext)
	{
	UIContentDialog->SecondaryButtonText=nullptr;
	return;
	}
auto hres=GetResourceString(htext);
if(hres)
	htext=hres;
UIContentDialog->Title=ref new Platform::String(htext->Begin());
}

}}