#include "Bus.h"
#include<stdio.h>



Bus::Bus()
{
	this->RAM = Memory();
}


u8* Bus::read(u16 addres)
{
	if (addres < 2048)
		return &this->RAM.memory[addres];
}

void Bus::write(u16 addres, u8 data)
{
	if (addres < 2048)
		this->RAM.write(addres, data);
}


// ==============================RAM=================================

void Bus::Memory::write(u16 addres, u8 value)
{
	if (addres < 2048)
		this->memory[addres] = value;
}

u8 * Bus::Memory::read(u16 addres)
{
	if (addres < 2048)
		return &this->memory[addres];
}

void Bus::Memory::print()
{
	printf("MEMORY");
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
