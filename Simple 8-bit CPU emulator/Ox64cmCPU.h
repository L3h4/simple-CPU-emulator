#pragma once
#include<iostream>
#include<vector>
#include"Registers.h"
#include"Bus.h"
#include"Status.h"


#define DEBUG


#define u8 uint8_t
#define u16 uint16_t

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



	struct Instructin
	{
		std::string name;
		void(Ox64cmCPU::*execute)(void) = nullptr;
		std::string(Ox64cmCPU::*get_arg1)(void) = nullptr;
		std::string(Ox64cmCPU::*get_arg2)(void) = nullptr;
	};

	// функции / операции
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



	enum argTypes
	{
		IMMDATA,
		IMMDATA16,

		REGISTER,
		REGISTER16,

		ADDRESS,
		ADDRESS16,

		REGISTERPTR,
		REGISTERPTR16,
	};
	struct OpArg
	{
		u8 type;
		Register *reg;
		u16 address;
		u8 value;
		u16 value16;
		void set_type(u8 t) 
		{
			type = t;
		}
	};
	bool arg_id = false;
	OpArg arg1;
	OpArg arg2;
	// определения инструкций

	// сокращения в мнемониках и коде
	// d8 или V        - 8-битное число
	// a8 или A        - 8-битный адрес 
	// R               - 8-битный регистр
	// [R]  или aR     - 8-битный адрес в регистре
	// R16             - 16-битный регистр
	// [R16]  или aR16 - 16-битный адрес в регистре


	// функции парсинга аргументов
	//void RV(); void RR(); void RA(); void AR(); void AV(); void RaR(); void aRR(); void aRaR(); void aRV(); void aRA(); void AaR(); void AA();
	//void R16V(); void R16R16(); void R16A(); void AR16(); void R16aR(); void aR16R(); void aR16aR(); void aR16V(); void aR16A(); void AaR16();
	//void R16R(); void RR16(); void RaR16(); void aRR16(); void aRaR16(); void aR16aR16(); void aR16R16();
	std::string V(); std::string V16(); std::string R(); std::string aR(); std::string R16(); std::string aR16(); std::string A(); std::string A16();
	std::string NA();


	Bus* bus;
	Status* status;
	Registers regs;
	std::vector<Instructin> opcodes;
};

