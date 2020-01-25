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
	Registers->Register* parse_register()
	{
		// парсинг регистра
		Regs.Register* res = nullptr;
		switch (*RAM.read(Regs.PC))
		{
		case A:
			res = &Regs.AX;
			break;
		case B:
			res = &Regs.BX;
			break;
		case C:
			res = &Regs.CX;
			break;
		case D:
			res = &Regs.DX;
			break;
		case PC:
			res = &Regs.PC;
			break;
		case SP:
			res = &Regs.SP;
			break;
		default:
			throw out_of_range("Can't parse register, " + to_string(*RAM.read(Regs.PC)));
			break;
		}
		return res;
	}
} bin_parser;


struct
{
	// функци€ переноса
	void MOV(u8 *dest, u8 *source)
	{
		// просто копирую значение из source в dest
		::memcpy(dest, source, sizeof(u8));
	}
	// функци€ сложени€
	void ADD(u8 *oprand1, u8 *operand2)
	{
		// обнул€ю флаги
		Regs.STATUS.FLAGS.C = false;
		Regs.STATUS.FLAGS.S = false;
		Regs.STATUS.FLAGS.Z = false;
		// ¬ыставл€ю флаги
		if (short int(*oprand1) + short int(*operand2) > 255)
		{
			Regs.STATUS.FLAGS.C = true;
		}
		if (u8(*oprand1 + *operand2) == 0)
		{
			Regs.STATUS.FLAGS.Z = true;
		}
		// провожу операцию
		*oprand1 += *operand2;
	}
	// функци€ вычетани€
	void SUB(u8 *oprand1, u8 *operand2)
	{
		// обнул€ю флаги
		Regs.STATUS.FLAGS.C = false;
		Regs.STATUS.FLAGS.Z = false;

		// ¬ыставл€ю флаги
		if (short int(*oprand1) - *operand2 < 0)
		{
			Regs.STATUS.FLAGS.S = true;
		}
		if (*oprand1 - *operand2 == 0)
		{
			Regs.STATUS.FLAGS.Z = true;
		}
		// провожу операцию
		*oprand1 -= *operand2;
	}
	// функци€ вычетани€ сравнени€
	void CMP(u8 *oprand1, u8 *operand2)
	{
		// обнул€ю флаги
		Regs.STATUS.FLAGS.C = false;
		Regs.STATUS.FLAGS.S = false;
		Regs.STATUS.FLAGS.Z = false;

		// ¬ыставл€ю флаги
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
		//  безусловный переход
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


// определени€ инструкций

// сокращени€ в мнемониках и коде
// d8 или V    - 8-битное число
// a8 или A    - 8-битный адрес 
// R           - 8-битный регистр
// [R]  или aR - 8-битный адрес в регистре


//   NOP
void NOP();

// MOV R, d8;     MOV R, R;    MOV R, a8;    MOV a8, R;   MOV a8, d8;    MOV R, [R];    MOV [R], R;   MOV [R], [R];   MOV [R], d8;   MOV [R], a8;   MOV a8, [R];   MOV a8, a8
void MOVRV(); void MOVRR(); void MOVRA(); void MOVAR(); void MOVAV(); void MOVRaR(); void MOVaRR(); void MOVaRaR(); void MOVaRV(); void MOVaRA(); void MOVAaR(); void MOVAA();

// ADD R, d8;     ADD R, R;    ADD R, a8;    ADD a8, R;   ADD a8, d8;    ADD R, [R];    ADD [R], R;   ADD [R], [R];   ADD [R], d8;  ADD  [R], a8;   ADD a8, [R];   ADD a8, a8 
void ADDRV(); void ADDRR(); void ADDRA(); void ADDAR(); void ADDAV(); void ADDRaR(); void ADDaRR(); void ADDaRaR(); void ADDaRV(); void ADDaRA(); void ADDAaR(); void ADDAA();

// SUB R, d8;     SUB R, R;    SUB R, a8;    SUB a8, R;   SUB a8, d8;    SUB R, [R];    SUB [R], R;   SUB [R], [R];   SUB [R], d8;  SUB  [R], a8;   SUB a8, [R];   SUB a8, a8 
void SUBRV(); void SUBRR(); void SUBRA(); void SUBAR(); void SUBAV(); void SUBRaR(); void SUBaRR(); void SUBaRaR(); void SUBaRV(); void SUBaRA(); void SUBAaR(); void SUBAA();

// CMP R, d8;     CMP R, R;    CMP R, a8;    CMP a8, R;   CMP a8, d8;    CMP R, [R];    CMP [R], R;   CMP [R], [R];   CMP [R], d8;  CMP  [R], a8;   CMP a8, [R];   CMP a8, a8 
void CMPRV(); void CMPRR(); void CMPRA(); void CMPAR(); void CMPAV(); void CMPRaR(); void CMPaRR(); void CMPaRaR(); void CMPaRV(); void CMPaRA(); void CMPAaR(); void CMPAA();

//    INC R;      INC a8;      INC [R]
void INCR(); void INCA(); void INCaR();

//    DEC R;      DEC a8;      DEC [R]
void DECR(); void DECA(); void DECaR();

//    JMP R;      JMP a8
void JMPR(); void JMPA();

//    JE R;      JE a8
void JER(); void JEA();

//    JNE R;      JNE a8
void JNER(); void JNEA();

//    JL R;      JL a8
void JLR(); void JLA();

//    JG R;      JG a8
void JGR(); void JGA();

//    JLE R;      JLE a8
void JLER(); void JLEA();

//    JGE R;      JGE a8
void JGER(); void JGEA();

//     HLT;        SYSCALL
void HLT(); void SYSCALL();