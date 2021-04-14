//=============
// Symbols.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Symbols.h"


//===========
// Namespace
//===========

namespace Graphics {


//========
// Common
//========

Handle<String> SymbolString(Symbols symbol)
{
WCHAR psymbol[2]={ (WCHAR)symbol, 0 };
return new String(psymbol);
}

Platform::String^ PlatformSymbolString(Symbols symbol)
{
WCHAR psymbol[2]={ (WCHAR)symbol, 0 };
return ref new Platform::String(psymbol);
}

}