//===========
// Panel.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Graphics/Color.h"
#include "Panel.h"

using namespace Graphics;
using namespace Windows::UI::Xaml::Media;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//========
// Common
//========

VOID Panel::Rearrange()
{
Graphics::RECT rc({ 0, 0, (INT)UIPanel->Width, (INT)UIPanel->Height });
SizeChanged(this, this, rc);
}


//============================
// Con-/Destructors Protected
//============================

Panel::Panel():
Background(this, Colors::Transparent)
{
Background.Changed.Add(this, &Panel::OnBackgroundChanged);
}


//================
// Common Private
//================

VOID Panel::OnBackgroundChanged(COLOR c)
{
Windows::UI::Color cui;
cui.R=c.GetRed();
cui.G=c.GetGreen();
cui.B=c.GetBlue();
cui.A=c.GetAlpha();
UIPanel->Background=ref new SolidColorBrush(cui);
}

}}