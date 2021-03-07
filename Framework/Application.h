//===============
// Application.h
//===============

#pragma once


//===========
// Namespace
//===========

namespace Framework {


//=====================
// FrameworkViewSource
//=====================

ref class FrameworkViewSource sealed: public Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	// IFrameworkViewSource
	Windows::ApplicationModel::Core::IFrameworkView^ CreateView()override;
};


//===============
// FrameworkView
//===============

ref class FrameworkView sealed: public Windows::ApplicationModel::Core::IFrameworkView
{
private:
	// Using
	using CoreApplicationView=Windows::ApplicationModel::Core::CoreApplicationView;
	using CoreWindow=Windows::UI::Core::CoreWindow;
	using SuspendingEventArgs=Windows::ApplicationModel::SuspendingEventArgs;

public:
	// IFrameworkView
	VOID Initialize(CoreApplicationView^ View)override;
	VOID Load(Platform::String^ EntryPoint)override;
	VOID Run()override;
	VOID SetWindow(CoreWindow^ Window)override;
	VOID Uninitialize()override;

internal:
	// Common
	VOID OnSuspending(Platform::Object^ Sender, SuspendingEventArgs^ Args);
};

}