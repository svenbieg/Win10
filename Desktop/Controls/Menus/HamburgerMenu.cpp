//===================
// HamburgerMenu.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include "Desktop/Application.h"
#include "HamburgerMenu.h"
#include "MenuHelper.h"

using namespace Desktop;
using namespace Graphics;
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
Content(this),
hIconFont(ref new FontFamily(L"Segoe MDL2 Assets")),
hItems(new ItemList()),
hParent(hparent),
// Callback
hCallback(ref new Callback(this))
{
Content.Changed.Add(this, &HamburgerMenu::OnContentChanged);
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
			hButton->Content=PlatformSymbolString(Symbols::Hamburger);
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

VOID HamburgerMenu::Add(Handle<String> hstr, Symbols symbol, Handle<Control> hcontrol)
{
if(symbol==Symbols::None)
	symbol=Symbols::Point;
UINT ucount=(UINT)hItems->GetCount();
hItems->Append(hcontrol);
auto hpanel=ref new StackPanel();
	{
	hpanel->Orientation=Orientation::Horizontal;
	auto hsymbol=ref new TextBlock();
		{
		hsymbol->FontFamily=hIconFont;
		hsymbol->FontSize=24;
		hsymbol->Text=PlatformSymbolString(symbol);
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

VOID HamburgerMenu::Select(INT id)
{
Application::Current->Dispatch(this, &HamburgerMenu::DoSelect, id);
}

VOID HamburgerMenu::Select(Handle<Control> control)
{
UINT id=0;
for(auto hit=hItems->First(); hit->HasCurrent(); hit->MoveNext())
	{
	auto current=hit->GetCurrent();
	if(current==control)
		Select(id);
	id++;
	}
}


//================
// Common Private
//================

VOID HamburgerMenu::DoSelect(INT id)
{
hListBox->SelectedIndex=id;
}

VOID HamburgerMenu::OnContentChanged(Handle<Control> content)
{
FrameworkElement^ control=content? content->UIControl: nullptr;
hSplitView->Content=control;
hParent->Rearrange();
}

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
INT sel=pMenu->hListBox->SelectedIndex;
auto control=pMenu->hItems->GetAt(sel);
if(!control)
	return;
pMenu->Content=control;
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