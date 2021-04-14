//=================
// ColorHelper.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "ColorHelper.h"


//===========
// Namespace
//===========

namespace Graphics {


//========
// Common
//========

COLOR ColorFromUIColor(Windows::UI::Color c)
{
return COLOR(c.R, c.G, c.B, c.A);
}

Windows::UI::Color ColorToUIColor(COLOR c)
{
Windows::UI::Color cui;
cui.R=c.GetRed();
cui.G=c.GetGreen();
cui.B=c.GetBlue();
cui.A=c.GetAlpha();
return cui;
}

}