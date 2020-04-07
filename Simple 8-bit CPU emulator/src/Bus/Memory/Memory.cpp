#pragma once
#include "Memory.h"





Memory::Memory()
{
	for (int i = 0; i < 2048; i++)
	{
		memory[i] = 0x1F;
	}
	allocated = {
		{ 0x0, 0x06F0, READ | WRITE | EXECUTE, READ | WRITE | EXECUTE, READ | WRITE | EXECUTE },
		{ 0x07F0, 0xF, READ, READ, NO }
	};
}

Memory::~Memory()
{
}

void Memory::print()
{
	// метод отрисовки всех значений в консоль(рисует красивую табличку)
	printf("MEMORY\n==========================================================================");
	for (int i = 0; i < sizeof(this->memory); i++)
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
				throw (std::string)buf;
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
			throw (std::string)buf;
		}
	}
	char buf[100];
	sprintf_s(buf, "Cant execute [0x%.4X] (BAD_ADDRESS)", address);
	throw (std::string)buf;
}

bool RamVec::in(u16 addres)
{
	return (this->addres <= addres && addres <= this->addres + size && size > 0) || (size < 0 && this->addres + size <= addres && addres <= this->addres);
}
