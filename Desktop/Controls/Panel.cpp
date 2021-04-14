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


//==================
// Common Protected
//==================

VOID Panel::Initialize(Windows::UI::Xaml::Controls::Panel^ panel)
{
UIPanel=panel;
UIPanel->Background=ref new SolidColorBrush(Windows::UI::Colors::Transparent);
}


//================
// Common Private
//================

VOID Panel::OnBackgroundChanged(COLOR c)
{
auto cui=ColorToUIColor(c);
UIPanel->Background=ref new SolidColorBrush(cui);
}

}}