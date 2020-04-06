#pragma once
#include<iostream>
#include<fstream>

#include"../cpu/Ox64cmCPU.h"
#include"../Status.hpp"
#include"Memory/Memory.h"

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


public: // девайсы на шине (ОЗУ)
	Memory RAM; // ОЗУ


private:
		Status *status;
		Ox64cmCPU *cpu;
};