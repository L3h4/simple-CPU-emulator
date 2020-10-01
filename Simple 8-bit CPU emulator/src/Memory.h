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


class Memory : public BusDevice // клас ОЗУ
{
	u8 *memory = nullptr; // 2кб озу
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

	void print();

	u8 fetch_instruction(u16 address);

	const RamVec stack = { 0x7EF, -0xFF, READ | WRITE, READ | WRITE, READ | WRITE };
	std::vector<RamVec> allocated = {
		{ 0x0, 0x06F0, READ | WRITE | EXECUTE, READ | WRITE | EXECUTE, READ | WRITE | EXECUTE }, // куча
		{ 0x07F0, 0xF, READ | WRITE, READ, NO }, // 
		stack
	};
};
