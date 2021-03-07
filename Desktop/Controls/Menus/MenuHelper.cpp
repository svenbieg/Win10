//================
// MenuHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "MenuHelper.h"


//===========
// Namespace
//===========

namespace Desktop {
	namespace Controls {
		namespace Menus {


//========
// Common
//========

VOID GetMenuString(Handle<String>* phtext, Handle<String>* phacc)
{
if(!phtext)
	return;
Handle<String>& htext=*phtext;
auto hres=GetResourceString(htext);
if(hres)
	htext=hres;
LPCWSTR ptext=htext->Begin();
UINT upos=0;
if(StringFind(ptext, "&", &upos))
	{
	WCHAR acc=CharToCapital(ptext[upos+1]);
	if(acc)
		{
		WCHAR pacc[]={ CharToCapital(ptext[upos+1]), 0 };
		if(phacc)
			*phacc=pacc;
		}
	UINT ulen=StringLength(ptext);
	WCHAR pstr[256];
	if(upos>0)
		StringCopy(pstr, 256, ptext, upos);
	StringCopy(&pstr[upos], 256-upos, &ptext[upos+1]);
	htext=pstr;
	}
}

}}}