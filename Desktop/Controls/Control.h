//===========
// Control.h
//===========

#pragma once


//=======
// Using
//=======

#include "Devices/Input/VirtualKey.h"
#include "Graphics/Rect.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//======================
// Forward-Declarations
//======================

class Panel;


//======================
// Horizontal Alignment
//======================

enum class HorizontalAlignment
{
Left,
Center,
Right,
Stretch
};


//====================
// Vertical Alignment
//====================

enum class VerticalAlignment
{
Top,
Middle,
Bottom,
Stretch
};


//=========
// Control
//=========

class Control: public Object
{
private:
	// Using
	using VirtualKey=Devices::Input::VirtualKey;

public:
	// Common
	Property<Control, HorizontalAlignment> Align;
	Property<Control, VerticalAlignment> AlignVertical;
	Event<Control, VirtualKey> KeyDown;
	Property<Control, UINT> MaxHeight;
	Property<Control, UINT> MaxWidth;
	Property<Control, UINT> MinHeight;
	Property<Control, UINT> MinWidth;
	Event<Control, Handle<Control>, Graphics::RECT&> SizeChanged;
	Windows::UI::Xaml::FrameworkElement^ UIControl;
	Property<Control, BOOL> Visible;

protected:
	// Con-/Destructors
	Control();

	// Common
	VOID Initialize(Windows::UI::Xaml::FrameworkElement^ Control);

private:
	// Common
	VOID OnAlignChanged(HorizontalAlignment Align);
	VOID OnAlignVerticalChanged(VerticalAlignment Align);
	VOID OnMaxHeightChanged(UINT MaxHeight);
	VOID OnMaxWidthChanged(UINT MaxWidth);
	VOID OnMinHeightChanged(UINT MaxHeight);
	VOID OnMinWidthChanged(UINT MaxWidth);
	VOID OnVisibleChanged(BOOL Visible);

	// Callback
	ref class Callback sealed
		{
		internal:
			// Con-/Destructors
			Callback(Control* Control): pControl(Control) {}

			// Common
			VOID OnKeyDown(Platform::Object^ Sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ Args);
			Control* pControl;
		};
	Callback^ hCallback;
};

}}