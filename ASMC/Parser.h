#pragma once
#include<vector>
#include<stdio.h>
#include<iostream>
#include<sstream>
#include<cctype>
#include<algorithm>
#include<string>
#include<fstream>



#include"Operation.h"


class Parser
{
public:
	Parser();
	~Parser();

	Parser(bool dbg);

public:
	std::vector<Lexeme> parse_from_file(std::string file_name);

private:
	//std::vector<Operation> parse_from_text(std::string text);
	Lexeme parse_line(std::string line, int line_N);

	bool is_instruction(std::string text);

	bool is_size_identifier(std::string text);

	bool is_register(std::string text);
	bool is_dec_number(std::string text);
	bool is_hex_number(std::string text);

	bool is_ptr_in_register(std::string text);
	bool is_ptr_in_dec_number(std::string text);
	bool is_ptr_in_hex_number(std::string text);
	bool is_ptr_in_named_ptr(std::string text);

	bool is_named_ptr(std::string text);
	bool is_named_ptr_definition(std::string text);

private:
	bool debug;
};


