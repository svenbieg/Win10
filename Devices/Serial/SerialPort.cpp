//================
// SerialPort.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "SerialPort.h"

using namespace Concurrency;
using namespace Windows::Devices::SerialCommunication;
using namespace Windows::Storage::Streams;


//===========
// Namespace
//===========

namespace Devices {
	namespace Serial {


//==================
// Con-/Destructors
//==================

SerialPort::SerialPort(Serial::BaudRate baud):
BaudRate(this, baud)
{
BaudRate.Changed.Add(this, &SerialPort::OnBaudRateChanged);
}

SerialPort::~SerialPort()
{
CloseInternal();
}


//========
// Common
//========

VOID SerialPort::Abort()
{
Cancel();
ScopedLock lock(cCriticalSection);
SerialDevice^ device=create_task(SerialDevice::FromIdAsync(hDeviceId)).get();
if(!device)
	{
	Disconnected(this);
	return;
	}
hDevice=device;
Initialize();
}

VOID SerialPort::Cancel()
{
CloseInternal();
}

VOID SerialPort::ClearBuffer()
{
ScopedLock lock(cCriticalSection);
if(!hReader)
	return;
SIZE_T available=hReader->UnconsumedBufferLength;
if(!available)
	return;
try
	{
	for(SIZE_T u=0; u<available; u++)
		hReader->ReadByte();
	}
catch(Platform::Exception^)
	{
	if(hDevice)
		{
		lock.Release();
		Disconnected(this);
		}
	}
}

VOID SerialPort::Close()
{
ScopedLock lock(cCriticalSection);
if(!hDevice)
	return;
CloseInternal();
}

VOID SerialPort::Connect(Platform::String^ hid)
{
ScopedLock lock(cCriticalSection);
if(hDevice)
	return;
hDeviceId=hid;
Handle<SerialPort> hserial=this;
create_task(SerialDevice::FromIdAsync(hDeviceId)).then([this, hserial](SerialDevice^ hdevice)
	{
	if(!hdevice)
		{
		Disconnected(this);
		return;
		}
	ScopedLock lock(cCriticalSection);
	hDevice=hdevice;
	Initialize();
	lock.Release();
	Connected(this);
	});
}

VOID SerialPort::Listen(UINT size)
{
ScopedLock lock(cCriticalSection);
if(!hReader)
	return;
if(hListenTask)
	return;
hListenTask=CreateTask(this, &SerialPort::DoListen, size);
}

UINT SerialPort::Load(UINT size, UINT timeout)
{
ScopedLock lock(cCriticalSection);
if(!hReader)
	return 0;
if(hListenTask)
	return 0;
if(hReader->UnconsumedBufferLength)
	return hReader->UnconsumedBufferLength;
if(timeout)
	hTimeoutTask=CreateTask(this, &SerialPort::DoTimeout, timeout);
UINT available=0;
try
	{
	available=create_task(hReader->LoadAsync(size)).get();
	}
catch(Platform::Exception^)
	{
	if(hDevice)
		{
		lock.Release();
		Disconnected(this);
		}
	return 0;
	}
if(hTimeoutTask)
	{
	hTimeoutTask->Cancel=true;
	hTimeoutTask->Wait();
	hTimeoutTask=nullptr;
	}
return available;
}

VOID SerialPort::SetDataTerminalReady(BOOL enabled)
{
ScopedLock lock(cCriticalSection);
if(hDevice)
	hDevice->IsDataTerminalReadyEnabled=enabled;
}

VOID SerialPort::SetRequestToSend(BOOL enabled)
{
ScopedLock lock(cCriticalSection);
if(hDevice)
	hDevice->IsRequestToSendEnabled=enabled;
}


//==============
// Input-Stream
//==============

SIZE_T SerialPort::Available()
{
ScopedLock lock(cCriticalSection);
if(!hReader)
	return 0;
return hReader->UnconsumedBufferLength;
}

SIZE_T SerialPort::Read(VOID* pbuf, SIZE_T size)
{
ScopedLock lock(cCriticalSection);
if(!hReader)
	return 0;
UINT available=hReader->UnconsumedBufferLength;
UINT read=(UINT)MIN(size, available);
try
	{
	if(!pbuf)
		{
		for(SIZE_T u=0; u<read; u++)
			hReader->ReadByte();
		return read;
		}
	hReader->ReadBytes(Platform::ArrayReference<BYTE>((BYTE*)pbuf, read));
	}
catch(Platform::Exception^)
	{
	if(hDevice)
		{
		lock.Release();
		Disconnected(this);
		}
	return 0;
	}
return read;
}


//===============
// Output-Stream
//===============

VOID SerialPort::Flush()
{
ScopedLock lock(cCriticalSection);
if(!hWriter)
	return;
if(!hWriter->UnstoredBufferLength)
	return;
try
	{
	create_task(hWriter->StoreAsync()).wait();
	}
catch(Platform::Exception^)
	{
	if(hDevice)
		{
		lock.Release();
		Disconnected(this);
		}
	return;
	}
}

SIZE_T SerialPort::Write(VOID const* pbuf, SIZE_T size)
{
ScopedLock lock(cCriticalSection);
if(!hWriter)
	return 0;
try
	{
	hWriter->WriteBytes(Platform::ArrayReference<BYTE>((BYTE*)pbuf, (UINT)size));
	}
catch(Platform::Exception^)
	{
	if(hDevice)
		{
		lock.Release();
		Disconnected(this);
		}
	}
return size;
}


//================
// Common Private
//================

VOID SerialPort::CloseInternal()
{
hDevice=nullptr;
hReader=nullptr;
hWriter=nullptr;
if(hListenTask)
	{
	hListenTask->Cancel=true;
	hListenTask->Wait();
	hListenTask=nullptr;
	}

}

VOID SerialPort::DoListen(Handle<Task> task, UINT size)
{
while(!task->Cancel)
	{
	UINT available=hReader->UnconsumedBufferLength;
	if(!available)
		{
		try
			{
			available=create_task(hReader->LoadAsync(size)).get();
			}
		catch(Platform::Exception^)
			{
			if(hDevice)
				Disconnected(this);
			return;
			}
		}
	DataReceived(this);
	}
}

VOID SerialPort::DoTimeout(Handle<Task> task, UINT timeout)
{
UINT count=timeout/10;
for(UINT u=0; u<count; u++)
	{
	if(task->Cancel)
		return;
	Sleep(10);
	}
Abort();
}

VOID SerialPort::Initialize()
{
TimeSpan time;
time.Duration=-1;
hDevice->BaudRate=(UINT)BaudRate.GetInternal();
hDevice->DataBits=8;
hDevice->Handshake=SerialHandshake::None;
hDevice->Parity=SerialParity::None;
hDevice->ReadTimeout=time;
hDevice->StopBits=SerialStopBitCount::One;
hDevice->WriteTimeout=time;
hReader=ref new DataReader(hDevice->InputStream);
hReader->InputStreamOptions=InputStreamOptions::Partial;
hWriter=ref new DataWriter(hDevice->OutputStream);
}

VOID SerialPort::OnBaudRateChanged(Serial::BaudRate baud)
{
ScopedLock lock(cCriticalSection);
if(hDevice)
	hDevice->BaudRate=(UINT)baud;
}

}}