#include "Lexer.h"



Lexer::Lexer()
{
	using a = Lexer;
	std::vector<Instrution> ins_table = {
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
}


Lexer::~Lexer()
{
}

std::vector<uint8_t> Lexer::analise(std::vector<Lexeme> operations)
{
	std::vector<uint8_t> program;
	for (Lexeme op : operations) 
	{
		switch (op.type)
		{
		case CPU_INSTRUCTION:
			analise_lexeme(op);
			break;
		case POINT_DEFINITION:
			break;
		case NONE:
			break;
		default:
			break;
		}
	}
	return program;
}

std::vector<uint8_t> Lexer::analise_lexeme(Lexeme op)
{
	std::vector<uint8_t> command;
	
	for (int i = 0; i < instruction_table.size(); i++)
	{
		if (op.cmd != instruction_table[i].name)
			continue;

		if ((this->*instruction_table[i].arg0_validator)(op.arg0) && (this->*instruction_table[i].arg1_validator)(op.arg1))
		{
			command.push_back(instruction_table[i].code);
			// ебана€ хуйн€€€€€€ бл€ть ебать его перфоратором сукааааааааааа не работает ниху€ 
			// ааааааааааааа

			break;
		}
	}
	
	if (command.size() == 0) 
	{
		char buf[70];
		sprintf_s(buf, "Line %d can't compile \"%s\"", op.line, op.full_command.c_str());
		throw (std::string)buf;
	}
	return command;
}


// валидаторы аргументов

bool Lexer::register8(std::string text)
{
	for (std::string possible_token : possible_registers8)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}
bool Lexer::register16(std::string text)
{
	for (std::string possible_token : possible_registers16)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}
bool Lexer::dec_number(std::string text)
{
	for (auto ch : text)
		if (ch < '0' || ch > '9')
			return false;

	return true;
}
bool Lexer::hex_number(std::string text)
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


bool Lexer::ptr_in_register(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return register16(text) || register8(text);
}
bool Lexer::ptr_in_dec_number(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return dec_number(text);
}
bool Lexer::ptr_in_hex_number(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return hex_number(text);
}

bool Lexer::named_ptr(std::string text)
{
	if (dec_number(text.substr(0, 1)) || text.substr(text.size() - 1, 1) == ":")
		return false;
	for (auto ch : text)
		if ((ch < 'a' || ch > 'z') && (ch < '0' || ch > '9'))
			if (ch != '_' && ch != '-')
				return false;
	return true;
}
bool Lexer::ptr_in_named_ptr(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return named_ptr(text);
}
bool Lexer::named_ptr_definition(std::string text)
{
	if (text.substr(text.size() - 1, 1) != ":")
		return false;
	else
		text = text.substr(0, text.size() - 2);

	return named_ptr(text);
}

bool Lexer::no_arg(std::string text)
{
	if (text == "")
		return true;
	else
		return false;

}


// компил€торы аргументов
std::vector<uint8_t> Lexer::compile_dec_number(std::string text)
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
std::vector<uint8_t> Lexer::compile_hex_number(std::string text)
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
std::vector<uint8_t> Lexer::compile_register(std::string text)
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

std::string Lexer::delete_brackets(std::string text)
{
	return text.substr(1).substr(0, text.size() - 2);
}
bool Lexer::has_brackets(std::string text)
{
	return text.substr(0, 1) == "[" && text.substr(text.size() - 1) == "]";
}