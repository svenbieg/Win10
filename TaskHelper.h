//==============
// TaskHelper.h
//==============

#pragma once


//=======
// Using
//=======

#include <concrt.h>
#include <ppltasks.h>


//========
// Common
//========

using AsyncAction=Windows::Foundation::IAsyncAction;
template <class TResult> using AsyncOperation=Windows::Foundation::IAsyncOperation<TResult>;

template <class _ReturnType> inline Concurrency::task<_ReturnType> CreateTask(Concurrency::task<_ReturnType> const& Task)
{
return Concurrency::create_task(Task);
}

template <class _Ty> inline Concurrency::task<typename Concurrency::details::_TaskTypeFromParam<_Ty>::_Type> CreateTask(_Ty Task, Concurrency::task_options Options=Concurrency::task_options())
{
return Concurrency::create_task(Task, Options);
}
