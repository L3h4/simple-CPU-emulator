#pragma once
#include<iostream>
#include<stdio.h>
#include<fstream>

#include"Ox64cmCPU.h"
#include"Status.h"
#include"Memory.h"
#include"GPU.h"

#define u8 uint8_t
#define u16 uint16_t

class Ox64cmCPU;


// клас шина
class Bus
{
public:
	Bus();
	Bus(Status *s);

	void connect_cpu(Ox64cmCPU *c);

	void load_from_file(std::string file_name);


	template<typename T>
	void write(u16 address, T value)// метод записи НА ШИНУ
	{
		if (address >= 0 && address < 2048)
			RAM.write<T>(address,value);
		//else if (address >= 2048 && address < 2048 + 1024)
			//gpu.write<T>(address, value);
		else
		{
			char buf[100];
			sprintf_s(buf, "Cant read [0x%.4X] (BAD_ADDRESS)", address);
			throw buf;
		}
	}

	template<typename T>
	T  read(u16 address)// метод чтения ИЗ ШИНЫ
	{
		if (address >= 0 && address < 2048)
			return RAM.read<T>(address);
		//else if (address >= 2048 && address < 2048+1024)
		//	return gpu.read<T>(address);
		else
		{
			char buf[100];
			sprintf_s(buf, "Cant read [0x%.4X] (BAD_ADDRESS)", address);
			throw buf;
		}
	}

public: // девайсы на шине
	Memory RAM; // ОЗУ
	GPU gpu; // видео адаптер

private:
	Status *status;
	Ox64cmCPU *cpu;
};