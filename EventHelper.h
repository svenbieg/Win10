//===============
// EventHelper.h
//===============

#pragma once


//========
// Common
//========

using EventToken=Windows::Foundation::EventRegistrationToken;
template <class TSender, class TResult> using TypedEventHandler=Windows::Foundation::TypedEventHandler<TSender, TResult>;
