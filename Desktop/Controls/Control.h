//===========
// Control.h
//===========

#pragma once


//=======
// Using
//=======

#include "Graphics/Rect.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//======================
// Forward-Declarations
//======================

class Panel;


//======================
// Horizontal Alignment
//======================

enum class HorizontalAlignment
{
Left,
Center,
Right,
Stretch
};


//====================
// Vertical Alignment
//====================

enum class VerticalAlignment
{
Top,
Middle,
Bottom,
Stretch
};


//=========
// Control
//=========

class Control: public Object
{
public:
	// Common
	Property<Control, HorizontalAlignment> Align;
	Property<Control, VerticalAlignment> AlignVertical;
	Property<Control, UINT> MaxHeight;
	Property<Control, UINT> MaxWidth;
	Property<Control, UINT> MinHeight;
	Property<Control, UINT> MinWidth;
	Event<Control, Handle<Control>, Graphics::RECT&> SizeChanged;
	Windows::UI::Xaml::FrameworkElement^ UIControl;
	Property<Control, BOOL> Visible;

protected:
	// Con-/Destructors
	Control();

private:
	// Common
	VOID OnAlignChanged(HorizontalAlignment Align);
	VOID OnAlignVerticalChanged(VerticalAlignment Align);
	VOID OnMaxHeightChanged(UINT MaxHeight);
	VOID OnMaxWidthChanged(UINT MaxWidth);
	VOID OnMinHeightChanged(UINT MaxHeight);
	VOID OnMinWidthChanged(UINT MaxWidth);
	VOID OnVisibleChanged(BOOL Visible);
};

}}