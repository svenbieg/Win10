//=================
// ProgressBar.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "ProgressBar.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

ProgressBar::ProgressBar():
Progress(this, 0)
{
UIProgressBar=ref new Windows::UI::Xaml::Controls::ProgressBar();
UIProgressBar->Maximum=100;
UIControl=UIProgressBar;
Progress.Changed.Add(this, &ProgressBar::OnProgressChanged);
}


//================
// Common Private
//================

VOID ProgressBar::OnProgressChanged(UINT uprogress)
{
UIProgressBar->Value=uprogress;
}

}}