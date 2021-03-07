//==========
// Grid.cpp
//==========

#include "pch.h"


//=======
// Using
//=======

#include "Grid.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

Grid::Grid()
{
UIGrid=ref new Windows::UI::Xaml::Controls::Grid();
UIPanel=UIGrid;
UIControl=UIGrid;
hChildren=new ControlList();
}


//========
// Common
//========

VOID Grid::Add(Handle<Control> hctrl, UINT ucol, UINT urow)
{
UIGrid->Children->Append(hctrl->UIControl);
UIGrid->SetColumn(hctrl->UIControl, ucol);
UIGrid->SetRow(hctrl->UIControl, urow);
hChildren->Append(hctrl);
}

VOID Grid::AddColumn(UINT uwidth)
{
auto hdef=ref new ColumnDefinition();
hdef->Width=uwidth;
UIGrid->ColumnDefinitions->Append(hdef);
}

VOID Grid::AddColumn(GridLength width)
{
auto hdef=ref new ColumnDefinition();
GridUnitType unit=GridUnitType::Auto;
if(width==GridLength::Star)
	unit=GridUnitType::Star;
hdef->Width=Windows::UI::Xaml::GridLength(1, unit);
UIGrid->ColumnDefinitions->Append(hdef);
}

VOID Grid::AddRow(UINT uheight)
{
auto hdef=ref new RowDefinition();
hdef->Height=uheight;
UIGrid->RowDefinitions->Append(hdef);
}

VOID Grid::AddRow(GridLength height)
{
auto hdef=ref new RowDefinition();
GridUnitType unit=GridUnitType::Auto;
if(height==GridLength::Star)
	unit=GridUnitType::Star;
hdef->Height=Windows::UI::Xaml::GridLength(1, unit);
UIGrid->RowDefinitions->Append(hdef);
}

}}