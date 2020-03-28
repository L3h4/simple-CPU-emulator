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
	int line_counter = 1;

	if (!file)
		throw "File not found " + file_name;

	while (std::getline(file, line)) {
		std::transform(line.begin(), line.end(), line.begin(), std::tolower);
		Lexeme op = parse_line(line, line_counter++);
		if(op.type != NONE)
			operations.push_back(op);
	}
	file.close();
	return operations;
}


Lexeme Parser::parse_line(std::string line, int line_N)
{
	Lexeme op;
	op.full_command = trim(line);
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
	int pos = 0;
	bool size_modifier_read_only = false;

	while (std::getline(f, token, ' '))
	{
		if (token == "" ) 
		{
			continue;
		}
		else if (named_ptr_definition(token))
		{
			op.named_ptr = token;
			op.type = POINT_DEFINITION;
			
		}
		else if (is_instruction(token)) {
			op.cmd = token;
			op.type = CPU_INSTRUCTION;
		}
		else if (is_size_identifier(token) && pos == 1) {
			if (!size_modifier_read_only)
			{
				op.size_identifier = (token == "word" || token == "w") ? "w" : op.size_identifier;
				op.size_identifier = (token == "byte" || token == "b") ? "b" : op.size_identifier;
				size_modifier_read_only = true;
			}
			else
			{
				char buf[70];
				sprintf_s(buf, "Line: %d unknown modifier \"%s\"", line_N, token.c_str());
				throw (std::string)buf;
			}
		}
		else if (register8(token) || register16(token)) {
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type =  REGISTER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = REGISTER;
			}

			if (!size_modifier_read_only)
			{
				op.size_identifier = (op.size_identifier == "") && register16(token) ? "w" : (op.size_identifier == "") ? "b" : op.size_identifier;
				op.size_identifier = (op.size_identifier == "w" || op.size_identifier == "word") && !register16(token) ? "b" : op.size_identifier;
			}
			argid++;
		}
		else if (dec_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type = NUMBER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = NUMBER;
			}
			argid++;
			if (op.size_identifier == "")
			{
				unsigned int x;
				sscanf_s(token.c_str(), "%d", &x);
				op.size_identifier = x > 0xFF && x < 0xFFFF ? "w" : "b";
			}
		}
		else if (hex_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type = NUMBER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = NUMBER;
			}
			argid++;
			if (op.size_identifier == "")
			{
				unsigned int x;
				sscanf_s(token.c_str(), "%x", &x);
				op.size_identifier = x > 0xFF && x < 0xFFFF ? "w" : "b";
			}
		}
		else if (named_ptr(token) && op.cmd != "")
		{
			op.uses_POINT = true;
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type = NUMBER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = NUMBER;
			}
			argid++;
		}
		else if (ptr_in_register(token) && has_brackets(token)) {
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type = register16(delete_brackets(token)) ? PTR_IN_REGISTER : PTR_IN_REGISTER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = register16(delete_brackets(token)) ? PTR_IN_REGISTER : PTR_IN_REGISTER;
			}
			if (!size_modifier_read_only)
			{
				op.size_identifier = (op.size_identifier == "") && register16(delete_brackets(token)) ? "w" : (op.size_identifier == "") ? "b" : op.size_identifier;
				op.size_identifier = (op.size_identifier == "w" || op.size_identifier == "word") && !register16(delete_brackets(token)) ? "b" : op.size_identifier;
			}
			argid++;
		}
		else if (ptr_in_dec_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type = PTR_IN_NUMBER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = PTR_IN_NUMBER;
			}
			argid++;
		}
		else if (ptr_in_hex_number(token)) {
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type = PTR_IN_NUMBER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = PTR_IN_NUMBER;
			}
			argid++;
		}
		else if (is_ptr_in_named_ptr(token) && has_brackets(token))
		{
			op.uses_POINT = true;
			if (argid == 0) {
				op.arg0 = token;
				op.arg0_type = PTR_IN_NUMBER;
			}
			else if (argid == 1) {
				op.arg1 = token;
				op.arg1_type = PTR_IN_NUMBER;
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
		pos++;
	}

	if(debug)
		printf("%d : %-5s %s  %s  %s\n", line_N, op.cmd.c_str(), op.size_identifier.c_str(), op.arg0.c_str(), op.arg1.c_str());

	if (op.cmd == "" && op.type == CPU_INSTRUCTION) 
	{
		char buf[70];
		sprintf_s(buf, "Line: %d bad operation \"%s\"", line_N, op.full_command.c_str());
		throw (std::string)buf;
	}
	return op;
}

