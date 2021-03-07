//=========
// Image.h
//=========

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


//=======
// Image
//=======

class Image: public Control
{
public:
	// Con-/Destructors
	Image();

	// Common
	Windows::UI::Xaml::Controls::Image^ UIImage;
	VariableHandle<Image, String> Source;
	Property<Image, BOOL> Stretch;

private:
	// Common
	VOID OnSourceChanged(Handle<String> Source);
	VOID OnStretchChanged(BOOL Stretch);
};

}}