#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>



#define u8 uint8_t
#define u16 uint16_t

enum Rights
{
	KERNEL,
	ROOT,
	USER
};


enum MemoryRights
{
	NO = 0,
	READ = 1,
	WRITE = 2,
	EXECUTE = 4,

};

struct RamVec
{
	u16 addres;
	int size;

	int rights_KERNEL = READ | WRITE;
	int rights_ROOT = READ | WRITE;
	int rights_USER = READ;
	
	bool in(u16 addres);
};


class Memory // êëàñ ÎÇÓ
{
public:
	Memory();
	~Memory();


public:
	u8 memory[1024 * 2]; // 2êá îçó

	template<typename T>
	void write(u16 address, T value)
	{
		if (stack.in(address))
		{
			if (stack.rights_KERNEL & WRITE)
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
				sprintf_s(buf, "Cant write [0x%.4X] (stack) (UNWRITABLE_MEMORY)", address);
				throw (std::string)buf;
			}
		}
		else
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
						throw (std::string)buf;
					}
				}

			}
		}
		char buf[100];
		sprintf_s(buf, "Cant write [0x%.4X] (BAD_ADDRESS)", address);
		throw (std::string)buf;		
	}

	template<typename T>
	T  read(u16 address)
	{
		if (stack.in(address))
		{
			if (stack.rights_KERNEL & READ)
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
				sprintf_s(buf, "Cant read [0x%.4X] (stack) (UNREADABLE_MEMORY)", address);
				throw (std::string)buf;
			}
		}
		else
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
						throw (std::string)buf;
					}
				}
			
			}
		}

		char buf[100];
		sprintf_s(buf, "Cant read [0x%.4X] (BAD_ADDRESS)", address);
		throw (std::string)buf;
		
	}

	void print();

	u8 fetch_instruction(u16 address);

	RamVec stack = { 0x7EF, -0xFF, READ | WRITE, READ | WRITE, READ | WRITE };
	std::vector<RamVec> allocated;
};

