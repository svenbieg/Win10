//===========
// Image.cpp
//===========

#include "pch.h"


//=======
// Using
//=======

#include "Image.h"

using namespace Windows::UI::Xaml::Media::Imaging;


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {


//==================
// Con-/Destructors
//==================

Image::Image():
Source(this),
Stretch(this, true)
{
UIImage=ref new Windows::UI::Xaml::Controls::Image();
UIControl=UIImage;
Source.Changed.Add(this, &Image::OnSourceChanged);
Stretch.Changed.Add(this, &Image::OnStretchChanged);
}


//================
// Common Private
//================

VOID Image::OnSourceChanged(Handle<String> hsource)
{
if(!hsource)
	{
	UIImage->Source=nullptr;
	return;
	}
auto huri=ref new Windows::Foundation::Uri(Platform::StringReference(hsource->Begin()));
UIImage->Source=ref new BitmapImage(huri);
}

VOID Image::OnStretchChanged(BOOL bstretch)
{
if(bstretch)
	{
	UIImage->Stretch=Windows::UI::Xaml::Media::Stretch::UniformToFill;
	}
else
	{
	UIImage->Stretch=Windows::UI::Xaml::Media::Stretch::None;
	}
}

}}