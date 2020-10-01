#pragma once
#include<iostream>
#include<vector>

// Типы инструкций
enum type {
	CPU_INSTRUCTION,
	META_DATA,
	PREPROCESSOR_INSTRUCTION,
	POINT_DEFINITION,
	NONE
};
// типы аргументов
enum arg_type {
	REGISTER,
	NUMBER,
	PTR_IN_REGISTER,
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
	type type = NONE; // Флажок который помечает реальная ли это инструкция или чтото другое
	int line; // Номер строки на которой находится инструкция (нужно для вывода ошибок)
	int size = 0; // размер операции в бинарном виде
	std::vector<uint8_t> bin; // сама бинарная программа
	bool uses_POINT = false; // 
};


const std::vector<std::string> possible_cmds = { "nop", "mov", "add", "sub", "hlt", "cmp", "jmp", "je", "jne", "jl", "jg", "jle", "jge", "push", "pop", "call", "ret", "syscall" }; // Все  возможные операции
const std::vector<std::string> possible_size_identifiers = { "byte", "b", "word", "w" }; // Все возможные типы данных
const std::vector<std::string> possible_registers = { "a", "b", "c", "d", "status", "ax", "bx", "cx", "dx", "pc", "sp" }; // Все возможные регистры
const std::vector<std::string> possible_registers16 = { "ax", "bx", "cx", "dx", "pc", "sp" }; // Все возможные 16 битные регистры
const std::vector<std::string> possible_registers8 = { "a", "b", "c", "d", "status" }; // Все возможные 8 битные регистры

const std::vector<std::string> possible_preprocessor_cmds = { "db", "word", "byte", "dw", "string" };
const std::vector<std::string> possible_metadata_cmds = { "entry", "rights" };
const std::vector<std::string> possible_rights = { "kernel", "root", "user" };
