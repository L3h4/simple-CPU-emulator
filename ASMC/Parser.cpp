#include "Parser.h"



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
	int line_counter = 1;

	if (!file)
		throw "File not found " + file_name;

	while (std::getline(file, line)) {
		std::transform(line.begin(), line.end(), line.begin(), std::tolower);
		Lexeme op = parse_line(line, line_counter++);
		operations.push_back(op);
	}
	file.close();
	return operations;
}


Lexeme Parser::parse_line(std::string line, int line_N)
{
	Lexeme op;
	op.full_command = line;
	line.erase(std::remove(line.begin(), line.end(), ','), line.end());
	line = line.substr(0, line.find(';'));
	op.line = line_N;
	if (line == "") 
	{
		op.type = NONE;
		return op;
	}

	//printf("%s\n", line.c_str());
	
	std::istringstream f(line);
	std::string token;
	int argid = 0;

	while (std::getline(f, token, ' '))
	{
		if (token == "" ) 
		{
			continue;
		}
		else if (is_named_ptr_definition(token))
		{
			op.named_ptr = token;
			op.type = POINT_DEFINITION;
		}
		else if (is_instruction(token)) {
			op.cmd = token;
			op.type = CPU_INSTRUCTION;
		}
		else if (is_size_identifier(token)) {
			op.size_identifier = token;
		}
		else if (is_register(token)) {
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else if (is_dec_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else if (is_hex_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else if (is_named_ptr(token))
		{
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else if (is_ptr_in_register(token)) {
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else if (is_ptr_in_dec_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else if (is_ptr_in_hex_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else if (is_ptr_in_named_ptr(token))
		{
			if (argid == 0) {
				op.arg0 = token;
			}
			else if (argid == 1) {
				op.arg1 = token;
			}
			argid++;
		}
		else
		{
			char buf[70];
			sprintf_s(buf, "Line: %d unknown token \"%s\"", line_N, token.c_str());
			throw (std::string)buf;
		}

		if (argid > 2) 
		{
			char buf[70];
			sprintf_s(buf, "Line: %d at \"%s\" can't understand argument \"%s\"", line_N, op.full_command.c_str(), token.c_str());
			throw (std::string)buf;
		}

	}

	if(debug)
		printf("%-4d : %-5s %s  %s  %s\n", line_N, op.cmd.c_str(), op.size_identifier.c_str(), op.arg0.c_str(), op.arg1.c_str());

		if (op.cmd == "" && op.type == CPU_INSTRUCTION) 
		{
			char buf[70];
			sprintf_s(buf, "Line: %d bad operation \"%s\"", line_N, op.full_command.c_str());
			throw (std::string)buf;
		}
	return op;
}

bool Parser::is_instruction(std::string text)
{
	for (std::string possible_token : possible_cmds)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}

bool Parser::is_size_identifier(std::string text)
{
	for (std::string possible_token : possible_size_identifiers) 
	{
		if(text == possible_token)
		return true;
	}
	return false;
}

bool Parser::is_register(std::string text)
{
	for (std::string possible_token : possible_registers)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}

bool Parser::is_dec_number(std::string text)
{
	for (auto ch : text) 
		if (ch < '0' || ch > '9')
			return false;

	return true;
}

bool Parser::is_hex_number(std::string text)
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

bool Parser::is_ptr_in_register(std::string text)
{
	if (text.substr(0, 1) != "[" && text.substr(text.size() - 1) != "]")
		return false;
	else
		text = text.substr(1).substr(0, text.size() - 2);;

	return is_register(text);
}

bool Parser::is_ptr_in_dec_number(std::string text)
{
	if (text.substr(0, 1) != "[" && text.substr(text.size() - 1) != "]")
		return false;
	else
		text = text.substr(1).substr(0, text.size() - 2);;

	return is_dec_number(text);
}

bool Parser::is_ptr_in_hex_number(std::string text)
{
	if (text.substr(0, 1) != "[" && text.substr(text.size() - 1) != "]")
		return false;
	else
		text = text.substr(1).substr(0, text.size() - 2);;

	return is_hex_number(text);
}

bool Parser::is_ptr_in_named_ptr(std::string text)
{
	if (text.substr(0, 1) != "[" && text.substr(text.size() - 1) != "]")
		return false;
	else
		text = text.substr(1).substr(0, text.size() - 2);;

	return is_named_ptr(text);
}


bool Parser::is_named_ptr(std::string text)
{
	if (is_dec_number(text.substr(0, 1)) || text.substr(text.size() - 1, 1) == ":")
		return false;
	for (auto ch : text)
		if ((ch < 'a' || ch > 'z') && (ch < '0' || ch > '9'))
			if (ch != '_' && ch != '-')
				return false;
	return true;
}

bool Parser::is_named_ptr_definition(std::string text)
{
	if (text.substr(text.size() - 1, 1) != ":")
		return false;
	else
		text = text.substr(0, text.size() - 2);

	return is_named_ptr(text);
}