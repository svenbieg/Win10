//===================
// HamburgerMenu.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include "HamburgerMenu.h"
#include "MenuHelper.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//==================
// Con-/Destructors
//==================

HamburgerMenu::HamburgerMenu(Handle<Panel> hparent):
hIconFont(ref new FontFamily(L"Segoe MDL2 Assets")),
hItems(new ItemList()),
hParent(hparent),
// Callback
hCallback(ref new Callback(this))
{
hSplitView=ref new Windows::UI::Xaml::Controls::SplitView();
	{
	hSplitView->DisplayMode=SplitViewDisplayMode::CompactOverlay;
	hSplitView->LayoutUpdated+=ref new Windows::Foundation::EventHandler<Platform::Object^>(hCallback, &Callback::OnSplitViewLayoutUpdated);
	hStackPanel=ref new Windows::UI::Xaml::Controls::StackPanel();
		{
		hStackPanel->Orientation=Orientation::Vertical;
		hButton=ref new Button();
			{
			hButton->Click+=ref new RoutedEventHandler(hCallback, &Callback::OnButtonClick);
			hButton->Content=L"\xE700";
			hButton->FontFamily=hIconFont;
			hButton->FontSize=24;
			}
		hStackPanel->Children->Append(hButton);
		hListBox=ref new ListBox();
			{
			hListBox->SelectionChanged+=ref new SelectionChangedEventHandler(hCallback, &Callback::OnListBoxSelectionChanged);
			hListBox->SelectionMode=Windows::UI::Xaml::Controls::SelectionMode::Single;
			}
		hStackPanel->Children->Append(hListBox);
		}
	hSplitView->Pane=hStackPanel;
	}
hParent->UIPanel->Children->Append(hSplitView);
hParent->SizeChanged.Add(this, &HamburgerMenu::OnParentSizeChanged);
}


//========
// Common
//========

VOID HamburgerMenu::Add(Handle<String> hstr, Symbols usymbol, Handle<Control> hcontrol)
{
if(usymbol==Symbols::None)
	usymbol=Symbols::Point;
UINT ucount=hItems->GetCount();
hItems->Append(hcontrol);
auto hpanel=ref new StackPanel();
	{
	hpanel->Orientation=Orientation::Horizontal;
	auto hsymbol=ref new TextBlock();
		{
		hsymbol->FontFamily=hIconFont;
		hsymbol->FontSize=24;
		WCHAR psymbol[2]={ (WCHAR)usymbol, 0 };
		hsymbol->Text=ref new Platform::String(psymbol);
		}
	hpanel->Children->Append(hsymbol);
	GetMenuString(&hstr, nullptr);
	auto htext=ref new TextBlock();
		{
		htext->FontSize=18;
		htext->Margin=Thickness(16, 0, 16, 0);
		htext->Text=ref new Platform::String(hstr->Begin());
		}
	hpanel->Children->Append(htext);
	}
hListBox->Items->Append(hpanel);
if(ucount==0)
	hListBox->SelectedIndex=0;
}


//================
// Common Private
//================

VOID HamburgerMenu::OnParentSizeChanged(Handle<Control> hparent, Graphics::RECT& rc)
{
hSplitView->SetValue(Canvas::LeftProperty, rc.Left);
hSplitView->SetValue(Canvas::TopProperty, rc.Top);
hSplitView->Width=rc.Right-rc.Left;
hSplitView->Height=rc.Bottom-rc.Top;
}


//==================
// Callback Private
//==================

HamburgerMenu::Callback::Callback(HamburgerMenu* pmenu):
pMenu(pmenu)
{}

VOID HamburgerMenu::Callback::OnButtonClick(Platform::Object^ hsender, RoutedEventArgs^ hargs)
{
BOOL bopen=pMenu->hSplitView->IsPaneOpen;
pMenu->hSplitView->IsPaneOpen=!bopen;
}

VOID HamburgerMenu::Callback::OnListBoxSelectionChanged(Platform::Object^ hsender, SelectionChangedEventArgs^ hargs)
{
INT isel=pMenu->hListBox->SelectedIndex;
auto hcontrol=pMenu->hItems->GetAt(isel);
if(!hcontrol)
	return;
pMenu->hSplitView->Content=hcontrol->UIControl;
pMenu->hParent->Rearrange();
}

VOID HamburgerMenu::Callback::OnSplitViewLayoutUpdated(Platform::Object^ hsender, Platform::Object^ hargs)
{
DOUBLE dbtn=pMenu->hButton->ActualWidth;
pMenu->hSplitView->CompactPaneLength=dbtn;
DOUBLE dminwidth=0;
for(auto hit=pMenu->hListBox->Items->First(); hit->HasCurrent; hit->MoveNext())
	{
	auto hpanel=reinterpret_cast<StackPanel^>(hit->Current);
	DOUBLE dwidth=hpanel->ActualWidth+hpanel->Margin.Left+hpanel->Margin.Right;
	dminwidth=max(dminwidth, dwidth);
	}
dminwidth+=24;
pMenu->hSplitView->OpenPaneLength=dminwidth;
}

}}}