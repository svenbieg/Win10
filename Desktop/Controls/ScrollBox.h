//=============
// ScrollBox.h
//=============

#pragma once


//=======
// Using
//=======

#include "Control.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//============
// Scroll-Box
//============

class ScrollBox: public Control
{
public:
	// Con-/Destructors
	ScrollBox();

	// Common
	Windows::UI::Xaml::Controls::ScrollViewer^ UIScrollBox;
};

}}