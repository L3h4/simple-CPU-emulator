#pragma once
#include<iostream>
#include<stdio.h>

#define u8 uint8_t
#define u16 uint16_t

class Status
{

public:
	bool execute_til_hlt = false; // режим виполнения программы до команды HLT (прекратить выполнение)
	bool execute_til_ie = false; // режим виполнения программы до команды IE (прервать выполнение)
	bool erorr = false; // флаг ошибки
public:
	// типы ошибок
	enum Exceptions {
		UNKNOWN_REGISTER,
		READONLY_REGISTER,
		BAD_ADDRESS,
		READONLY_MEMORY,
		UNEXECUTABLE_MEMORY,
		UNREADABLE_MEMORY,
		UNKNOWN_INSTRUCTION
	};
	void raise_exception(u16 PC, Exceptions e_type, std::string text) 
	{
		// метод выводит где произошла ошибка и что именно пошло не так
		erorr = true;
		execute_til_hlt = false;
		std::string e_type_str;
		printf("\n===========================================\n");
		printf("Raised critical exceptin!\nExecution stoped\n");
		switch (e_type) 
		{
		case UNKNOWN_REGISTER:
			e_type_str = "Unknown register";
			break;
		case READONLY_REGISTER:
			e_type_str = "Readonly register";
			break;
		case BAD_ADDRESS:
			e_type_str = "Bad address";
			break;
		case READONLY_MEMORY:
			e_type_str = "Read only memory";
			break;
		case UNEXECUTABLE_MEMORY:
			e_type_str = "Unexecutable memory";
			break;
		case UNREADABLE_MEMORY:
			e_type_str = "Unreadable memory";
			break;
		case UNKNOWN_INSTRUCTION:
			e_type_str = "Unknown instruction";
			break;
		default:
			break;
		}
		printf("0x%.4X %s: \n\t%s\n", PC, e_type_str.c_str(), text.c_str());
		printf("===========================================\n");
	}
};

