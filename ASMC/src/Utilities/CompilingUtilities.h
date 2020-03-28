#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"../Operation/Operation.h"


namespace utilities
{
	std::vector<uint8_t> concat_vectors(std::vector<uint8_t> a, std::vector<uint8_t> b);
	bool has_brackets(std::string text);

	std::string delete_brackets(std::string text);
	std::string trim(const std::string& str);

	// валидаторы аргументов
	bool is_instruction(std::string text);
	bool is_size_identifier(std::string text);



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

	bool is_ptr_in_named_ptr(std::string text);


	bool no_arg(std::string text);


	// компиляторы аргументов
	std::vector<uint8_t> compile_dec_number(std::string text, int size);
	std::vector<uint8_t> compile_hex_number(std::string text, int size);
	std::vector<uint8_t> compile_number(std::string text, int size);
	std::vector<uint8_t> compile_register(std::string text);
}