#include "Parser.h"
using namespace utilities;


Parser::Parser()
{

}


Parser::~Parser()
{
}

Parser::Parser(bool dbg)
{
	debug = dbg;
}

std::vector<Lexeme> Parser::parse_from_file(std::string file_name)
{
	std::fstream file(file_name);
	std::vector<Lexeme> operations;
	std::string line;
	int line_counter = 1; // счетчик номера строки

	if (!file)
		throw "File not found " + file_name;

	while (std::getline(file, line)) { // Читаем файл построчно
		line = trim(line); // Обрезать лишние пробелы и табы
		
		Lexeme op = parse_line(line, line_counter++); // парсим
		if(op.type != NONE) // если получилось добавляем в масив
			operations.push_back(op);
	}
	file.close();
	return operations;
}


Lexeme Parser::parse_line(std::string line, int line_N)
{
	// Добро пожаловать в обитель говнокода 
	// тут происходит магия парсинга

	Lexeme op;
	
	line = line.substr(0, line.find(';'));

	op.line = line_N;
	if (line == "")
		return op;

	op.full_command = line;

	
	line = replace_string(line, ",", " , ");

	
	std::istringstream f(line);
	std::string token;
	int argpos = 0;
	bool size_modifier_set_by_user = false;
	std::vector<std::string> tokens;
	

	while (std::getline(f, token, ' '))
	{
		if (token == "" || token == " ")
			continue;

		tokens.push_back(token);
	}

	for (int i = 0; i < tokens.size(); i++)
	{
		token = tokens[i];
		if (i == 0)
		{
			if (named_ptr_definition(token))
			{
				op.type = POINT_DEFINITION;
				
				if (tokens.size() - 1 > i)
				{
					if (is_preprocessor_instruction(to_lower(tokens[i + 1])))
						op.type = PREPROCESSOR_INSTRUCTION;
					else
					{
						char buf[70];
						sprintf_s(buf, "Line: %d unknown token \"%s\"", line_N, token.c_str());
						throw (std::string)buf;
					}
				}
				
				op.named_ptr = token;
			}
			else if (is_instruction(to_lower(token)))
			{
				op.cmd = token;
				op.type = CPU_INSTRUCTION;
				
			}
			else if (is_metadata(to_lower(token)))
			{
				op.type = META_DATA;
			}
			else
			{
				char buf[70];
				sprintf_s(buf, "Line: %d unknown token \"%s\"", line_N, token.c_str());
				throw (std::string)buf;
			}
			continue;
		}

		if (op.type == CPU_INSTRUCTION)
		{
			if (is_size_identifier(to_lower(token)) && op.size_identifier == "")
			{
				op.size_identifier = (to_lower(token) == "word" || to_lower(token) == "w") ? "w" : (to_lower(token) == "byte" || to_lower(token) == "b") ? "b" : op.size_identifier;
				size_modifier_set_by_user = true;
				i++;
				token = tokens[i];
			}

			if (token == ",")
			{
				i++;
				token = tokens[i];
			}

			if (register8(to_lower(token)) || register16(to_lower(token)))
			{
				if (argpos == 0) {
					op.arg0 = to_lower(token);
					op.arg0_type = REGISTER;
				}
				else if (argpos == 1) {
					op.arg1 = to_lower(token);
					op.arg1_type = REGISTER;
				}
				if (!size_modifier_set_by_user)
				{
					op.size_identifier = (op.size_identifier == "") && register16(to_lower(token)) ? "w" : (op.size_identifier == "") ? "b" : op.size_identifier;
					op.size_identifier = (op.size_identifier == "w" || op.size_identifier == "word") && !register16(to_lower(token)) ? "b" : op.size_identifier;
				}

				argpos++;
			}
			else if (dec_number(token) || hex_number(to_lower(token))) {
				if (argpos == 0) {
					op.arg0 = to_lower(token);
					op.arg0_type = NUMBER;
				}
				else if (argpos == 1) {
					op.arg1 = to_lower(token);
					op.arg1_type = NUMBER;
				}
				if (op.size_identifier == "" && !size_modifier_set_by_user)
				{
					int x;
					if (dec_number(to_lower(token)))
						sscanf_s(to_lower(token).c_str(), "%d", &x);
					else
						sscanf_s(to_lower(token).c_str(), "%x", &x);

					if (x < 0) x = -x;
					op.size_identifier = x > 0xFF ? "w" : "b";
				}
				argpos++;
			}
			else if (named_ptr(token))
			{
				op.uses_POINT = true;
				if (argpos == 0) {
					op.arg0 = token;
					op.arg0_type = NUMBER;
				}
				else if (argpos == 1) {
					op.arg1 = token;
					op.arg1_type = NUMBER;
				}
				argpos++;
			}
			else if (ptr_in_register(to_lower(token)) && has_brackets(token)) 
			{
				if (argpos == 0) 
				{
					op.arg0 = to_lower(token);
					op.arg0_type = PTR_IN_REGISTER;
				}
				else if (argpos == 1) 
				{
					op.arg1 = to_lower(token);
					op.arg1_type = PTR_IN_REGISTER;
				}
				if (!size_modifier_set_by_user)
				{
					op.size_identifier = (op.size_identifier == "") && register16(delete_brackets(to_lower(token))) ? "w" : (op.size_identifier == "") ? "b" : op.size_identifier;
					op.size_identifier = (op.size_identifier == "w" || op.size_identifier == "word") && !register16(delete_brackets(to_lower(token))) ? "b" : op.size_identifier;
				}
				argpos++;
			}
			else if (ptr_in_dec_number(token) || ptr_in_hex_number(to_lower(token)))
			{
				if (argpos == 0) 
				{
					op.arg0 = to_lower(token);
					op.arg0_type = PTR_IN_NUMBER;
				}
				else if (argpos == 1) 
				{
					op.arg1 = to_lower(token);
					op.arg1_type = PTR_IN_NUMBER;
				}
				argpos++;
			}

			else if (ptr_in_named_ptr(token) && has_brackets(token))
			{
				op.uses_POINT = true;
				if (argpos == 0) {
					op.arg0 = token;
					op.arg0_type = PTR_IN_NUMBER;
				}
				else if (argpos == 1) {
					op.arg1 = token;
					op.arg1_type = PTR_IN_NUMBER;
				}
				argpos++;
			}
			else
			{
				char buf[70];
				sprintf_s(buf, "Line: %d unknown token \"%s\"", line_N, token.c_str());
				throw (std::string)buf;
			}

		}
		else if (op.type == PREPROCESSOR_INSTRUCTION)
		{
			if (is_preprocessor_instruction(to_lower(token)))
			{
				
				if (tokens.size() - 1 == i)
				{
					char buf[70];
					sprintf_s(buf, "Line: %d in \"%s\" string not specified", line_N, op.full_command.c_str());
					throw (std::string)buf;
				}

				std::string str;
				for (int j = i+1; j < tokens.size(); j++)
				{
					str += tokens[j]+ " ";
				}
				str = str.substr(0, str.size()-1);

				if (!has_quotes(str))
				{
					char buf[70];
					sprintf_s(buf, "Line: %d in \"%s\" bad string", line_N, op.full_command.c_str());
					throw (std::string)buf;
				}

				op.bin = compile_string(delete_quotes(str));
				break;
				
				/*
				if (to_lower(token) == "word")
				{
					if (dec_number(tokens[i + 1]) || hex_number(to_lower(tokens[i + 1])))
					{
						op.bin = compile_number(tokens[i + 1], 2);
					}
					//else
				}
				*/
			}
		}

	}


	if (debug && op.type == CPU_INSTRUCTION)
		printf("%-2d : %-5s %s  %s  %s\n", line_N, op.cmd.c_str(), op.size_identifier.c_str(), op.arg0.c_str(), op.arg1.c_str());

	if (debug && op.type == POINT_DEFINITION)
		printf("\n%-2d : %s\n", line_N, op.named_ptr.c_str());

	return op;
}

