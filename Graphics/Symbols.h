//===========
// Symbols.h
//===========

#pragma once


//===========
// Namespace
//===========

namespace Graphics {


//=========
// Symbols
//=========

enum class Symbols: WCHAR
{
None=0,
Check=0xE081,
House=0xE10F,
Point=0xE1F5,
Upload=0xE17C,
Hamburger=0xE700
};

Handle<String> SymbolString(Symbols Symbol);
Platform::String^ PlatformSymbolString(Symbols Symbol);

}
