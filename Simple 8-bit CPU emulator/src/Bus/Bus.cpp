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

void Bus::load_from_file(std::string file_name)
{
	// Читаю бинарник сишным способом потому что с++ный способ не работает
	FILE* f;
	fopen_s(&f, file_name.c_str(), "rb");
	
	if (!f)
	{
		char buf[100];
		sprintf_s(buf, "Cant open file \"%s\"", file_name.c_str());

		throw (std::string)buf;
	}



	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	u8* bytes = new u8[size];

	fread_s(bytes, size, 1, size, f);
	
	fclose(f);

	
	for (int i = 0; i < size; i++)// заделка под чтение хедера и всего остального
	{
		RAM.memory[i] = (u8)bytes[i];
	}

	delete bytes;
}

/*
u8 Bus::read(u16 addres)
{
	if (addres < 2048) // ОЗУ на шине имеет адрес от 0x0 до 0x0800 (2048 байт) соответственно если мы попали в этот диапазон, то мы работаем с ОЗУ
	{
		return this->RAM.read<u8>(addres);
	}
	else // иначе поднимаем ошибку
	{
		char buf[40];
		sprintf_s(buf, "Can't read from address 0x%.4X", addres);
		this->status->raise_exception(cpu->regs.PC.value, status->BAD_ADDRESS, buf);
	}
		return 0;
}

void Bus::write(u16 addres, u8 data)
{
	if (addres < 2048) // ОЗУ на шине имеет адрес от 0x0 до 0x0800 (2048 байт) соответственно если мы попали в этот диапазон, то мы работаем с ОЗУ
	{
		this->RAM.write(addres, data);
	}
	else // иначе поднимаем ошибку
	{
		char buf[40];
		sprintf_s(buf, "Can't write 0x%.2X to address 0x%.4X", data, addres);
		this->status->raise_exception(cpu->regs.PC.value, status->BAD_ADDRESS, buf);
	}
}
*/
