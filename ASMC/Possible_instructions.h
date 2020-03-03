#pragma once
#include<vector>
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include"Operation.h"

/*
bool register8(std::string text);
bool register16(std::string text);
bool dec_number(std::string text);
bool hex_number(std::string text);
bool ptr_in_register(std::string text);
bool ptr_in_dec_number(std::string text);
bool ptr_in_hex_number(std::string text);
bool ptr_in_named_ptr(std::string text);
bool named_ptr(std::string text);
bool named_ptr_definition(std::string text);
bool no_arg(std::string text);

std::vector<uint8_t> compile_dec_number(std::string text);
std::vector<uint8_t> compile_hex_number(std::string text);
std::vector<uint8_t> compile_register(std::string text);
*/ 

struct Instrution 
{
	std::string name;

	uint8_t code;

	bool(*arg1_validator)(std::string text) = nullptr;
	bool(*arg2_validator)(std::string text) = nullptr;

	std::vector<uint8_t> (*arg1_compiler)(std::string text) = nullptr;
	std::vector<uint8_t> (*arg2_compiler)(std::string text) = nullptr;
	

	std::vector<uint8_t> compile(Lexeme op)
	{
		std::vector<uint8_t> command;
		command.push_back(code);
		std::vector<uint8_t> arg1 = arg1_compiler(op.arg0);
		command.insert(command.end(), arg1.begin(), arg1.end());
		std::vector<uint8_t> arg2 = arg2_compiler(op.arg1);
		command.insert(command.end(), arg2.begin(), arg2.end());
		return command;
	}
};





std::string delete_brackets(std::string text)
{
	return text.substr(1).substr(0, text.size() - 2);
}
bool has_brackets(std::string text)
{
	return text.substr(0, 1) == "[" && text.substr(text.size() - 1) == "]";
}

// валидаторы аргументов

bool register8(std::string text)
{
	for (std::string possible_token : possible_registers8)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}
bool register16(std::string text)
{
	for (std::string possible_token : possible_registers16)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}
bool dec_number(std::string text)
{
	for (auto ch : text)
		if (ch < '0' || ch > '9')
			return false;

	return true;
}
bool hex_number(std::string text)
{
	if (text.substr(0, 2) != "0x")
		return false;
	else
		text = text.substr(2);
	for (auto ch : text)
		if (('9' < ch || ch < '0') && ('f' < ch || ch < 'a'))
			return false;

	return true;
}


bool ptr_in_register(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return register16(text) || register8(text);
}
bool ptr_in_dec_number(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return dec_number(text);
}
bool ptr_in_hex_number(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return hex_number(text);
}

bool named_ptr(std::string text)
{
	if (dec_number(text.substr(0, 1)) || text.substr(text.size() - 1, 1) == ":")
		return false;
	for (auto ch : text)
		if ((ch < 'a' || ch > 'z') && (ch < '0' || ch > '9'))
			if (ch != '_' && ch != '-')
				return false;
	return true;
}
bool ptr_in_named_ptr(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return named_ptr(text);
}
bool named_ptr_definition(std::string text)
{
	if (text.substr(text.size() - 1, 1) != ":")
		return false;
	else
		text = text.substr(0, text.size() - 2);

	return named_ptr(text);
}

bool no_arg(std::string text)
{
	if (text == "")
		return true;
	else
		return false;
	
}


// компиляторы аргументов
std::vector<uint8_t> compile_dec_number(std::string text)
{
	std::vector<uint8_t> res;
	int x;
	sscanf_s(text.c_str(), "%d", &x);
	if (x < 256)
	{
		res.push_back((uint8_t)x);
	}
	else if (x > 255 && x < 65536)
	{
		uint8_t hi = x >> 8;
		uint8_t lo = x;
		res.push_back(hi);
		res.push_back(lo);
	}
	else
	{
		char buf[70];
		sprintf_s(buf, "Can't understand number 0x%X (%d)", x, x);
		throw (std::string)buf;
	}
	return res;
}
std::vector<uint8_t> compile_hex_number(std::string text)
{
	std::vector<uint8_t> res;
	int x;
	sscanf_s(text.c_str(), "0x%x", &x);
	if (x < 256)
	{
		res.push_back((uint8_t)x);
	}
	else if (x > 255 && x < 65536)
	{
		uint8_t hi = x >> 8;
		uint8_t lo = x;
		res.push_back(hi);
		res.push_back(lo);
	}
	else
	{
		char buf[70];
		sprintf_s(buf, "Can't understand number 0x%X (%d)", x, x);
		throw (std::string)buf;
	}
	return res;
}
std::vector<uint8_t> compile_register(std::string text)
{
	std::vector<uint8_t> res;

	if (text == "a") 
	{
		res.push_back(0xA);
	}
	else if (text == "b")
	{
		res.push_back(0xB);
	}
	else if (text == "c")
	{
		res.push_back(0xC);
	}
	else if (text == "d")
	{
		res.push_back(0xD);
	}
	else if (text == "ax")
	{
		res.push_back(0xAA);
	}
	else if (text == "bx")
	{
		res.push_back(0xBB);
	}
	else if (text == "cx")
	{
		res.push_back(0xCC);
	}
	else if (text == "dx")
	{
		res.push_back(0xDD);
	}
	else if (text == "pc")
	{
		res.push_back(0xEE);
	}
	else if (text == "sp")
	{
		res.push_back(0xFF);
	}
	else
	{
		char buf[70];
		sprintf_s(buf, "Can't understand register %s", text.c_str());
		throw (std::string)buf;
	}

	return res;
}



// массив всех инструкций
std::vector<Instrution> instruction_table = {
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr},
	{"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}, {"nop", 0x0, &a::no_arg, &a::no_arg, nullptr, nullptr}
};