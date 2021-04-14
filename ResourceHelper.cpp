//====================
// ResourceHelper.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "ResourceHelper.h"

using namespace Windows::ApplicationModel::Resources;


//========
// Common
//========

Handle<String> GetResourceString(Handle<String> hid)
{
if(!hid)
	return nullptr;
if(hid->Contains("%"))
	return nullptr;
auto hresl=ResourceLoader::GetForCurrentView();
auto hres=hresl->GetString(Platform::StringReference(hid->Begin()));
if(!hres)
	return nullptr;
return hres->Begin();
}
