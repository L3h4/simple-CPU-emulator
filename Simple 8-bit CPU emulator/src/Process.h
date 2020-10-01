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
	NO,
	READ,
	WRITE,
	EXECUTE,
};

struct RamVec
{

	MemoryRights rights;
	
	u16 addres;
	u16 size;

};


class Process
{
public:
	Process();
	~Process();

public:

	

	void step();



protected:
	void save_registers();
	void restore_registers();



public:
	void SIG_START();

	void SIG_FREEZE();

	void SIG_STOP();

	void SIG_DEALLOC();



protected:
	RamVec exe_posititon;

	RamVec stack;

	RamVec heap;

	u8 read(u16 address);
	void write(u16 address, u8 data);


protected:

	u8 pid;

	u8 priority;

	Rights permissions;

};

