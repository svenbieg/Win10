//=============
// ListBox.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "ListBox.h"

using namespace Windows::UI::Xaml::Controls;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

ListBox::ListBox():
hCallback(ref new Callback(this))
{
UIListBox=ref new Windows::UI::Xaml::Controls::ListBox();
UIListBox->SelectionChanged+=ref new SelectionChangedEventHandler(hCallback, &Callback::OnSelectionChanged);
UIControl=UIListBox;
}


//========
// Common
//========

VOID ListBox::Append(Handle<String> htext)
{
if(!htext)
	return;
auto htextblock=ref new TextBlock();
htextblock->Text=ref new Platform::String(htext->Begin());
auto hitem=ref new ListBoxItem();
hitem->Content=htextblock;
UIListBox->Items->Append(hitem);
}

VOID ListBox::Clear()
{
UIListBox->Items->Clear();
}

BOOL ListBox::Contains(Handle<String> htext)
{
return GetId(htext)>=0;
}

Handle<String> ListBox::GetAt(UINT upos)
{
auto hitem=dynamic_cast<ListBoxItem^>(UIListBox->Items->GetAt(upos));
if(!hitem)
	return nullptr;
auto htextblock=dynamic_cast<TextBlock^>(hitem->Content);
if(!htextblock)
	return nullptr;
return htextblock->Text->Begin();
}

INT ListBox::GetId(Handle<String> htext)
{
if(!htext)
	return -1;
INT iid=0;
for(auto hit=UIListBox->Items->First(); hit->HasCurrent; hit->MoveNext())
	{
	auto hitem=dynamic_cast<ListBoxItem^>(hit->Current);
	if(!hitem)
		continue;
	auto htextblock=dynamic_cast<TextBlock^>(hitem->Content);
	if(!htextblock)
		continue;
	if(StringCompare(htextblock->Text->Begin(), htext->Begin())==0)
		return iid;
	iid++;
	}
return -1;
}

INT ListBox::GetSelected()
{
return UIListBox->SelectedIndex;
}

VOID ListBox::Remove(Handle<String> htext)
{
INT iid=GetId(htext);
if(iid<0)
	return;
UIListBox->Items->RemoveAt(iid);
}

VOID ListBox::RemoveAt(UINT upos)
{
UIListBox->Items->RemoveAt(upos);
}

VOID ListBox::Select(INT isel)
{
UIListBox->SelectedIndex=isel;
}

VOID ListBox::Set(Handle<StringList> hitems)
{
for(auto hit=UIListBox->Items->First(); hit->HasCurrent; hit->MoveNext())
	{
	auto hitem=dynamic_cast<ListBoxItem^>(hit->Current);
	if(!hitem)
		continue;
	auto htextblock=dynamic_cast<TextBlock^>(hitem->Content);
	if(!htextblock)
		continue;
	if(!hitems->Contains(htextblock->Text->Begin()))
		{
		UINT uid=0;
		if(UIListBox->Items->IndexOf(hitem, &uid))
			UIListBox->Items->RemoveAt(uid);
		}
	}
for(auto hit=hitems->First(); hit->HasCurrent(); hit->MoveNext())
	{
	auto hname=hit->GetCurrent()->Value;
	if(!Contains(hname))
		Append(hname);
	}
}


//==================
// Callback Private
//==================

VOID ListBox::Callback::OnSelectionChanged(Platform::Object^ hsender, SelectionChangedEventArgs^ hargs)
{
pListBox->SelectionChanged(pListBox, pListBox, pListBox->GetSelected());
}

}}