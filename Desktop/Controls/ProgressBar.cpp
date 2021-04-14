//=================
// ProgressBar.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "ProgressBar.h"

using namespace Graphics;
using namespace Windows::UI::Xaml::Media;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

ProgressBar::ProgressBar():
Background(this, Colors::LightGray),
Progress(this, 0)
{
UIProgressBar=ref new Windows::UI::Xaml::Controls::ProgressBar();
UIProgressBar->Maximum=100;
UIControl=UIProgressBar;
Background.Changed.Add(this, &ProgressBar::OnBackgroundChanged);
Progress.Changed.Add(this, &ProgressBar::OnProgressChanged);
OnBackgroundChanged(Background.GetInternal());
}


//================
// Common Private
//================

VOID ProgressBar::OnBackgroundChanged(COLOR c)
{
auto cui=ColorToUIColor(c);
UIProgressBar->Background=ref new SolidColorBrush(cui);
}

VOID ProgressBar::OnProgressChanged(INT progress)
{
if(progress<0)
	{
	UIProgressBar->IsIndeterminate=true;
	return;
	}
UIProgressBar->IsIndeterminate=false;
UIProgressBar->Value=progress;
}

}}