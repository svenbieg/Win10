//==============
// SerialPort.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"
#include "Devices/Serial/BaudRate.h"


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
	SerialPort(Serial::BaudRate BaudRate=Serial::BaudRate::Baud115200);
	~SerialPort();

	// Common
	VOID Abort();
	Property<SerialPort, Serial::BaudRate> BaudRate;
	VOID Cancel();
	VOID ClearBuffer();
	VOID Close();
	VOID Connect(Platform::String^ Id);
	Event<SerialPort> Connected;
	Event<SerialPort> DataReceived;
	Event<SerialPort> Disconnected;
	VOID Listen(UINT Size=4096);
	UINT Load(UINT Size, UINT Timeout=0);
	VOID SetDataTerminalReady(BOOL Enabled);
	VOID SetRequestToSend(BOOL Enabled);

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	VOID CloseInternal();
	VOID DoListen(Handle<Task> Task, UINT Size);
	VOID DoTimeout(Handle<Task> Task, UINT Timeout);
	VOID Initialize();
	VOID OnBaudRateChanged(Serial::BaudRate BaudRate);
	CriticalSection cCriticalSection;
	SerialDevice^ hDevice;
	Platform::String^ hDeviceId;
	DataReader^ hReader;
	Handle<Task> hListenTask;
	Handle<Task> hTimeoutTask;
	DataWriter^ hWriter;
};

}}