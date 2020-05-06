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
	16/8 ������ ��������

	���� ���
	_______________________
	|	 AX (16 ���)      |
	|         | A (8 ���) |
	*/
	struct Register {
		std::string name; // ��������� ��� �������� ���  �����������
		std::string name16; // ��������� ��� 16-������� �������� ���  �����������
		union
		{
			u8 lo; // ������� 8 ���
			u16 value; // ��� 16 ���
		};
	};


	// �������� ������ ���������� 
	Register AX{ "A", "AX" };
	Register BX{ "B", "BX" };
	Register CX{ "C", "CX" };
	Register DX{ "D", "DX" };

	Register PC{ "PC", "PC" }; // ������� ���������
	Register SP{ "SP", "SP" }; // ��������� �����

	// 8-������ ������ �������
	union
	{
		struct {
			bool Z : 1; // ���� ����
			bool C : 1; // ���� ��������
			bool u : 5; // �� ������������
			bool S : 1; // ���� ����� (0 : + | 1 : -)
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