//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Application.h"


//===========
// Namespace
//===========

namespace Desktop {


//==================
// Con-/Destructors
//==================

Application::Application(Handle<String> htitle):
Core::Application(htitle)
{
Current=this;
}


//========
// Common
//========

Handle<Application> Application::Current;

}