#pragma once
#include "Memory.h"





Memory::Memory()
{
	memory = new u8[2048]();
	std::fill_n(memory, 2048, 0x1F);
}

Memory::Memory(const Memory & obj) : Memory()
{
	for (int i = 0; i < 2048; i++)
	{
		memory[i] = obj.memory[i];
	}
	allocated = obj.allocated;
}

Memory::Memory(Memory && obj)
{

	memory = obj.memory;
	obj.memory = nullptr;
}

Memory::~Memory()
{
	delete[] this->memory;
}

Memory & Memory::operator=(const Memory & obj)
{
	if (this == &obj)
		return *this;

	for (int i = 0; i < 2048; i++)
	{
		memory[i] = obj.memory[i];
	}
	allocated = obj.allocated;

	return *this;
}

Memory & Memory::operator=(Memory && obj)
{
	if (this == &obj)
		return *this;

	memory = obj.memory;
	obj.memory = nullptr;

	return *this;
}

u16 Memory::read16(u16 address)
{
	for (RamVec rv : allocated)
		if (rv.in(address))
		{
			if (rv.rights_KERNEL & READ)
				return (u16)(memory[address] << 8) + memory[address + 1];
				
			else
			{
				char buf[100];
				sprintf_s(buf, "Cant read [0x%.4X] (UNREADABLE_MEMORY)", address);
				throw buf;
			}
		}

	char buf[100];
	sprintf_s(buf, "Cant read [0x%.4X] (BAD_ADDRESS)", address);
	throw buf;
}

u8 Memory::read8(u16 address)
{
	for (RamVec rv : allocated)
		if (rv.in(address))
		{
			if (rv.rights_KERNEL & READ)
				return memory[address];

			else
			{
				char buf[100];
				sprintf_s(buf, "Cant read [0x%.4X] (UNREADABLE_MEMORY)", address);
				throw buf;
			}
		}

	char buf[100];
	sprintf_s(buf, "Cant read [0x%.4X] (BAD_ADDRESS)", address);
	throw buf;
}

void Memory::write16(u16 address, u16 data)
{
	for (RamVec rv : allocated)
		if (rv.in(address))
		{
			if (rv.rights_KERNEL & WRITE)
			{
					memory[address] = (u8)(data >> 8);
					memory[address + 1] = (u8)data;
					return;
			}
			else
			{
				char buf[100];
				sprintf_s(buf, "Cant write [0x%.4X] (UNWRITABLE_MEMORY)", address);
				throw buf;
			}
		}

	char buf[100];
	sprintf_s(buf, "Cant write [0x%.4X] (BAD_ADDRESS)", address);
	throw buf;
}

void Memory::write8(u16 address, u8 data)
{
	for (RamVec rv : allocated)
		if (rv.in(address))
		{
			if (rv.rights_KERNEL & WRITE)
			{
				memory[address] = data;
				return;
			}
			else
			{
				char buf[100];
				sprintf_s(buf, "Cant write [0x%.4X] (UNWRITABLE_MEMORY)", address);
				throw buf;
			}
		}

	char buf[100];
	sprintf_s(buf, "Cant write [0x%.4X] (BAD_ADDRESS)", address);
	throw buf;
}

void Memory::print()
{
	// метод отрисовки всех значений в консоль(рисует красивую табличку)
	printf("MEMORY\n==========================================================================");
	for (int i = 0; i < 2048; i++)
	{
		if (i % 16 == 0)
		{
			printf("\n");
			printf("  0x%.4X  |  ", i);
		}
		printf(" %.2X ", this->memory[i]);
	}
	printf("\n==========================================================================\n\n");
}

u8 Memory::fetch_instruction(u16 address)
{
	for (RamVec rv : allocated)
	{
		if (rv.in(address))
		{
			if (rv.rights_KERNEL & EXECUTE)
			{
				return read<u8>(address);
			}
			else
			{
				char buf[100];
				sprintf_s(buf, "Cant execute [0x%.4X] (UNEXECUTABLE_MEMORY)", address);
				throw buf;
			}
		}
	}
	if (stack.in(address))
	{
		if (stack.rights_KERNEL & EXECUTE)
		{
			return read<u8>(address);
		}
		else
		{
			char buf[100];
			sprintf_s(buf, "Cant execute [0x%.4X] (stack) (UNEXECUTABLE_MEMORY)", address);
			throw buf;
		}
	}
	char buf[100];
	sprintf_s(buf, "Cant execute [0x%.4X] (BAD_ADDRESS)", address);
	throw buf;
}

bool RamVec::in(u16 addres) const
{
	return (this->addres <= addres && addres <= this->addres + size && size > 0) || (size < 0 && this->addres + size <= addres && addres <= this->addres);
}
