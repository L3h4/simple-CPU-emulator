#include "Lexer.h"
using namespace utilities;


Lexer::Lexer()
{
	instruction_table = 
	{
		{ 0x0, "nop", "", NOARG, NOARG, 1 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},

		{ 0x10, "mov", "b", REGISTER, NUMBER,          3 }, { 0x11, "mov", "b", PTR_IN_REGISTER, NUMBER,          3 }, { 0x12, "mov", "b", PTR_IN_NUMBER, NUMBER,          4 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x20, "mov", "b", REGISTER, REGISTER,        3 }, { 0x21, "mov", "b", PTR_IN_REGISTER, REGISTER,        3 }, { 0x22, "mov", "b", PTR_IN_NUMBER, REGISTER,        4 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x30, "mov", "b", REGISTER, PTR_IN_NUMBER,   4 }, { 0x31, "mov", "b", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { 0x32, "mov", "b", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x40, "mov", "b", REGISTER, PTR_IN_REGISTER, 3 }, { 0x41, "mov", "b", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { 0x42, "mov", "b", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},

		{ 0x50, "mov", "w", REGISTER, NUMBER,          4 }, { 0x51, "mov", "w", PTR_IN_REGISTER, NUMBER,          4 }, { 0x52, "mov", "w", PTR_IN_NUMBER, NUMBER,          5 }, { 0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x60, "mov", "w", REGISTER, REGISTER,        3 }, { 0x61, "mov", "w", PTR_IN_REGISTER, REGISTER,        3 }, { 0x62, "mov", "w", PTR_IN_NUMBER, REGISTER,        4 }, { 0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x70, "mov", "w", REGISTER, PTR_IN_NUMBER,   4 }, { 0x71, "mov", "w", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { 0x72, "mov", "w", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 }, { 0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x80, "mov", "w", REGISTER, PTR_IN_REGISTER, 3 }, { 0x81, "mov", "w", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { 0x82, "mov", "w", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 }, { 0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},

		{ 0x90, "jmp", "", NUMBER, NOARG, 3 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x0, "nop", "", NOARG, NOARG, 1 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x0, "nop", "", NOARG, NOARG, 1 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x0, "nop", "", NOARG, NOARG, 1 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x0, "nop", "", NOARG, NOARG, 1 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x0, "nop", "", NOARG, NOARG, 1 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
		{ 0x0, "nop", "", NOARG, NOARG, 1 }, { 0x0, "nop", "", NOARG, NOARG, 1 }, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1}, {0x0, "nop", "", NOARG, NOARG, 1},
	};
}


Lexer::~Lexer()
{
}

std::vector<uint8_t> Lexer::analise(std::vector<Lexeme> operations)
{
	std::vector<uint8_t> res;
	program = operations;
	analise_sizes();
	analise_named_pointers();
	compile();

	for (auto inst : program)
	{
		res = concat_vectors(res, inst.bin);
	}

	return res;
}

void Lexer::analise_sizes()
{
	for (int i = 0; i < program.size(); i++)
	{
		if (program[i].type != CPU_INSTRUCTION)
			continue;

		//printf("Line %d : Analising %s\n", program[i].line, program[i].cmd.c_str());
		//printf("%-4d : %-5s %s  %s  %s\n", program[i].line, program[i].cmd.c_str(), program[i].size_identifier.c_str(), program[i].arg0.c_str(), program[i].arg1.c_str());
		for (int j = 0; j < instruction_table.size(); j++)
		{
			if (program[i].cmd != instruction_table[j].name)
				continue;
			if (program[i].cmd == instruction_table[j].name && program[i].arg0_type == instruction_table[j].arg0_type && program[i].arg1_type == instruction_table[j].arg1_type && program[i].size_identifier == instruction_table[j].size_identifier)
			{
				program[i].size = instruction_table[j].size;
				//program[i].bin.push_back(instruction_table[j].code);
				break;
			}

		}
		if (program[i].size == 0)
		{
			char buf[70];
			sprintf_s(buf, "Line %d can't understand \"%s\"", program[i].line, program[i].full_command.c_str());
			throw (std::string)buf;
		}
	}
}

void Lexer::analise_named_pointers()
{
	std::vector<Point> definitions;
	for (int i = 0; i < program.size(); i++)
	{
		if (program[i].type == CPU_INSTRUCTION)
			continue;
		else if (program[i].type == POINT_DEFINITION)
		{
			definitions.push_back(Point(program[i].named_ptr, get_instruction_addres(i)));
		}
	}
	for (auto p : definitions)
	{
		for (int i = 0; i < program.size(); i++)
		{

			if (utilities::delete_brackets(program[i].arg0) == p.name)
			{
				program[i].arg0 = std::to_string(p.address);
				program[i].uses_POINT = false;
			}
			else if (named_ptr(delete_brackets(program[i].arg0)))
			{
				char buf[70];
				sprintf_s(buf, "Line %d unknown pointer \"%s\"", program[i].line, program[i].arg0.c_str());
				throw (std::string)buf;
			}
			if (delete_brackets(program[i].arg1) == p.name)
			{
				program[i].arg1 = std::to_string(p.address);
				program[i].uses_POINT = false;
			}
			else if (named_ptr(delete_brackets(program[i].arg1)))
			{
				char buf[70];
				sprintf_s(buf, "Line %d unknown pointer \"%s\"", program[i].line, program[i].arg1.c_str());
				throw (std::string)buf;
			}
			printf("%s %s, %s\n", program[i].cmd.c_str(), program[i].arg0.c_str(), program[i].arg1.c_str());

		}
	}
}

void Lexer::compile()
{

	for (int i = 0; i < program.size(); i++)
	{
		if (program[i].type != CPU_INSTRUCTION)
			continue;

		for (int j = 0; j < instruction_table.size(); j++)
		{
			if (program[i].cmd != instruction_table[j].name)
				continue;
			else if (program[i].cmd == instruction_table[j].name && program[i].arg0_type == instruction_table[j].arg0_type && program[i].arg1_type == instruction_table[j].arg1_type && program[i].size_identifier == instruction_table[j].size_identifier)
			{
				program[i].bin.push_back(instruction_table[j].code);

				if (program[i].arg0_type == NUMBER)
				{
					int size = program[i].size - program[i].bin.size();
					if (size <= 2 && size > 0)
					{
						try
						{
							program[i].bin = concat_vectors(program[i].bin, compile_number(delete_brackets(program[i].arg0), size));
						}
						catch (std::string e)
						{
							char buf[70];
							sprintf_s(buf, "Line %d %s", program[i].line, e.c_str());
							throw (std::string)buf;
						}
					}
					else
					{
						char buf[70];
						sprintf_s(buf, "Line %d cant compile number \"%s\"", program[i].line, program[i].arg0.c_str());
						throw (std::string)buf;
					}
				}
				else if (program[i].arg0_type == PTR_IN_NUMBER)
				{
					try
					{
						program[i].bin = concat_vectors(program[i].bin, compile_number(delete_brackets(program[i].arg0), 2));
					}
					catch (std::string e)
					{
						char buf[70];
						sprintf_s(buf, "Line %d %s", program[i].line, e.c_str());
						throw (std::string)buf;
					}
				}
				else if (program[i].arg0_type == REGISTER || program[i].arg0_type == PTR_IN_REGISTER)
				{
					try
					{
						program[i].bin = concat_vectors(program[i].bin, compile_register(delete_brackets(program[i].arg0)));
					}
					catch (std::string e)
					{
						char buf[70];
						sprintf_s(buf, "Line %d %s", program[i].line, e.c_str());
						throw (std::string)buf;
					}
				}
				else
				{
				}
				
				if (program[i].arg1_type == NUMBER)
				{
					int size = program[i].size - program[i].bin.size();
					if (size <= 2 && size > 0)
					{
						try
						{
							program[i].bin = concat_vectors(program[i].bin, compile_number(delete_brackets(program[i].arg1), size));
						}
						catch (std::string e)
						{
							char buf[70];
							sprintf_s(buf, "Line %d %s", program[i].line, e.c_str());
							throw (std::string)buf;
						}
					}
					else
					{
						char buf[70];
						sprintf_s(buf, "Line %d cant compile number \"%s\"", program[i].line, program[i].arg1.c_str());
						throw (std::string)buf;
					}
				}
				else if (program[i].arg1_type == PTR_IN_NUMBER)
				{
					try
					{
						program[i].bin = concat_vectors(program[i].bin, compile_number(delete_brackets(program[i].arg1), 2));
					}
					catch (std::string e)
					{
						char buf[70];
						sprintf_s(buf, "Line %d %s", program[i].line, e.c_str());
						throw (std::string)buf;
					}
				}
				else if (program[i].arg1_type == REGISTER || program[i].arg1_type == PTR_IN_REGISTER)
				{
					try
					{
						program[i].bin = concat_vectors(program[i].bin, compile_register(delete_brackets(program[i].arg1)));
					}
					catch (std::string e)
					{
						char buf[70];
						sprintf_s(buf, "Line %d %s", program[i].line, e.c_str());
						throw (std::string)buf;
					}
				}
				else
				{
				}

				printf("Line %d { ", program[i].line);
				for (auto num : program[i].bin)
				{
					printf("0x%.2X, ", num);
				}
				printf("\b\b }\n");
				break;
			}
		}
		if (program[i].size == 0)
		{
			char buf[70];
			sprintf_s(buf, "Line %d can't compile \"%s\"", program[i].line, program[i].full_command.c_str());
			throw (std::string)buf;
		}
	}
}

int Lexer::get_instruction_addres(int i)
{
	int address = 0;
	for (int a = 0; a < i; a++)
	{
		address += program[a].size;
	}
	return address;
}


