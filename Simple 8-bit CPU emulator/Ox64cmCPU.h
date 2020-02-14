#pragma once
#include<iostream>
#include<vector>

#include"Bus.h"
#include"Status.hpp"


#define u8 uint8_t
#define u16 uint16_t

// ���������������� ��������� ������, ����� ������ ����� �����������
#define DEBUG

class Bus;


class Ox64cmCPU
{
public:
	Ox64cmCPU() {};
	Ox64cmCPU(Bus *b, Status *s);

public:
	void step();
	void reset();
	void print_debug();
	void print_disassembly(u16 start, u16 size);

private:
	/*
	16/8 ������ ��������

	���� ���
	_______________________
	|	 AX (16 ���)      |
	|         | A (8 ���) |
	*/
	struct Register {
		std::string name; // ��������� ��� �������� ��� �����������
		std::string name16; // ��������� ��� 16-������� �������� ��� �����������
		union
		{
			u8 lo; // ������� 8 ���
			u16 value; // ��� 16 ���
		};
	};

public:
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
	void print_regs(); // ����� �������� ��������� � �������

private:
	Register *parse_reg(u8 code);


private:
	// ���������� ��������� ����������
	struct Instructin
	{
		std::string name; // ��������� �������������, ����� ��� ������ �����������
		void(Ox64cmCPU::*execute)(void) = nullptr; // ��������� �� ���������� ��������
		std::string(Ox64cmCPU::*get_arg1)(void) = nullptr; // ��������� �� "������" 1 ���������, ���������� ������ � ��� ��� �� ��� ��������(����� ��� ������ �����������)
		std::string(Ox64cmCPU::*get_arg2)(void) = nullptr; // ��������� �� "������" 2 ���������, ���������� ������ � ��� ��� �� ��� ��������(����� ��� ������ �����������) 
	};

	// ������� / ��������
	void MOV();
	void ADD();
	void SUB();
	void INC();
	void DEC();
	void CMP();
	void JMP();
	void JE();
	void JNE();
	void JL();
	void JG();
	void JLE();
	void JGE();
	void NOP();


private:
	enum argTypes // ������������� ���� ����� ���������� (8���. ��������, 16���. ��������, ������� ...)
	{
		IMMDATA,
		IMMDATA16,

		REGISTER,
		REGISTER16,

		// ����� ��� ������ 16 ������, ������ ��� ���������� �������� ��������/��������� �����
		ADDRESS, // �����/������ 1 ����
		ADDRESS16, // �����/������ 2 �����
	};
	struct OpArg
	{
		argTypes type;
		Register *reg;
		u16 address;
		u8 value;
		u16 value16;
		void set_type(argTypes t)
		{
			type = t;
		}
	};
	bool arg_id = false; // ���� ����������. ���� false �� ����� 1 �������� ����� 2
	OpArg arg1; // �������� 1
	OpArg arg2; // �������� 2
	// ����������� ����������

	// ���������� � ���������� � ����
	// d8 ��� V        - 8-������ �����
	// d16 ��� V16     - 16-������ �����
	// a16 ��� A       - 1 ���� �� 16-������� ������
	// a16 ��� A16     - 2 ����� �� 16-������� ������
	// R               - 8-������ �������
	// R16             - 16-������ �������
	// [R]  ��� aR     - 1 ���� �� ������ � 16-������ ��������
	// [R16]  ��� aR16 - 2 ����� �� ������ � 16-������ ��������
	

	// ������� �������� ����������. ���������� ������ � ��� ��� �� ��� ��������(����� ��� ������ �����������) 
	std::string V(); std::string V16(); std::string R(); std::string aR(); std::string R16(); std::string aR16(); std::string A(); std::string A16();
	std::string NA();

public:
	Bus* bus;
	Status* status;
	std::vector<Instructin> opcodes;
};

