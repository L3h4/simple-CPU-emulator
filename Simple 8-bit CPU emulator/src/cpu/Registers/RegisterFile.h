#pragma once
#include<iostream>
#include<stdio.h>

#define u8 uint8_t
#define u16 uint16_t



class RegisterFile
{
public:
	RegisterFile();
	~RegisterFile();


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
	/*
	16/8 битные регистры

	типа как
	_______________________
	|	 AX (16 бит)      |
	|         | A (8 бит) |
	*/
	struct Register {
		std::string name; // текстовое имя регистра для  дизассембли
		std::string name16; // текстовое имя 16-битного регистра для  дизассембли
		union
		{
			u8 lo; // младшие 8 бит
			u16 value; // все 16 бит
		};
	};


	// Регистры общего назначения 
	Register AX{ "A", "AX" };
	Register BX{ "B", "BX" };
	Register CX{ "C", "CX" };
	Register DX{ "D", "DX" };

	Register PC{ "PC", "PC" }; // счетчик программы
	Register SP{ "SP", "SP" }; // указатель стэка

	// 8-битный статус регистр
	union
	{
		struct {
			bool Z : 1; // Флаг ноля
			bool C : 1; // Флаг переноса
			bool u : 5; // Не используется
			bool S : 1; // Флаг знака (0 : + | 1 : -)
		};
		u8 value;
	}STATUS;


public:


	std::string get_string(u8 code);


	std::string get_string_name(u8 code);

	template<typename T>
	void write(u8 code, T value)
	{
		switch (code)
		{
		case Ac:
			AX.lo = value;
			break;
		case Bc:
			BX.lo = value;
			break;
		case Cc:
			CX.lo = value;
			break;
		case Dc:
			DX.lo = value;
			break;
		case STATc:
			STATUS.value = value;
			break;

		case AXc:
			AX.value = value;
			break;
		case BXc:
			BX.value = value;
			break;
		case CXc:
			CX.value = value;
			break;
		case DXc:
			DX.value = value;
			break;

		case PCc:
			PC.value = value;
			break;
		case SPc:
			SP.value = value;
			break;

		default:
			char buf[70];
			sprintf_s(buf, "Cant understand write 0x%.2X (NOTFOUND)", code);
			throw (std::string)buf;
			break;
		}
	}

	template<typename T>
	T read(u8 code)
	{
		switch (code)
		{
		case Ac:
			return AX.lo;
			break;
		case Bc:
			return BX.lo;
			break;
		case Cc:
			return CX.lo;
			break;
		case Dc:
			return DX.lo;
			break;
		case STATc:
			return STATUS.value;
			break;

		case AXc:
			return AX.value;
			break;
		case BXc:
			return BX.value;
			break;
		case CXc:
			return CX.value;
			break;
		case DXc:
			return DX.value;
			break;

		case PCc:
			return PC.value;
			break;
		case SPc:
			return SP.value;
			break;

		default:
			char buf[70];
			sprintf_s(buf, "Cant read register 0x%.2X (NOTFOUND)", code);
			throw (std::string)buf;
			break;
		}
	}


private:
	Register* parse_register(u8 code);
};