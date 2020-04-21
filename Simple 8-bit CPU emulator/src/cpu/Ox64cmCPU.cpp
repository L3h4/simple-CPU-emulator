﻿#include "Ox64cmCPU.h"



Ox64cmCPU::Ox64cmCPU(Bus * b, Status * s)
{
	// конструктор процессора
	this->bus = b;
	this->status = s;

	// Инициализация сэта инструкций
	using a = Ox64cmCPU;
	opcodes = {
		

		{"mov", BYTE, &a::MOV, REGISTER, NUMBER,          3}, {"mov", BYTE, &a::MOV, PTR_IN_REGISTER, NUMBER,          3}, {"mov", BYTE, &a::MOV, PTR_IN_NUMBER, NUMBER,          4}, /**/ {"add", BYTE, &a::ADD, REGISTER, NUMBER,          3}, {"add", BYTE, &a::ADD, PTR_IN_REGISTER, NUMBER,          3}, {"add", BYTE, &a::ADD, PTR_IN_NUMBER, NUMBER,          4}, /**/ {"sub", BYTE, &a::SUB, REGISTER, NUMBER,          3}, {"sub", BYTE, &a::SUB, PTR_IN_REGISTER, NUMBER,          3}, {"sub", BYTE, &a::SUB, PTR_IN_NUMBER, NUMBER,          4}, {"push", BYTE, &a::PUSH, NUMBER,          NO_ARG, 2},   {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"nop", NODATA, &a::NOP, NO_ARG, NO_ARG, 1},
		{"mov", BYTE, &a::MOV, REGISTER, REGISTER,        3}, {"mov", BYTE, &a::MOV, PTR_IN_REGISTER, REGISTER,        3}, {"mov", BYTE, &a::MOV, PTR_IN_NUMBER, REGISTER,        4}, /**/ {"add", BYTE, &a::ADD, REGISTER, REGISTER,        3}, {"add", BYTE, &a::ADD, PTR_IN_REGISTER, REGISTER,        3}, {"add", BYTE, &a::ADD, PTR_IN_NUMBER, REGISTER,        4}, /**/ {"sub", BYTE, &a::SUB, REGISTER, REGISTER,        3}, {"sub", BYTE, &a::SUB, PTR_IN_REGISTER, REGISTER,        3}, {"sub", BYTE, &a::SUB, PTR_IN_NUMBER, REGISTER,        4}, {"push", BYTE, &a::PUSH, REGISTER,        NO_ARG, 2},   {"pop", BYTE, &a::POP, REGISTER,        NO_ARG, 2}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
		{"mov", BYTE, &a::MOV, REGISTER, PTR_IN_NUMBER,   4}, {"mov", BYTE, &a::MOV, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"mov", BYTE, &a::MOV, PTR_IN_NUMBER, PTR_IN_NUMBER,   5}, /**/ {"add", BYTE, &a::ADD, REGISTER, PTR_IN_NUMBER,   4}, {"add", BYTE, &a::ADD, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"add", BYTE, &a::ADD, PTR_IN_NUMBER, PTR_IN_NUMBER,   5}, /**/ {"sub", BYTE, &a::SUB, REGISTER, PTR_IN_NUMBER,   4}, {"sub", BYTE, &a::SUB, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"sub", BYTE, &a::SUB, PTR_IN_NUMBER, PTR_IN_NUMBER,   5}, {"push", BYTE, &a::PUSH, PTR_IN_NUMBER,   NO_ARG, 3},   {"pop", BYTE, &a::POP, PTR_IN_NUMBER,   NO_ARG, 3}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
		{"mov", BYTE, &a::MOV, REGISTER, PTR_IN_REGISTER, 3}, {"mov", BYTE, &a::MOV, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"mov", BYTE, &a::MOV, PTR_IN_NUMBER, PTR_IN_REGISTER, 4}, /**/ {"add", BYTE, &a::ADD, REGISTER, PTR_IN_REGISTER, 3}, {"add", BYTE, &a::ADD, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"add", BYTE, &a::ADD, PTR_IN_NUMBER, PTR_IN_REGISTER, 4}, /**/ {"sub", BYTE, &a::SUB, REGISTER, PTR_IN_REGISTER, 3}, {"sub", BYTE, &a::SUB, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"add", BYTE, &a::SUB, PTR_IN_NUMBER, PTR_IN_REGISTER, 4}, {"push", BYTE, &a::PUSH, PTR_IN_REGISTER, NO_ARG, 2},   {"pop", BYTE, &a::POP, PTR_IN_REGISTER, NO_ARG, 2}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
																																																																																																																																											   									    
		{"mov", WORD, &a::MOV, REGISTER, NUMBER,          4}, {"mov", WORD, &a::MOV, PTR_IN_REGISTER, NUMBER,          4}, {"mov", WORD, &a::MOV, PTR_IN_NUMBER, NUMBER,          5}, /**/ {"add", WORD, &a::ADD, REGISTER, NUMBER,          4}, {"add", WORD, &a::ADD, PTR_IN_REGISTER, NUMBER,          4}, {"add", WORD, &a::ADD, PTR_IN_NUMBER, NUMBER,          5}, /**/ {"sub", WORD, &a::SUB, REGISTER, NUMBER,          4}, {"sub", WORD, &a::SUB, PTR_IN_REGISTER, NUMBER,          4}, {"sub", WORD, &a::SUB, PTR_IN_NUMBER, NUMBER,          5}, {"push", WORD, &a::PUSH, NUMBER,          NO_ARG, 3},   {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
		{"mov", WORD, &a::MOV, REGISTER, REGISTER,        3}, {"mov", WORD, &a::MOV, PTR_IN_REGISTER, REGISTER,        3}, {"mov", WORD, &a::MOV, PTR_IN_NUMBER, REGISTER,        4}, /**/ {"add", WORD, &a::ADD, REGISTER, REGISTER,        3}, {"add", WORD, &a::ADD, PTR_IN_REGISTER, REGISTER,        3}, {"add", WORD, &a::ADD, PTR_IN_NUMBER, REGISTER,        4}, /**/ {"sub", WORD, &a::SUB, REGISTER, REGISTER,        3}, {"sub", WORD, &a::SUB, PTR_IN_REGISTER, REGISTER,        3}, {"sub", WORD, &a::SUB, PTR_IN_NUMBER, REGISTER,        4}, {"push", WORD, &a::PUSH, REGISTER,        NO_ARG, 2},   {"pop", WORD, &a::POP, REGISTER,        NO_ARG, 2}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
		{"mov", WORD, &a::MOV, REGISTER, PTR_IN_NUMBER,   4}, {"mov", WORD, &a::MOV, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"mov", WORD, &a::MOV, PTR_IN_NUMBER, PTR_IN_NUMBER,   5}, /**/ {"add", WORD, &a::ADD, REGISTER, PTR_IN_NUMBER,   4}, {"add", WORD, &a::ADD, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"add", WORD, &a::ADD, PTR_IN_NUMBER, PTR_IN_NUMBER,   5}, /**/ {"sub", WORD, &a::SUB, REGISTER, PTR_IN_NUMBER,   4}, {"sub", WORD, &a::SUB, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"sub", WORD, &a::SUB, PTR_IN_NUMBER, PTR_IN_NUMBER,   5}, {"push", WORD, &a::PUSH, PTR_IN_NUMBER,   NO_ARG, 3},   {"pop", WORD, &a::POP, PTR_IN_NUMBER,   NO_ARG, 3}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
		{"mov", WORD, &a::MOV, REGISTER, PTR_IN_REGISTER, 3}, {"mov", WORD, &a::MOV, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"mov", WORD, &a::MOV, PTR_IN_NUMBER, PTR_IN_REGISTER, 4}, /**/ {"add", WORD, &a::ADD, REGISTER, PTR_IN_REGISTER, 3}, {"add", WORD, &a::ADD, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"add", WORD, &a::ADD, PTR_IN_NUMBER, PTR_IN_REGISTER, 4}, /**/ {"sub", WORD, &a::SUB, REGISTER, PTR_IN_REGISTER, 3}, {"sub", WORD, &a::SUB, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"sub", WORD, &a::SUB, PTR_IN_NUMBER, PTR_IN_REGISTER, 4}, {"push", WORD, &a::PUSH, PTR_IN_REGISTER, NO_ARG, 2},   {"pop", WORD, &a::POP, PTR_IN_REGISTER, NO_ARG, 2}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
																																																																																																																																																															          				            											        											        											         
		{"cmp", BYTE, &a::CMP, REGISTER, NUMBER,          3}, {"cmp", BYTE, &a::CMP, PTR_IN_REGISTER, NUMBER,          3}, {"cmp", BYTE, &a::CMP, PTR_IN_NUMBER, NUMBER,          4},{"nop", NODATA, &a::NOP, NO_ARG, NO_ARG, 1},                {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"call", NODATA, &a::CALL, NUMBER,          NO_ARG, 3}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},
		{"cmp", BYTE, &a::CMP, REGISTER, REGISTER,        3}, {"cmp", BYTE, &a::CMP, PTR_IN_REGISTER, REGISTER,        3}, {"cmp", BYTE, &a::CMP, PTR_IN_NUMBER, REGISTER,        4},{"nop", NODATA, &a::NOP, NO_ARG, NO_ARG, 1},                {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"call", NODATA, &a::CALL, REGISTER,        NO_ARG, 2}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"ret", NODATA, &a::RET, NO_ARG, NO_ARG, 1},
		{"cmp", BYTE, &a::CMP, REGISTER, PTR_IN_NUMBER,   4}, {"cmp", BYTE, &a::CMP, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"cmp", BYTE, &a::CMP, PTR_IN_NUMBER, PTR_IN_NUMBER,   5},{"nop", NODATA, &a::NOP, NO_ARG, NO_ARG, 1},                {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"call", NODATA, &a::CALL, PTR_IN_NUMBER,   NO_ARG, 3}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"hlt", NODATA, &a::HLT, NO_ARG, NO_ARG, 1},
		{"cmp", BYTE, &a::CMP, REGISTER, PTR_IN_REGISTER, 3}, {"cmp", BYTE, &a::CMP, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"cmp", BYTE, &a::CMP, PTR_IN_NUMBER, PTR_IN_REGISTER, 4},{"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"call", NODATA, &a::CALL, PTR_IN_REGISTER, NO_ARG, 2}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},        {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},

		{"cmp", WORD, &a::CMP, REGISTER, NUMBER,          4}, {"cmp", WORD, &a::CMP, PTR_IN_REGISTER, NUMBER,          4}, {"cmp", WORD, &a::CMP, PTR_IN_NUMBER, NUMBER,          5}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"jmp", NODATA, &a::JMP, NUMBER,          NO_ARG, 3},   {"je", NODATA, &a::JE, NUMBER,          NO_ARG, 3}, {"jne", NODATA, &a::JNE, NUMBER,          NO_ARG, 3}, {"jl", NODATA, &a::JL, NUMBER,          NO_ARG, 3}, {"jg", NODATA, &a::JG, NUMBER,          NO_ARG, 3}, {"jle", NODATA, &a::JLE, NUMBER,          NO_ARG, 3}, {"jge", NODATA, &a::JGE, NUMBER,          NO_ARG, 3},
		{"cmp", WORD, &a::CMP, REGISTER, REGISTER,        3}, {"cmp", WORD, &a::CMP, PTR_IN_REGISTER, REGISTER,        3}, {"cmp", WORD, &a::CMP, PTR_IN_NUMBER, REGISTER,        4}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"jmp", NODATA, &a::JMP, REGISTER,        NO_ARG, 2},   {"je", NODATA, &a::JE, REGISTER,        NO_ARG, 2}, {"jne", NODATA, &a::JNE, REGISTER,        NO_ARG, 2}, {"jl", NODATA, &a::JL, REGISTER,        NO_ARG, 2}, {"jg", NODATA, &a::JG, REGISTER,        NO_ARG, 2}, {"jle", NODATA, &a::JLE, REGISTER,        NO_ARG, 2}, {"jge", NODATA, &a::JGE, REGISTER,        NO_ARG, 2},
		{"cmp", WORD, &a::CMP, REGISTER, PTR_IN_NUMBER,   4}, {"cmp", WORD, &a::CMP, PTR_IN_REGISTER, PTR_IN_NUMBER,   4}, {"cmp", WORD, &a::CMP, PTR_IN_NUMBER, PTR_IN_NUMBER,   5}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"jmp", NODATA, &a::JMP, PTR_IN_NUMBER,   NO_ARG, 3},   {"je", NODATA, &a::JE, PTR_IN_NUMBER,   NO_ARG, 3}, {"jne", NODATA, &a::JNE, PTR_IN_NUMBER,   NO_ARG, 3}, {"jl", NODATA, &a::JL, PTR_IN_NUMBER,   NO_ARG, 3}, {"jg", NODATA, &a::JG, PTR_IN_NUMBER,   NO_ARG, 3}, {"jle", NODATA, &a::JLE, PTR_IN_NUMBER,   NO_ARG, 3}, {"jge", NODATA, &a::JGE, PTR_IN_NUMBER,   NO_ARG, 3},
		{"cmp", WORD, &a::CMP, REGISTER, PTR_IN_REGISTER, 3}, {"cmp", WORD, &a::CMP, PTR_IN_REGISTER, PTR_IN_REGISTER, 3}, {"cmp", WORD, &a::CMP, PTR_IN_NUMBER, PTR_IN_REGISTER, 4}, {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                    {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},          {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},                 {"err", NODATA, &a::ERR, NO_ARG, NO_ARG, 1},               {"jmp", NODATA, &a::JMP, PTR_IN_REGISTER, NO_ARG, 2},   {"je", NODATA, &a::JE, PTR_IN_REGISTER, NO_ARG, 2}, {"jne", NODATA, &a::JNE, PTR_IN_REGISTER, NO_ARG, 2}, {"jl", NODATA, &a::JL, PTR_IN_REGISTER, NO_ARG, 2}, {"jg", NODATA, &a::JG, PTR_IN_REGISTER, NO_ARG, 2}, {"jle", NODATA, &a::JLE, PTR_IN_REGISTER, NO_ARG, 2}, {"jge", NODATA, &a::JGE, PTR_IN_REGISTER, NO_ARG, 2},

	};
	/*
		потом в коде я смогу легко получать нужные обработчики команд и аргументов типа 
		opcodes[код операции] и из этого я получаю обьект ИНСТРКЦИЯ, которою я смогу обрабатывать 
		Обьявление структуры ИНСТРУКЦИЯ в файле Ox64cmCPU.h
	*/
	this->reset();
}

