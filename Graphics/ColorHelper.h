//===============
// ColorHelper.h
//===============

#pragma once


//=======
// Using
//=======

#include "Graphics/Color.h"


//===========
// Namespace
//===========

namespace Graphics {


//========
// Common
//========

COLOR ColorFromUIColor(Windows::UI::Color Color);
Windows::UI::Color ColorToUIColor(COLOR Color);

}