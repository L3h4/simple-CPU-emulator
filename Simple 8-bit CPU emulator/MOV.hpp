#include "Ox64cmCPU.h"
#pragma once

void Ox64cmCPU::MOV()
{
	// обработчик всех типов операции MOV
	if (arg1.type == REGISTER)
	{
		if (arg2.type == IMMDATA)
		{
			arg1.reg->lo = arg2.value;
		}
		else if (arg2.type == REGISTER)
		{
			arg1.reg->lo = arg2.reg->lo;
		}
		else if (arg2.type == ADDRESS)
		{
			arg1.reg->lo = bus->read(arg2.address);
		}
		else
		{
			throw "Unknown data source";
		}
	}
	else if (arg1.type == REGISTER16)
	{
		if (arg2.type == IMMDATA16)
		{
			arg1.reg->value = arg2.value16;
		}
		else if (arg2.type == REGISTER16)
		{
			arg1.reg->value = arg2.reg->value;
		}
		else if (arg2.type == ADDRESS16)
		{
			arg1.reg->value = (bus->read(arg2.address) << 8) + bus->read(arg2.address + 1);
		}
		else
		{
			throw "Unknown data source";
		}
	}
	else if (arg1.type == ADDRESS)
	{
		if (arg2.type == IMMDATA)
		{
			bus->write(arg1.address, arg2.value);
		}
		else if (arg2.type == REGISTER)
		{
			bus->write(arg1.address, arg2.reg->lo);
		}
		else if (arg2.type == ADDRESS)
		{
			bus->write(arg1.address, bus->read(arg2.address));
		}
		else
		{
			throw "Unknown data source";
		}
	}
	else if (arg1.type == ADDRESS16)
	{
		if (arg2.type == IMMDATA16)
		{
			bus->write(arg1.address, arg2.value16 >> 8);
			bus->write(arg1.address + 1, arg2.value16);
		}
		else if (arg2.type == REGISTER16)
		{
			bus->write(arg1.address, arg2.reg->value >> 8);
			bus->write(arg1.address + 1, arg2.reg->value);
		}
		else if (arg2.type == ADDRESS16)
		{
			bus->write(arg1.address, bus->read(arg2.address));
			bus->write(arg1.address + 1, bus->read(arg2.address + 1));
		}
		else
		{
			throw "Unknown data source";
		}
	}
	else
	{
		throw "Unknown source";
	}
}
