//===============
// ScrollBox.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "ScrollBox.h"

using namespace Windows::UI::Xaml::Controls;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

ScrollBox::ScrollBox()
{
UIScrollBox=ref new ScrollViewer();
Initialize(UIScrollBox);
}

}}