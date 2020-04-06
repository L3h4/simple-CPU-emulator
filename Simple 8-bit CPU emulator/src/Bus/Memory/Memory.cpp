#pragma once
#include "Memory.h"





Memory::Memory()
{
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