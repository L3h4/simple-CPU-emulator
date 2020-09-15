#pragma once
#include<iostream>
#include<fstream>

#include"../cpu/Ox64cmCPU.h"
#include"../Status.hpp"
#include"Memory/Memory.h"
#include"GPU/GPU.h"

#define u8 uint8_t
#define u16 uint16_t

class Ox64cmCPU;
class Memory;

// клас шина
class Bus
{
public:
	Bus() {}
	Bus(Status *s);

	void connect_cpu(Ox64cmCPU *c);

	
public:
	void load_from_file(std::string file_name);
	//u8 read(u16 addres); // метод чтения ИЗ ШИНЫ

	//void write(u16 addres, u8 data); // метод записи НА ШИНУ
	template<typename T>
	void write(u16 address, T value)
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
	T  read(u16 address)
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