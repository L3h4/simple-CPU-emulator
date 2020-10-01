#pragma once
#include<iostream>
#include<vector>

#include"Bus.h"
#include"Status.h"
#include"RegisterFile.h"
#include"Memory.h"


#define u8 uint8_t
#define u16 uint16_t


class Bus;

struct DisassembledInstruction
{
	u16 address;
	std::string text;

	DisassembledInstruction(u16 address, std::string text)
		: address(address), text(text)
	{ }
};

class Ox64cmCPU
{
public:
	Ox64cmCPU();
	Ox64cmCPU(Bus *b, Status *s);

public:
	void step();
	void reset();
	void print_debug();
	void print_disassembly(u16 start, u16 size);

	std::vector<DisassembledInstruction> get_disassembly(u16 start, u16 size);



	RegisterFile & get_registers();
	


private:

	RegisterFile regs;

	enum ArgType // Перречисление всех типов аргументов (8бит. значение, 16бит. значение, регистр ...)
	{
		NUMBER,
		REGISTER,
		PTR_IN_REGISTER,
		PTR_IN_NUMBER,
		NO_ARG
	};
	enum DataType
	{
		NODATA,
		BYTE,
		WORD
	};


	// Обьявление структуры ИНСТРУКЦИЯ
	struct Instruction
	{
		std::string name; // текстовое представление, нужно для вывода  дизассембли
		DataType data_type;
		void (Ox64cmCPU::*operate)(Instruction i) = nullptr;
		ArgType arg1_type;
		ArgType arg2_type;
		int size;
	};

	struct Syscall_instruction
	{
		std::string name;
		void (Ox64cmCPU::*operate)(void) = nullptr;
	};

	// функции / операции
	void MOV(Instruction i);
	void ADD(Instruction i);
	void SUB(Instruction i);
	void CMP(Instruction i);
	void JMP(Instruction i);
	void JE(Instruction i);
	void JNE(Instruction i);
	void JL(Instruction i);
	void JG(Instruction i);
	void JLE(Instruction i);
	void JGE(Instruction i);

	void PUSH(Instruction i);
	void POP(Instruction i);

	void CALL(Instruction i);
	void RET(Instruction i);

	void NOP(Instruction i);
	void HLT(Instruction i);

	void SYSCALL(Instruction i);

	void ERR(Instruction i);

	std::string cout_buffer;

	void exit_syscall();
	void cout_buf_push_syscall();
	void cout_buf_clear_syscall();
	void display_clear_syscall();
	void cout_buf_print_syscall();


	Bus* bus;
	Status* status;
	std::vector<Instruction> opcodes;
	std::vector<Syscall_instruction> syscalls;

private:
	template<typename T>
	T add(T dest, T number)
	{
		if (typeid(T) == typeid(u16))
		{
			if ((int)dest + number > 0xFFFF)
				regs.STATUS.C = true;

			if ((u16)(dest + number) == 0)
				regs.STATUS.Z = true;
		}
		else
		{
			if ((int)dest + number > 0xFF)
				regs.STATUS.C = true;
			if ((u8)(dest + number) == 0)
				regs.STATUS.Z = true;
		}
		return (T)dest + number;
	}
	template<typename T>
	T sub(T dest, T number)
	{

		if ((int)dest - number < 0x0)
			regs.STATUS.S = true;
		if ((T)(dest - number) == 0)
			regs.STATUS.Z = true;

		return (T)dest - number;
	}

	std::string parse_arg(u16& PC, ArgType arg_type, DataType data_type);


	u8 parse_2nd_arg_value8(Instruction i);
	u16 parse_2nd_arg_value16(Instruction i);

	u8 parse_1st_arg_value8(Instruction i);
	u16 parse_1st_arg_value16(Instruction i);
	
	
	// определения инструкций

	// сокращения в мнемониках и коде
	// d8 или V        - 8-битное число
	// d16 или V16     - 16-битное число
	// a16 или A       - 1 байт по 16-битному адресу
	// a16 или A16     - 2 байта по 16-битному адресу
	// R               - 8-битный регистр
	// R16             - 16-битный регистр
	// [R]  или aR     - 1 байт по адресу в 16-битном регистре
	// [R16]  или aR16 - 2 байта по адресу в 16-битном регистре
	
};

