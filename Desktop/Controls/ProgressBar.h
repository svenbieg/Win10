//===============
// ProgressBar.h
//===============

#pragma once


//=======
// Using
//=======

#include "Graphics/Color.h"
#include "Control.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==============
// Progress-Bar
//==============

class ProgressBar: public Control
{
public:
	// Con-/Destructors
	ProgressBar();

	// Common
	Property<ProgressBar, Graphics::COLOR> Background;
	Property<ProgressBar, INT> Progress;
	Windows::UI::Xaml::Controls::ProgressBar^ UIProgressBar;

private:
	// Common
	VOID OnBackgroundChanged(Graphics::COLOR Color);
	VOID OnProgressChanged(INT Progress);
};

}}