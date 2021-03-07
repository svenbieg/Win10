//===============
// Application.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Xaml {


//=============
// Application
//=============

ref class Application: public Windows::UI::Xaml::Application
{
private:
	// Using
	using LaunchActivatedEventArgs=Windows::ApplicationModel::Activation::LaunchActivatedEventArgs;
	using SuspendingEventArgs=Windows::ApplicationModel::SuspendingEventArgs;
	using WindowCreatedEventArgs=Windows::UI::Xaml::WindowCreatedEventArgs;

public:
	// Common
	VOID OnLaunched(LaunchActivatedEventArgs^ e)override;
	VOID OnWindowCreated(WindowCreatedEventArgs^ e)override;

internal:
	// Con-/Destructors
	Application();

private:
	// Common
	VOID OnSuspending(Platform::Object^ Sender, SuspendingEventArgs^ Args);
};

}