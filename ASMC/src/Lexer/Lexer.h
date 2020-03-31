#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"../Operation/Operation.h"
#include "../Utilities/CompilingUtilities.h"

// Класс котрый отвечает за лексический анализ и генерацию кода
class Lexer
{
public:
	Lexer();
	~Lexer();
	Lexer(bool debug);

public:
	std::vector<uint8_t> analise(std::vector<Lexeme> operations);

private:
	void analise_sizes();
	void analise_named_pointers();
	void compile();

	int get_instruction_addres(int i);

	struct Instrution
	{
		uint8_t code;
		std::string name;
		std::string size_identifier;
		arg_type arg0_type;
		arg_type arg1_type;
		int size;
	};
	struct NamedPtr 
	{
		NamedPtr(std::string name, int addr)
		{
			this->name = name.substr(0, name.length() - 1);
			address = addr;
		}
		int address;
		std::string name;
	};



private:


	std::vector<Instrution> instruction_table;
	std::vector<Lexeme> program;
	bool debug = false;
};

