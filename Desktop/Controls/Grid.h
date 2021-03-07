//========
// Grid.h
//========

#pragma once


//=======
// Using
//=======

#include "Collections/Cluster.h"
#include "Panel.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//=============
// Grid-Length
//=============

enum class GridLength
{
Auto,
Star
};


//======
// Grid
//======

class Grid: public Panel
{
private:
	// Using
	using ControlList=Collections::Cluster<Handle<Control>>;

public:
	// Con-/Destructors
	Grid();

	// Common
	VOID Add(Handle<Control> Control, UINT Column=0, UINT Row=0);
	VOID AddColumn(UINT Width);
	VOID AddColumn(GridLength Width);
	VOID AddRow(UINT Height);
	VOID AddRow(GridLength Height);
	Windows::UI::Xaml::Controls::Grid^ UIGrid;

private:
	// Common
	Handle<ControlList> hChildren;
};

}}