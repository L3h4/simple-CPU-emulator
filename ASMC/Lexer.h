#pragma once
#include<iostream>
#include<vector>
#include"Operation.h"


// Класс котрый отвечает за лексический анализ
class Lexer
{
public:
	Lexer();
	~Lexer();
public:
	std::vector<uint8_t> analise(std::vector<Lexeme> operations);

private:
	std::vector<uint8_t> analise_lexeme(Lexeme op);

	struct Instrution
	{
		std::string name;

		uint8_t code;

		bool(Lexer::*arg0_validator)(std::string) = nullptr;
		bool(Lexer::*arg1_validator)(std::string) = nullptr;

		std::vector<uint8_t>(Lexer::*arg0_compiler)(std::string) = nullptr;
		std::vector<uint8_t>(Lexer::*arg1_compiler)(std::string) = nullptr;

	};



private:
	std::string delete_brackets(std::string text);
	bool has_brackets(std::string text);
	bool register8(std::string text);
	bool register16(std::string text);
	bool dec_number(std::string text);
	bool hex_number(std::string text);
	bool ptr_in_register(std::string text);
	bool ptr_in_dec_number(std::string text);
	bool ptr_in_hex_number(std::string text);
	bool named_ptr(std::string text);
	bool ptr_in_named_ptr(std::string text);
	bool named_ptr_definition(std::string text);
	bool no_arg(std::string text);

	// компиляторы аргументов
	std::vector<uint8_t> compile_dec_number(std::string text);
	std::vector<uint8_t> compile_hex_number(std::string text);
	std::vector<uint8_t> compile_register(std::string text);


	std::vector<Instrution> instruction_table;
};

