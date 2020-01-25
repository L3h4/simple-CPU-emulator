#pragma once
#include<stdio.h>
#include<iostream>

#define u8 uint8_t
#define u16 uint16_t

/* 
16/8 ������ ��������

���� ���
_______________________
|	 AX (16 ���)      |
|         | A (8 ���) |
*/
struct Registers
{
public:
	union Register
	{
		u8 lo;
		u16 value;
	};

	// �������� ������ ���������� 
	Register AX;
	Register BX;
	Register CX;
	Register DX;

	u16 PC;
	u16 SP;

	// 8-������ ������ �������
	union
	{
		struct {
			bool Z : 1; // ���� ����
			bool C : 1; // ���� ��������
			bool u : 5; // �� ������������
			bool S : 1; // ���� ����� (0 : + | 1 : -)
		} FLAGS;

		u8 value;
	}STATUS;
	void print() {
		// ����� �������� ��������� � �������
		printf("==========\n");
		printf("REGISTERS\n");
		printf("AX = 0x%.4X\n", Regs.AX.value);
		printf("BX = 0x%.4X\n", Regs.BX.value);
		printf("CX = 0x%.4X\n", Regs.CX.value);
		printf("DX = 0x%.4X\n", Regs.DX.value);
		printf("=========\n");
		printf("PC = 0x%.4X\n", Regs.PC);
		printf("SP = 0x%.4X\n", Regs.SP);
		printf("FLAGS\n");
		printf("S C Z\n");
		printf("%d %d %d\n", STATUS.FLAGS.S, STATUS.FLAGS.C, STATUS.FLAGS.Z);
		printf("==========\n");
	}
}Regs;


struct
{
public:
	u8 memory[1024 * 2]; // 2�� ���

	void write(u16 addres, u8 value) {
		if(addres < 2048)
			memory[addres] = value;
	}

	u8* read(u16 addres) {
		if (addres < 2048)
			return &memory[addres];
	}

	void print() 
	{
		printf("MEMORY");
		for (short int i = 0; i < sizeof(memory); i++) {
			if (i % 16 == 0) {
				printf("\n");
				printf("  0x%.2X  |  ", i);
			}
			printf(" %.2X ", memory[i]);
		}
		printf("\n==========================================================================\n\n");
	}
} RAM;