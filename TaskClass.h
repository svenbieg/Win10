//=============
// TaskClass.h
//=============

#pragma once


//=======
// Using
//=======

#include <concrt.h>
#include <ppltasks.h>
#include "Procedure.h"


//======
// Task
//======

class Task: public Object
{
public:
	// Common
	volatile BOOL Cancel;
	VOID Wait();

protected:
	// Con-/Destructors
	Task() {}

	// Common
	Handle<Task> hThis;
};


//============
// Task Typed
//============

template <class _owner_t, class... _args_t>
class TaskTyped: public Task
{
public:
	// Using
	typedef VOID (_owner_t::*TaskProc)(_args_t...);

	// Con-/Destructors
	TaskTyped(_owner_t* Owner, TaskProc Procedure):
		hOwner(Owner),
		pProcedure(Procedure)
		{}

	VOID Run(_args_t... Arguments)
		{
		hThis=this;
		Concurrency::create_task([this, Arguments...]()
			{
			(hOwner->*pProcedure)(Arguments...);
			hThis=nullptr;
			});
		}
private:
	// Common
	Handle<_owner_t> hOwner;
	TaskProc pProcedure;
};

template <class _owner_t, class... _args_t>
class TaskTyped<_owner_t, Handle<Task>, _args_t...>: public Task
{
public:
	// Using
	typedef VOID (_owner_t::*TaskProc)(Handle<Task>, _args_t...);

	// Con-/Destructors
	TaskTyped(_owner_t* Owner, TaskProc Procedure):
		hOwner(Owner),
		pProcedure(Procedure)
		{}

	VOID Run(_args_t... Arguments)
		{
		hThis=this;
		Concurrency::create_task([this, Arguments...]()
			{
			(hOwner->*pProcedure)(this, Arguments...);
			hThis=nullptr;
			});
		}
private:
	// Common
	Handle<_owner_t> hOwner;
	TaskProc pProcedure;
};
