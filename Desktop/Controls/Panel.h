//=========
// Panel.h
//=========

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


//=======
// Panel
//=======

class Panel: public Control
{
public:
	// Common
	Property<Panel, Graphics::COLOR> Background;
	VOID Rearrange();
	Windows::UI::Xaml::Controls::Panel^ UIPanel;

protected:
	// Con-/Destructors
	Panel();

	// Common
	VOID Initialize(Windows::UI::Xaml::Controls::Panel^ Panel);

private:
	// Common
	VOID OnBackgroundChanged(Graphics::COLOR Color);
};

}}