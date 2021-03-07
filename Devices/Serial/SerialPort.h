//==============
// SerialPort.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Serial {


//=============
// Serial-Port
//=============

class SerialPort: public Storage::Streams::RandomAccessStream
{
private:
	// Using
	using SerialDevice=Windows::Devices::SerialCommunication::SerialDevice;
	using DataReader=Windows::Storage::Streams::DataReader;
	using DataWriter=Windows::Storage::Streams::DataWriter;

public:
	// Con-/Destructors
	SerialPort(Platform::String^ Id);
	~SerialPort();

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

	// Common
	Property<SerialPort, UINT> BaudRate;
	VOID Close();
	Event<SerialPort> Disconnected;
	SIZE_T Receive(SIZE_T Size);
	SIZE_T Receive(SIZE_T Size, UINT MilliSeconds);

private:
	// Common
	VOID OnBaudRateChanged(UINT BaudRate);
	SerialDevice^ hDevice;
	DataReader^ hReader;
	DataWriter^ hWriter;
};

}}