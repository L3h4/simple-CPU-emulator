#pragma once
#include<iostream>
#include<vector>

// Типы инструкций
enum type {
	CPU_INSTRUCTION,
	META_DATA,
	POINT_DEFINITION,
	NONE
};
enum arg_type {
	REGISTER,
	//REGISTER16,
	NUMBER,

	PTR_IN_REGISTER,
	//PTR_IN_REGISTER16,
	PTR_IN_NUMBER,
	NOARG
};

// Структурa Операция, нужна для синкасического и семантического анализа
struct Lexeme
{
	std::string full_command; // Полная строка с командой и аргументами
	std::string cmd; // Только команда
	std::string size_identifier; // размер с которым работаем word или byte
	std::string arg0; // Аргумент 1
	std::string arg1; // Аргумент 2
	arg_type arg0_type = NOARG;
	arg_type arg1_type = NOARG;
	std::string named_ptr; // Сюда запишеться название функции например start:
	type type; // Флажок который помечает реальная ли это инструкция или чтото другое
	int line; // Номер строки на которой находится инструкция (нужно для вывода ошибок)
	int size = 0;
	std::vector<uint8_t> bin;
	bool uses_POINT;
};


const std::vector<std::string> possible_cmds = { "mov", "nop", "jmp" };
const std::vector<std::string> possible_size_identifiers = { "byte", "b", "word", "w" };
const std::vector<std::string> possible_registers = { "a", "b", "c", "d", "ax", "bx", "cx", "dx", "pc", "sp" };
const std::vector<std::string> possible_registers16 = { "ax", "bx", "cx", "dx", "pc", "sp" };
const std::vector<std::string> possible_registers8 = { "a", "b", "c", "d" };