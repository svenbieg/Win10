//===========
// ListBox.h
//===========

#pragma once


//=======
// Using
//=======

#include "Collections/StringList.h"
#include "Control.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==========
// List-Box
//==========

class ListBox: public Control
{
private:
	// Using
	using StringList=Collections::StringList;

public:
	// Con-/Destructors
	ListBox();

	// Common
	VOID Append(Handle<String> Item);
	VOID Clear();
	BOOL Contains(Handle<String> Item);
	Handle<String> GetAt(UINT Position);
	INT GetId(Handle<String> Item);
	INT GetSelected();
	VOID Remove(Handle<String> Text);
	VOID RemoveAt(UINT Position);
	VOID Select(INT Position);
	Event<ListBox, INT> SelectionChanged;
	VOID Set(Handle<StringList> Items);
	Windows::UI::Xaml::Controls::ListBox^ UIListBox;

private:
	// Callback
	ref class Callback sealed
		{
		internal:
			// Using
			using SelectionChangedEventArgs=Windows::UI::Xaml::Controls::SelectionChangedEventArgs;

			// Con-/Destructors
			Callback(ListBox* ListBox): pListBox(ListBox) {}

			// Common
			VOID OnSelectionChanged(Platform::Object^ Sender, SelectionChangedEventArgs^ Args);
			ListBox* pListBox;
		};
	Callback^ hCallback;
};

}}