void Ox64cmCPU::step()
{
	try
	{
		u8 opcode = bus->RAM.fetch_instruction(regs.PC.value);
		Instructin inst = opcodes[opcode];
		(this->*opcodes[opcode].operate)(inst);
	}
	catch (std::string e)
	{
		printf("ERORR: \"%s\"\n", e.c_str());
	}
	
}

void Ox64cmCPU::reset()
{
	this->regs.AX.value = 0;
	this->regs.BX.value = 0;
	this->regs.CX.value = 0;
	this->regs.DX.value = 0;

	this->regs.PC.value = 0;
	this->regs.SP.value = 0x07EF;

	this->regs.STATUS.value = 0;
}

void Ox64cmCPU::print_debug()
{
}

void Ox64cmCPU::print_disassembly(u16 start, u16 size)
{
	// функция для  дизассемблинга 
	// по сути делает то же самое что и ф-ция step() но просто не запускает обработчик операции, и после своей работы возвращает все назад
	u16 PC_backup = this->regs.PC.value;
	this->regs.PC.value = start;
	for (int i = 0; i < size; i++)
	{
		
	}
	this->regs.PC.value = PC_backup;
}


//#include"instructions/MOV.hpp"
void Ox64cmCPU::MOV(Instructin i)
{
	if (i.data_type == BYTE)
	{
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			u8 operand2 = parse_2nd_arg_value8(i);

			regs.write<u8>(dest, operand2);
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
			u8 operand2 = parse_2nd_arg_value8(i);

			bus->RAM.write<u8>(dest, operand2);
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
			u8 operand2 = parse_2nd_arg_value8(i);

			bus->RAM.write<u8>(dest, operand2);
		}
	}
	else if (i.data_type == WORD)
	{
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			u16 operand2 = parse_2nd_arg_value16(i);

			regs.write<u16>(dest, operand2);
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
			u16 operand2 = parse_2nd_arg_value16(i);

			bus->RAM.write<u16>(dest, operand2);
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
			u16 operand2 = parse_2nd_arg_value16(i);

			bus->RAM.write<u16>(dest, operand2);
		}
	}
	regs.PC.value++;
}



