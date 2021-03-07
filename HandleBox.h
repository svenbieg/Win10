
//==========
// Handle.h
//==========

#pragma once


//=======
// Using
//=======

#include "StringHelper.h"


//========
// Handle
//========

template <class _obj_t>
class HandleBox
{
public:
	// Con-/Destructors
	HandleBox(): hObject(nullptr) {}
	HandleBox(_obj_t^ Object): hObject(Object) {}
	HandleBox(HandleBox const& Handle): hObject(Handle.hObject) {}
	HandleBox(HandleBox && Handle): hObject(Handle.hObject) { Handle.hObject=nullptr; }
	~HandleBox() { hObject=nullptr; }

	// Acces
	operator _obj_t^()const { return hObject; }

	// Comparison
	BOOL operator==(HandleBox const& Handle)const { return hObject==Handle.hObject; }
	BOOL operator!=(HandleBox const& Handle)const { return hObject!=Handle.hObject; }
	BOOL operator>(HandleBox const& Handle)const { return hObject>Handle.hObject; }
	BOOL operator>=(HandleBox const& Handle)const { return hObject>=Handle.hObject; }
	BOOL operator<(HandleBox const& Handle)const { return hObject<Handle.hObject; }
	BOOL operator<=(HandleBox const& Handle)const { return hObject<=Handle.hObject; }

	// Assignment
	HandleBox& operator=(HandleBox const& Handle) { hObject=Handle.hObject; return *this; }

private:
	// Common
	_obj_t^ hObject;
};


//===============
// String-Handle
//===============

template <>
class HandleBox<Platform::String>
{
private:
	// Using
	using String=Platform::String;

public:
	// Con-/Destructors
	HandleBox(): hString(nullptr) {}
	HandleBox(String^ String): hString(String) {}
	HandleBox(HandleBox const& Handle): hString(Handle.hString) {}
	~HandleBox() { hString=nullptr; }

	// Acces
	operator String^()const { return hString; }

	// Comparison
	BOOL operator==(HandleBox const& Handle)const { return StringCompare(hString->Begin(), Handle.hString->Begin())==0; }
	BOOL operator!=(HandleBox const& Handle)const { return StringCompare(hString->Begin(), Handle.hString->Begin())!=0; }
	BOOL operator>(HandleBox const& Handle)const { return StringCompare(hString->Begin(), Handle.hString->Begin())>0; }
	BOOL operator>=(HandleBox const& Handle)const { return StringCompare(hString->Begin(), Handle.hString->Begin())>=0; }
	BOOL operator<(HandleBox const& Handle)const { return StringCompare(hString->Begin(), Handle.hString->Begin())<0; }
	BOOL operator<=(HandleBox const& Handle)const { return StringCompare(hString->Begin(), Handle.hString->Begin())<=0; }

	// Assignment
	HandleBox& operator=(HandleBox const& Handle) { hString=Handle.hString; return *this; }

private:
	// Common
	String^ hString;
};
