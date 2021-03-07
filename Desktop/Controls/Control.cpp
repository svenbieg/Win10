//=============
// Control.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Panel.h"

using namespace Windows::UI::Xaml;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//============================
// Con-/Destructors Protected
//============================

Control::Control():
Align(this, HorizontalAlignment::Left),
AlignVertical(this, VerticalAlignment::Top),
MaxHeight(this, -1),
MaxWidth(this, -1),
MinHeight(this, 0),
MinWidth(this, 0),
Visible(this, true)
{
Align.Changed.Add(this, &Control::OnAlignChanged);
AlignVertical.Changed.Add(this, &Control::OnAlignVerticalChanged);
MaxHeight.Changed.Add(this, &Control::OnMaxHeightChanged);
MaxWidth.Changed.Add(this, &Control::OnMaxWidthChanged);
MinHeight.Changed.Add(this, &Control::OnMinHeightChanged);
MinWidth.Changed.Add(this, &Control::OnMinWidthChanged);
Visible.Changed.Add(this, &Control::OnVisibleChanged);
}


//================
// Common Private
//================

VOID Control::OnAlignChanged(HorizontalAlignment align)
{
Windows::UI::Xaml::HorizontalAlignment a;
switch(align)
	{
	case HorizontalAlignment::Left:
		{
		a=Windows::UI::Xaml::HorizontalAlignment::Left;
		break;
		}
	case HorizontalAlignment::Center:
		{
		a=Windows::UI::Xaml::HorizontalAlignment::Center;
		break;
		}
	case HorizontalAlignment::Right:
		{
		a=Windows::UI::Xaml::HorizontalAlignment::Right;
		break;
		}
	case HorizontalAlignment::Stretch:
		{
		a=Windows::UI::Xaml::HorizontalAlignment::Stretch;
		break;
		}
	}
UIControl->HorizontalAlignment=a;
}

VOID Control::OnAlignVerticalChanged(VerticalAlignment align)
{
Windows::UI::Xaml::VerticalAlignment a;
switch(align)
	{
	case VerticalAlignment::Top:
		{
		a=Windows::UI::Xaml::VerticalAlignment::Top;
		break;
		}
	case VerticalAlignment::Middle:
		{
		a=Windows::UI::Xaml::VerticalAlignment::Center;
		break;
		}
	case VerticalAlignment::Bottom:
		{
		a=Windows::UI::Xaml::VerticalAlignment::Bottom;
		break;
		}
	case VerticalAlignment::Stretch:
		{
		a=Windows::UI::Xaml::VerticalAlignment::Stretch;
		break;
		}
	}
UIControl->VerticalAlignment=a;
}

VOID Control::OnMaxHeightChanged(UINT uheight)
{
UIControl->MaxHeight=uheight;
}

VOID Control::OnMaxWidthChanged(UINT uwidth)
{
UIControl->MaxWidth=uwidth;
}

VOID Control::OnMinHeightChanged(UINT uheight)
{
UIControl->MinHeight=uheight;
}

VOID Control::OnMinWidthChanged(UINT uwidth)
{
UIControl->MinWidth=uwidth;
}

VOID Control::OnVisibleChanged(BOOL bvisible)
{
if(UIControl)
	UIControl->Visibility=bvisible? Visibility::Visible: Visibility::Collapsed;
}

}}