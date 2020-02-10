#pragma once
#include<iostream>
#include"Ox64cmCPU.h"

#define u8 uint8_t
#define u16 uint16_t

class Bus
{
public:
	Bus();

private:
	class Memory
	{
	public:
		u8 memory[1024 * 2]; // 2κα ξησ
		void write(u16 addres, u8 value);
		u8* read(u16 addres);
		void print();
	};

public:
	u8* read(u16 addres);

	void write(u16 addres, u8 data);

	Memory RAM;
};