#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>



#include "BusDevice.h"

enum Rights
{
	KERNEL,
	ROOT,
	USER
};


enum MemoryRights
{
	NO = 0,
	READ = (1 << 0),
	WRITE = (1 << 1),
	EXECUTE = (1 << 2),

};

struct RamVec
{
	u16 addres;
	int size;

	int rights_KERNEL = READ | WRITE;
	int rights_ROOT = READ | WRITE;
	int rights_USER = READ;
	
	bool in(u16 addres) const;
};


class Memory : public BusDevice // ���� ���
{
	u8 *memory = nullptr; // 2�� ���
public:
	Memory();
	Memory(const Memory& obj);
	Memory(Memory&& obj);
	~Memory();

	Memory& operator=(const Memory& obj);
	Memory& operator=(Memory&& obj);

	u16 read16(u16 address)override;
	u8 read8(u16 address)override;

	void write16(u16 address, u16 data)override;
	void write8(u16 address, u8 data)override;
/*
	template<typename T>
	void write(u16 address, T value)
	{
		for (RamVec rv : allocated)
		{
			if (rv.in(address))
			{
				if (rv.rights_KERNEL & WRITE)
				{
					if (typeid(T) == typeid(u16))
					{
						memory[address] = (u8)(value >> 8);
						memory[address + 1] = (u8)value;
						return;
					}
					else
					{
						memory[address] = (u8)value;
						return;
					}
				}
				else
				{
					char buf[100];
					sprintf_s(buf, "Cant write [0x%.4X] (UNWRITABLE_MEMORY)", address);
					throw buf;
				}
			}
		}
		char buf[100];
		sprintf_s(buf, "Cant write [0x%.4X] (BAD_ADDRESS)", address);
		throw buf;		
	}

	template<typename T>
	T  read(u16 address)
	{
		for (RamVec rv : allocated)
		{
			if (rv.in(address))
			{
				if (rv.rights_KERNEL & READ)
				{
					if (typeid(T) == typeid(u16))
					{
						return (u16)(memory[address] << 8) + memory[address + 1];
					}
					else
					{
						return memory[address];
					}
				}
				else 
				{
					char buf[100];
					sprintf_s(buf, "Cant read [0x%.4X] (UNREADABLE_MEMORY)", address);
					throw buf;
				}
			}
		}

		char buf[100];
		sprintf_s(buf, "Cant read [0x%.4X] (BAD_ADDRESS)", address);
		throw buf;
		
	}
*/

	void print();

	u8 fetch_instruction(u16 address);

	const RamVec stack = { 0x7EF, -0xFF, READ | WRITE, READ | WRITE, READ | WRITE };
	std::vector<RamVec> allocated = {
		{ 0x0, 0x06F0, READ | WRITE | EXECUTE, READ | WRITE | EXECUTE, READ | WRITE | EXECUTE }, // ����
		{ 0x07F0, 0xF, READ | WRITE, READ, NO }, // 
		stack
	};
};
