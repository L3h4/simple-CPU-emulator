#pragma once
#include<iostream>


#define u8 uint8_t
#define u16 uint16_t

enum Registers_codes
{
	A = 0xA,
	B = 0xB,
	C = 0xC,
	D = 0xD,
	PC = 0xE,
	SP = 0xF
};



struct
{
	// ������� ��������
	void MOV(u8 *dest, u8 *source)
	{
		// ������ ������� �������� �� source � dest
		::memcpy(dest, source, sizeof(u8));
	}
	// ������� ��������
	void ADD(u8 *oprand1, u8 *operand2)
	{
		// ������� �����
		Regs.STATUS.FLAGS.C = false;
		Regs.STATUS.FLAGS.S = false;
		Regs.STATUS.FLAGS.Z = false;
		// ��������� �����
		if (short int(*oprand1) + short int(*operand2) > 255)
		{
			Regs.STATUS.FLAGS.C = true;
		}
		if (u8(*oprand1 + *operand2) == 0)
		{
			Regs.STATUS.FLAGS.Z = true;
		}
		// ������� ��������
		*oprand1 += *operand2;
	}
	// ������� ���������
	void SUB(u8 *oprand1, u8 *operand2)
	{
		// ������� �����
		Regs.STATUS.FLAGS.C = false;
		Regs.STATUS.FLAGS.Z = false;

		// ��������� �����
		if (short int(*oprand1) - *operand2 < 0)
		{
			Regs.STATUS.FLAGS.S = true;
		}
		if (*oprand1 - *operand2 == 0)
		{
			Regs.STATUS.FLAGS.Z = true;
		}
		// ������� ��������
		*oprand1 -= *operand2;
	}
	// ������� ��������� ���������
	void CMP(u8 *oprand1, u8 *operand2)
	{
		// ������� �����
		Regs.STATUS.FLAGS.C = false;
		Regs.STATUS.FLAGS.S = false;
		Regs.STATUS.FLAGS.Z = false;

		// ��������� �����
		if (short int(*oprand1) - *operand2 < 0)
		{
			Regs.STATUS.FLAGS.S = true;
		}
		if (u8(*oprand1 - *operand2) == 0)
		{
			Regs.STATUS.FLAGS.Z = true;
		}

	}

	void JMP(u8 addres)
	{
		Regs.PC = addres;
	}

	void JE(u8 addres)
	{
		//  ����������� �������
		if (Regs.STATUS.FLAGS.Z) {
			JMP(addres);
		}
	}

	void JNE(u8 addres)
	{
		if (!Regs.STATUS.FLAGS.Z) {
			JMP(addres);
		}
	}

	void JL(u8 addres)
	{
		if (Regs.STATUS.FLAGS.S) {
			JMP(addres);
		}
	}

	void JG(u8 addres)
	{
		if (!Regs.STATUS.FLAGS.S) {
			JMP(addres);
		}
	}

	void JLE(u8 addres)
	{
		if (Regs.STATUS.FLAGS.S || Regs.STATUS.FLAGS.Z) {
			JMP(addres);
		}
	}

	void JGE(u8 addres)
	{
		if (!Regs.STATUS.FLAGS.S || Regs.STATUS.FLAGS.Z) {
			JMP(addres);
		}
	}

} ALU;

struct
{
	std::string stdout_buffer;
	void SYSCALL()
	{

		if (Regs.AX.value == 1)
		{
			stdout_buffer += char(Regs.BX.value);
		}
		else if (Regs.AX.value == 2)
		{
			printf("%s", stdout_buffer.c_str());
			stdout_buffer = "";
		}
	}
} System;


