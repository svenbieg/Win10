//================
// SerialPort.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "SerialPort.h"

using namespace Concurrency;
using namespace Windows::Storage::Streams;


//===========
// Namespace
//===========

namespace Devices {
	namespace Serial {


//==================
// Con-/Destructors
//==================

SerialPort::SerialPort(Platform::String^ hid):
BaudRate(this, 115200)
{
create_task(SerialDevice::FromIdAsync(hid)).then([this](SerialDevice^ hdevice)
	{
	hDevice=hdevice;
	hDevice->BaudRate=BaudRate;
	hReader=ref new DataReader(hDevice->InputStream);
	hReader->InputStreamOptions=InputStreamOptions::Partial;
	hWriter=ref new DataWriter(hDevice->OutputStream);
	BaudRate.Changed.Add(this, &SerialPort::OnBaudRateChanged);
	});
}

SerialPort::~SerialPort()
{
Close();
}


//==============
// Input-Stream
//==============

SIZE_T SerialPort::Available()
{
if(!hReader)
	return 0;
return hReader->UnconsumedBufferLength;
}

SIZE_T SerialPort::Read(VOID* pbuf, SIZE_T usize)
{
if(!hReader)
	return 0;
SIZE_T uavailable=hReader->UnconsumedBufferLength;
SIZE_T uread=MIN(usize, uavailable);
if(!pbuf)
	{
	for(SIZE_T u=0; u<uread; u++)
		hReader->ReadByte();
	return uread;
	}
hReader->ReadBytes(Platform::ArrayReference<BYTE>((BYTE*)pbuf, uread));
return uread;
}


//===============
// Output-Stream
//===============

VOID SerialPort::Flush()
{
if(!hWriter)
	return;
try
	{
	create_task(hWriter->StoreAsync()).wait();
	}
catch(Platform::Exception^)
	{
	Disconnected(this);
	}
}

SIZE_T SerialPort::Write(VOID const* pbuf, SIZE_T usize)
{
if(!hWriter)
	return 0;
hWriter->WriteBytes(Platform::ArrayReference<BYTE>((BYTE*)pbuf, usize));
return usize;
}


//========
// Common
//========

VOID SerialPort::Close()
{
BaudRate.Changed.Remove(this);
hDevice=nullptr;
hReader=nullptr;
hWriter=nullptr;
}

SIZE_T SerialPort::Receive(SIZE_T usize)
{
if(!hReader)
	return 0;
TimeSpan timeout;
timeout.Duration=UINT64_MAX;
hDevice->ReadTimeout=timeout;
SIZE_T uavailable=0;
try
	{
	uavailable=create_task(hReader->LoadAsync(usize)).get();
	}
catch(Platform::Exception^)
	{
	Disconnected(this);
	}
return uavailable;
}

SIZE_T SerialPort::Receive(SIZE_T usize, UINT ums)
{
if(!hReader)
	return 0;
TimeSpan timeout;
timeout.Duration=ums*10000;
hDevice->ReadTimeout=timeout;
SIZE_T uavailable=0;
try
	{
	uavailable=create_task(hReader->LoadAsync(usize)).get();
	}
catch(Platform::Exception^)
	{
	Disconnected(this);
	}
return uavailable;
}


//================
// Common Private
//================

VOID SerialPort::OnBaudRateChanged(UINT ubaud)
{
if(hDevice)
	hDevice->BaudRate=ubaud;
}

}}