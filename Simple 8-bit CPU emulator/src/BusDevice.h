#pragma once
#include <iostream>

#define u8 uint8_t 
#define u16 uint16_t

class BusDevice
{
protected:
	virtual u16 read16(u16 address) = 0;
	virtual u8 read8(u16 address) = 0;

	virtual void write16(u16 address, u16 data) = 0;
	virtual void write8(u16 address, u8 data) = 0;
public:
	BusDevice();
	template<class T>
	T read(u16 address);
	template<class T>
	void write(u16 address, T data);
	virtual ~BusDevice();
};

template<class T>
inline T BusDevice::read(u16 address)
{
	if (typeid(T) == typeid(u16))
	{
		return read16(address);
	}
	else if (typeid(T) == typeid(u8))
	{
		return read8(address);
	}
	else
		throw "Invalid type";
}

template<class T>
inline void BusDevice::write(u16 address, T data)
{
	if (typeid(T) == typeid(u16))
	{
		write16(address, data);
	}
	else if (typeid(T) == typeid(u8))
	{
		write8(address, data);
	}
	else
		throw "Invalid type";
}
