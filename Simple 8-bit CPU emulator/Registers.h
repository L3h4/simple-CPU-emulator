#pragma once
#include<stdio.h>
#include<iostream>
#include <string> 

#define u8 uint8_t
#define u16 uint16_t

/*
16/8 битные регистры

типа как
_______________________
|	 AX (16 бит)      |
|         | A (8 бит) |
*/
struct Register {
	std::string name;
	std::string name16;
	u8 permissions;
	union 
	{
		u8 lo;
		u16 value;
	};
};


struct Registers
{
private:
	enum
	{
		Ac = 0xA,
		Bc = 0xB,
		Cc = 0xC,
		Dc = 0xD,
		STATc = 0xAB,

		AXc = 0xAA,
		BXc = 0xBB,
		CXc = 0xCC,
		DXc = 0xDD,

		PCc = 0xEE,
		SPc = 0xFF,
	};

public:

	// Регистры общего назначения 
	Register AX{ "A", "AX" };
	Register BX{ "B", "BX" };
	Register CX{ "C", "CX" };
	Register DX{ "D", "DX" };

	Register PC{ "PC", "PC" };
	Register SP{ "SP", "SP" };

	// 8-битный статус регистр
	union
	{
		struct {
			bool Z : 1; // Флаг ноля
			bool C : 1; // Флаг переноса
			bool u : 5; // Не используется
			bool S : 1; // Флаг знака (0 : + | 1 : -)
		} FLAGS;

		u8 value;
	}STATUS;
public:
	void print() {
		// Вывод значений регистров в консоль
		printf("==========\n");
		printf("REGISTERS\n");
		printf("AX = 0x%.4X\n", AX.value);
		printf("BX = 0x%.4X\n", BX.value);
		printf("CX = 0x%.4X\n", CX.value);
		printf("DX = 0x%.4X\n", DX.value);
		printf("=========\n");
		printf("PC = 0x%.4X\n", PC.value);
		printf("SP = 0x%.4X\n", SP.value);
		printf("FLAGS\n");
		printf("S C Z\n");
		printf("%d %d %d\n", STATUS.FLAGS.S, STATUS.FLAGS.C, STATUS.FLAGS.Z);
		printf("==========\n");
	}
	
	Register *parse(u8 code) {
		switch (code)
		{
		case Ac:
			return &AX;
		case Bc:
			return &BX;
		case Cc:
			return &CX;
		case Dc:
			return &DX;
		case AXc:
			return &AX;
		case BXc:
			return &BX;
		case CXc:
			return &CX;
		case DXc:
			return &DX;
		case PCc:
			return &PC;
		case SPc:
			return &SP;
		default:
			//raise error
			throw "Unknown register " + std::to_string(code);
			break;
		}
	}
};