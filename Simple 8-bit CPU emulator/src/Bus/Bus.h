#pragma once
#include<iostream>
#include"../cpu/Ox64cmCPU.h"
#include"../Status.hpp"

#define u8 uint8_t
#define u16 uint16_t

class Ox64cmCPU;

// клас шина
class Bus
{
public:
	Bus() {}
	Bus(Status *s);

	void connect_cpu(Ox64cmCPU *c);

private:
	class Memory // клас ОЗУ
	{
	public:
		u8 memory[1024 * 2]; // 2кб озу
		void write(u16 addres, u8 value); // метод записи В ПАМЯТЬ
		u8 read(u16 addres); // метод чтения ИЗ ПАМЯТИ
		void print();
	};
public:
	u8 read(u16 addres); // метод чтения ИЗ ШИНЫ

	void write(u16 addres, u8 data); // метод записи НА ШИНУ


public: // девайсы на шине (ОЗУ)
	Memory RAM; // ОЗУ


private:
		Status *status;
		Ox64cmCPU *cpu;
};