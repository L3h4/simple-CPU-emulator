#include "Bus.h"
#include<stdio.h>



Bus::Bus(Status *s)
{
	this->RAM = Memory();
	this->status = s;
}

void Bus::connect_cpu(Ox64cmCPU *c)
{
	this->cpu = c;
}


u8 Bus::read(u16 addres)
{
	if (addres < 2048) // ��� �� ���� ����� ����� �� 0x0 �� 0x0800 (2048 ����) ������������ ���� �� ������ � ���� ��������, �� �� �������� � ���
	{
		return this->RAM.read(addres);
	}
	else // ����� ��������� ������
	{
		char buf[40];
		sprintf_s(buf, "Can't from address 0x%.4X", addres);
		this->status->raise_exception(cpu->PC.value, status->BAD_ADDRESS, buf);
	}
		return 0;
}

void Bus::write(u16 addres, u8 data)
{
	if (addres < 2048) // ��� �� ���� ����� ����� �� 0x0 �� 0x0800 (2048 ����) ������������ ���� �� ������ � ���� ��������, �� �� �������� � ���
	{
		this->RAM.write(addres, data);
	}
	else // ����� ��������� ������
	{
		char buf[40];
		sprintf_s(buf, "Can't write 0x%.2X to address 0x%.4X", data, addres);
		this->status->raise_exception(cpu->PC.value, status->BAD_ADDRESS, buf);
	}
}


// ==============================RAM=================================

void Bus::Memory::write(u16 addres, u8 value)
{
	if (addres < 2048)
		this->memory[addres] = value;
}

u8  Bus::Memory::read(u16 addres)
{
	if (addres < 2048)
		return this->memory[addres];
}

void Bus::Memory::print()
{
	// ����� ��������� ���� �������� � �������(������ �������� ��������)
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
