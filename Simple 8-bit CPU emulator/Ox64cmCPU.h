#pragma once
#include<iostream>
#include<vector>

#include"Bus.h"
#include"Status.hpp"


#define u8 uint8_t
#define u16 uint16_t

// раскомментируйте следующую строку, чтобы видеть дебаг комментарии
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
	16/8 битные регистры

	типа как
	_______________________
	|	 AX (16 бит)      |
	|         | A (8 бит) |
	*/
	struct Register {
		std::string name; // текстовое имя регистра для дисассембли
		std::string name16; // текстовое имя 16-битного регистра для дисассембли
		union
		{
			u8 lo; // младшие 8 бит
			u16 value; // все 16 бит
		};
	};

public:
	// Регистры общего назначения 
	Register AX{ "A", "AX" };
	Register BX{ "B", "BX" };
	Register CX{ "C", "CX" };
	Register DX{ "D", "DX" };

	Register PC{ "PC", "PC" }; // счетчик программы
	Register SP{ "SP", "SP" }; // указатель стэка

	// 8-битный статус регистр
	union
	{
		struct {
			bool Z : 1; // Флаг ноля
			bool C : 1; // Флаг переноса
			bool u : 5; // Не используется
			bool S : 1; // Флаг знака (0 : + | 1 : -)
		};
		u8 value;
	}STATUS;

public:
	void print_regs(); // Вывод значений регистров в консоль

private:
	Register *parse_reg(u8 code);


private:
	// Обьявление структуры ИНСТРУКЦИЯ
	struct Instructin
	{
		std::string name; // текстовое представление, нужно для вывода дисассембли
		void(Ox64cmCPU::*execute)(void) = nullptr; // указатель на обработчик операции
		std::string(Ox64cmCPU::*get_arg1)(void) = nullptr; // указатель на "парсер" 1 аргумента, возвращает строку с тем что он там напарсил(нужно для вывода дисассембли)
		std::string(Ox64cmCPU::*get_arg2)(void) = nullptr; // указатель на "парсер" 2 аргумента, возвращает строку с тем что он там напарсил(нужно для вывода дисассембли) 
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


private:
	enum argTypes // Перречисление всех типов аргументов (8бит. значение, 16бит. значение, регистр ...)
	{
		IMMDATA,
		IMMDATA16,

		REGISTER,
		REGISTER16,

		// ВАЖНО все адреса 16 битные, просто они показивают сколлько записать/прочитать битов
		ADDRESS, // пишет/читает 1 байт
		ADDRESS16, // пишет/читает 2 байта
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
	bool arg_id = false; // флаг аргументов. Если false то парсм 1 аргумент иначе 2
	OpArg arg1; // аргумент 1
	OpArg arg2; // аргумент 2
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
	

	// функции парсинга аргументов. Возвращают строку с тем что он там напарсил(нужно для вывода дисассембли) 
	std::string V(); std::string V16(); std::string R(); std::string aR(); std::string R16(); std::string aR16(); std::string A(); std::string A16();
	std::string NA();

public:
	Bus* bus;
	Status* status;
	std::vector<Instructin> opcodes;
};

