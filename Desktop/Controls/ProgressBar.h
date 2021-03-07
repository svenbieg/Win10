//===============
// ProgressBar.h
//===============

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


//==============
// Progress-Bar
//==============

class ProgressBar: public Control
{
public:
	// Con-/Destructors
	ProgressBar();

	// Common
	Property<ProgressBar, UINT> Progress;
	Windows::UI::Xaml::Controls::ProgressBar^ UIProgressBar;

private:
	// Common
	VOID OnProgressChanged(UINT Progress);
};

}}