void Ox64cmCPU::ADD(Instructin i)
{
	
	this->regs.STATUS.C = false;
	this->regs.STATUS.Z = false;
	this->regs.STATUS.S = false;
	if (i.data_type == BYTE)
	{
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			u8 operand1 = regs.read<u8>(dest);
			u8 operand2 = parse_2nd_arg_value8(i);

			regs.write<u8>(dest, add(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
			u8 operand1 = bus->RAM.read<u8>(dest);
			u8 operand2 = parse_2nd_arg_value8(i);

			bus->RAM.write<u8>(dest, add(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
			u8 operand1 = bus->RAM.read<u8>(dest);
			u8 operand2 = parse_2nd_arg_value8(i);

			bus->RAM.write<u8>(dest, add(operand1, operand2));
		}
	}
	else if (i.data_type == WORD)
	{
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			u16 operand1 = regs.read<u16>(dest);
			u16 operand2 = parse_2nd_arg_value16(i);

			regs.write<u16>(dest, add(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
			u16 operand1 = bus->RAM.read<u16>(dest);
			u16 operand2 = parse_2nd_arg_value16(i);

			bus->RAM.write<u16>(dest, add(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
			u16 operand1 = bus->RAM.read<u16>(dest);
			u16 operand2 = parse_2nd_arg_value16(i);

			bus->RAM.write<u16>(dest, add(operand1, operand2));
		}
	}
	regs.PC.value++;
}


void Ox64cmCPU::SUB(Instructin i)
{
	this->regs.STATUS.C = false;
	this->regs.STATUS.Z = false;
	this->regs.STATUS.S = false;
	if (i.data_type == BYTE)
	{
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			u8 operand1 = regs.read<u8>(dest);
			u8 operand2 = parse_2nd_arg_value8(i);

			regs.write<u8>(dest, sub(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
			u8 operand1 = bus->RAM.read<u8>(dest);
			u8 operand2 = parse_2nd_arg_value8(i);

			bus->RAM.write<u8>(dest, sub(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
			u8 operand1 = bus->RAM.read<u8>(dest);
			u8 operand2 = parse_2nd_arg_value8(i);

			bus->RAM.write<u8>(dest, sub(operand1, operand2));
		}
	}
	else if (i.data_type == WORD)
	{
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			u16 operand1 = regs.read<u16>(dest);
			u16 operand2 = parse_2nd_arg_value16(i);

			regs.write<u16>(dest, sub(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
			u16 operand1 = bus->RAM.read<u16>(dest);
			u16 operand2 = parse_2nd_arg_value16(i);

			bus->RAM.write<u16>(dest, sub(operand1, operand2));
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
			u16 operand1 = bus->RAM.read<u16>(dest);
			u16 operand2 = parse_2nd_arg_value16(i);

			bus->RAM.write<u16>(dest, sub(operand1, operand2));
		}
	}
	regs.PC.value++;
}



void Ox64cmCPU::CMP(Instructin i)
{
	this->regs.STATUS.C = false;
	this->regs.STATUS.Z = false;
	this->regs.STATUS.S = false;
	if (i.data_type == BYTE)
	{
		u8 operand1 = parse_1st_arg_value8(i);
		u8 operand2 = parse_2nd_arg_value8(i);

		sub(operand1, operand2);
	}
	else if (i.data_type == WORD)
	{
		u16 operand1 = parse_1st_arg_value8(i);
		u16 operand2 = parse_2nd_arg_value16(i);

		sub(operand1, operand2);
	}
	regs.PC.value++;
}

void Ox64cmCPU::JMP(Instructin i)
{
	u16 address = parse_1st_arg_value16(i);
	regs.PC.value = address;
}

void Ox64cmCPU::JE(Instructin i)
{
	u16 address = parse_1st_arg_value16(i);

	if (regs.STATUS.Z)
		regs.PC.value = address;
	else
		regs.PC.value++;
}

void Ox64cmCPU::JNE(Instructin i)
{
	u16 address = parse_1st_arg_value16(i);

	if (!regs.STATUS.Z)
		regs.PC.value = address;
	else
		regs.PC.value++;
}

void Ox64cmCPU::JL(Instructin i)
{
	u16 address = parse_1st_arg_value16(i);

	if (regs.STATUS.S)
		regs.PC.value = address;
	else
		regs.PC.value++;
}

void Ox64cmCPU::JG(Instructin i)
{
	u16 address = parse_1st_arg_value16(i);

	if (!regs.STATUS.S)
		regs.PC.value = address;
	else
		regs.PC.value++;
}

void Ox64cmCPU::JLE(Instructin i)
{
	u16 address = parse_1st_arg_value16(i);

	if (regs.STATUS.Z || regs.STATUS.S)
		regs.PC.value = address;
	else
		regs.PC.value++;
}

void Ox64cmCPU::JGE(Instructin i)
{
	u16 address = parse_1st_arg_value16(i);

	if (regs.STATUS.Z || !regs.STATUS.S)
		regs.PC.value = address;
	else
		regs.PC.value++;
}

void Ox64cmCPU::PUSH(Instructin i)
{
	if (regs.SP.value < 0x07EF - 0xFF)
	{
		status->execute_til_hlt = false;
		throw (std::string)"stack overflow";
	}

	if (i.data_type == BYTE)
	{
		u8 value = parse_1st_arg_value8(i);
		bus->RAM.write<u8>(regs.SP.value, value);
		regs.SP.value--;
	}
	else if (i.data_type == WORD)
	{
		u16 value = parse_1st_arg_value16(i);
		regs.SP.value--;
		bus->RAM.write<u16>(regs.SP.value, value);
		regs.SP.value--;
	}
	regs.PC.value++;
}

void Ox64cmCPU::POP(Instructin i)
{
	if (i.data_type == BYTE)
	{
		if (regs.SP.value > 0x07EF)
		{
			status->execute_til_hlt = false;
			throw (std::string)"stack empty";
		}

		u8 value = bus->RAM.read<u8>(++regs.SP.value);
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			
			regs.write<u8>(dest, value);
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
			
			bus->RAM.write<u8>(dest, value);
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
			
			bus->RAM.write<u8>(dest, value);
		}
	}
	else if (i.data_type == WORD)
	{
		if (regs.SP.value > 0x07EF - 1)
		{
			status->execute_til_hlt = false;
			throw (std::string)"stack empty";
		}

		regs.SP.value++;
		u16 value = bus->RAM.read<u16>(regs.SP.value++);
		if (i.arg1_type == REGISTER)
		{
			u8 dest = bus->RAM.read<u8>(++regs.PC.value);
			regs.write<u16>(dest, value);
		}
		else if (i.arg1_type == PTR_IN_REGISTER)
		{
			u16 dest = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
	
			bus->RAM.write<u16>(dest, value);
		}
		else if (i.arg1_type == PTR_IN_NUMBER)
		{
			regs.PC.value++;
			u16 dest = bus->RAM.read<u16>(regs.PC.value++);
	
			bus->RAM.write<u16>(dest, value);
		}
	}
	regs.PC.value++;
}

void Ox64cmCPU::CALL(Instructin i)
{
	if (regs.SP.value < 0x07EF - 0xFF)
	{
		status->execute_til_hlt = false;
		throw (std::string)"stack overflow";
	}

	u16 value = parse_1st_arg_value16(i);
	regs.SP.value--;
	regs.PC.value++;
	bus->RAM.write<u16>(regs.SP.value, regs.PC.value);
	regs.SP.value--;

	regs.PC.value = value;
}

void Ox64cmCPU::RET(Instructin i)
{
	if (regs.SP.value > 0x07EF - 1)
	{
		status->execute_til_hlt = false;
		throw (std::string)"stack empty";
	}

	regs.SP.value++;
	u16 value = bus->RAM.read<u16>(regs.SP.value);
	regs.SP.value++;

	regs.PC.value = value;
}

void Ox64cmCPU::NOP(Instructin i)
{
	regs.PC.value++;
}

void Ox64cmCPU::HLT(Instructin i)
{
	status->execute_til_hlt = false;
	printf("Program finished\n");
}

void Ox64cmCPU::ERR(Instructin i)
{
	throw (std::string)"Bad instruction";
}


u8 Ox64cmCPU::parse_1st_arg_value8(Instructin i)
{
	u8 operand = 0;


	if (i.arg1_type == NUMBER)
	{
		operand = bus->RAM.read<u8>(++regs.PC.value);
	}
	else if (i.arg1_type == REGISTER)
	{
		operand = regs.read<u8>(bus->RAM.read<u8>(++regs.PC.value));
	}
	else if (i.arg1_type == PTR_IN_NUMBER)
	{
		regs.PC.value++;
		operand = bus->RAM.read<u8>(bus->RAM.read<u16>(regs.PC.value++));
	}
	else if (i.arg1_type == PTR_IN_REGISTER)
	{
		operand = bus->RAM.read<u8>(regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value)));
	}

	return operand;
}

u16 Ox64cmCPU::parse_1st_arg_value16(Instructin i)
{
	u16 operand = 0;
	if (i.arg1_type == NUMBER)
	{
		regs.PC.value++;
		operand = bus->RAM.read<u16>(regs.PC.value++);
	}
	else if (i.arg1_type == REGISTER)
	{
		operand = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
	}
	else if (i.arg1_type == PTR_IN_NUMBER)
	{
		regs.PC.value++;
		operand = bus->RAM.read<u16>(bus->RAM.read<u16>(regs.PC.value++));
	}
	else if (i.arg1_type == PTR_IN_REGISTER)
	{
		operand = bus->RAM.read<u16>(regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value)));
	}
	return operand;
}



u16 Ox64cmCPU::parse_2nd_arg_value16(Instructin i)
{
	u16 operand = 0;
	if (i.arg2_type == NUMBER)
	{
		regs.PC.value++;
		operand = bus->RAM.read<u16>(regs.PC.value++);
	}
	else if (i.arg2_type == REGISTER)
	{
		operand = regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value));
	}
	else if (i.arg2_type == PTR_IN_NUMBER)
	{
		regs.PC.value++;
		operand = bus->RAM.read<u16>(bus->RAM.read<u16>(regs.PC.value++));
	}
	else if (i.arg2_type == PTR_IN_REGISTER)
	{
		operand = bus->RAM.read<u16>(regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value)));
	}
	return operand;
}


u8 Ox64cmCPU::parse_2nd_arg_value8(Instructin i)
{
	u8 operand = 0;


	if (i.arg2_type == NUMBER)
	{
		operand = bus->RAM.read<u8>(++regs.PC.value);
	}
	else if (i.arg2_type == REGISTER)
	{
		operand = regs.read<u8>(bus->RAM.read<u8>(++regs.PC.value));
	}
	else if (i.arg2_type == PTR_IN_NUMBER)
	{
		regs.PC.value++;
		operand = bus->RAM.read<u8>(bus->RAM.read<u16>(regs.PC.value++));
	}
	else if (i.arg2_type == PTR_IN_REGISTER)
	{
		operand = bus->RAM.read<u8>(regs.read<u16>(bus->RAM.read<u8>(++regs.PC.value)));
	}

	return operand;
}


