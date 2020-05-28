#include "Lexer.h"
using namespace utilities;


Lexer::Lexer()
{
	// таблица всех возможных опкодов, их сигнатур и размеров
	// например операция "mov [0x0000], 123" будет занимать 4 байта в памяти, 
	// а "mov word [0x0000], 123" будет занимать уже 5 байт
	instruction_table = 
	{
		{ "mov", "b", REGISTER, NUMBER,          3 }, { "mov", "b", PTR_IN_REGISTER, NUMBER,          3 }, { "mov", "b", PTR_IN_NUMBER, NUMBER,          4 }, /**/ { "add", "b", REGISTER, NUMBER,          3 }, { "add", "b", PTR_IN_REGISTER, NUMBER,          3 }, { "add", "b", PTR_IN_NUMBER, NUMBER,          4 }, /**/ { "sub", "b", REGISTER, NUMBER,          3 }, { "sub", "b", PTR_IN_REGISTER, NUMBER,          3 }, { "sub", "b", PTR_IN_NUMBER, NUMBER,          4 },  { "push", "b", NUMBER,          NOARG, 2 }, { "err", "", NOARG, NOARG, 1},             { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "nop", "", NOARG, NOARG, 1},
		{ "mov", "b", REGISTER, REGISTER,        3 }, { "mov", "b", PTR_IN_REGISTER, REGISTER,        3 }, { "mov", "b", PTR_IN_NUMBER, REGISTER,        4 }, /**/ { "add", "b", REGISTER, REGISTER,        3 }, { "add", "b", PTR_IN_REGISTER, REGISTER,        3 }, { "add", "b", PTR_IN_NUMBER, REGISTER,        4 }, /**/ { "sub", "b", REGISTER, REGISTER,        3 }, { "sub", "b", PTR_IN_REGISTER, REGISTER,        3 }, { "sub", "b", PTR_IN_NUMBER, REGISTER,        4 },  { "push", "b", REGISTER,        NOARG, 2 }, { "pop", "b", REGISTER,        NOARG, 2 }, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},
		{ "mov", "b", REGISTER, PTR_IN_NUMBER,   4 }, { "mov", "b", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "mov", "b", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 }, /**/ { "add", "b", REGISTER, PTR_IN_NUMBER,   4 }, { "add", "b", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "add", "b", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 }, /**/ { "sub", "b", REGISTER, PTR_IN_NUMBER,   4 }, { "sub", "b", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "sub", "b", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 },  { "push", "b", PTR_IN_NUMBER,   NOARG, 3 }, { "pop", "b", PTR_IN_NUMBER,   NOARG, 3 }, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},
		{ "mov", "b", REGISTER, PTR_IN_REGISTER, 3 }, { "mov", "b", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "mov", "b", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 }, /**/ { "add", "b", REGISTER, PTR_IN_REGISTER, 3 }, { "add", "b", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "add", "b", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 }, /**/ { "sub", "b", REGISTER, PTR_IN_REGISTER, 3 }, { "sub", "b", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "sub", "b", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 },  { "push", "b", PTR_IN_REGISTER, NOARG, 2 }, { "pop", "b", PTR_IN_REGISTER, NOARG, 2 }, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},

		{ "mov", "w", REGISTER, NUMBER,          4 }, { "mov", "w", PTR_IN_REGISTER, NUMBER,          4 }, { "mov", "w", PTR_IN_NUMBER, NUMBER,          5 }, /**/ { "add", "w", REGISTER, NUMBER,          4 }, { "add", "w", PTR_IN_REGISTER, NUMBER,          4 }, { "add", "w", PTR_IN_NUMBER, NUMBER,          5 }, /**/ { "sub", "w", REGISTER, NUMBER,          4 }, { "sub", "w", PTR_IN_REGISTER, NUMBER,          4 }, { "sub", "w", PTR_IN_NUMBER, NUMBER,          5 },  { "push", "w", NUMBER,          NOARG, 3 }, { "err", "", NOARG, NOARG, 1},             { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},
		{ "mov", "w", REGISTER, REGISTER,        3 }, { "mov", "w", PTR_IN_REGISTER, REGISTER,        3 }, { "mov", "w", PTR_IN_NUMBER, REGISTER,        4 }, /**/ { "add", "w", REGISTER, REGISTER,        3 }, { "add", "w", PTR_IN_REGISTER, REGISTER,        3 }, { "add", "w", PTR_IN_NUMBER, REGISTER,        4 }, /**/ { "sub", "w", REGISTER, REGISTER,        3 }, { "sub", "w", PTR_IN_REGISTER, REGISTER,        3 }, { "sub", "w", PTR_IN_NUMBER, REGISTER,        4 },  { "push", "w", REGISTER,        NOARG, 2 }, { "pop", "w", REGISTER,        NOARG, 2 }, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},
		{ "mov", "w", REGISTER, PTR_IN_NUMBER,   4 }, { "mov", "w", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "mov", "w", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 }, /**/ { "add", "w", REGISTER, PTR_IN_NUMBER,   4 }, { "add", "w", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "add", "w", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 }, /**/ { "sub", "w", REGISTER, PTR_IN_NUMBER,   4 }, { "sub", "w", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "sub", "w", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 },  { "push", "w", PTR_IN_NUMBER,   NOARG, 3 }, { "pop", "w", PTR_IN_NUMBER,   NOARG, 3 }, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},
		{ "mov", "w", REGISTER, PTR_IN_REGISTER, 3 }, { "mov", "w", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "mov", "w", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 }, /**/ { "add", "w", REGISTER, PTR_IN_REGISTER, 3 }, { "add", "w", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "add", "w", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 }, /**/ { "sub", "w", REGISTER, PTR_IN_REGISTER, 3 }, { "sub", "w", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "sub", "w", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 },  { "push", "w", PTR_IN_REGISTER, NOARG, 2 }, { "pop", "w", PTR_IN_REGISTER, NOARG, 2 }, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},
																																																																																																																												              
		{ "cmp", "b", REGISTER, NUMBER,          3 }, { "cmp", "b", PTR_IN_REGISTER, NUMBER,          3 }, { "cmp", "b", PTR_IN_NUMBER, NUMBER,          4 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "call", "", NUMBER,          NOARG, 3 },   { "err", "", NOARG, NOARG, 1},             { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1},
		{ "cmp", "b", REGISTER, REGISTER,        3 }, { "cmp", "b", PTR_IN_REGISTER, REGISTER,        3 }, { "cmp", "b", PTR_IN_NUMBER, REGISTER,        4 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "call", "", REGISTER,        NOARG, 2 },   { "err", "", NOARG, NOARG, 1},             { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "ret", "", NOARG, NOARG, 1},
		{ "cmp", "b", REGISTER, PTR_IN_NUMBER,   4 }, { "cmp", "b", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "cmp", "b", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "call", "", PTR_IN_NUMBER,   NOARG, 3 },   { "err", "", NOARG, NOARG, 1},             { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "hlt", "", NOARG, NOARG, 1},
		{ "cmp", "b", REGISTER, PTR_IN_REGISTER, 3 }, { "cmp", "b", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "cmp", "b", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "call", "", PTR_IN_REGISTER, NOARG, 2 },   { "err", "", NOARG, NOARG, 1},             { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "err", "", NOARG, NOARG, 1}, { "syscall", "", NOARG, NOARG, 1},
																																							       								                 								                      								                          								                							                         							                       											     
		{ "cmp", "w", REGISTER, NUMBER,          4 }, { "cmp", "w", PTR_IN_REGISTER, NUMBER,          4 }, { "cmp", "w", PTR_IN_NUMBER, NUMBER,          5 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "jmp", "", NUMBER,          NOARG, 3 },    { "je", "", NUMBER,          NOARG, 3 },   { "jne", "", NUMBER,          NOARG, 3 }, { "jl", "", NUMBER,          NOARG, 3 }, { "jg", "", NUMBER,          NOARG, 3 }, { "jle", "", NUMBER,          NOARG, 3 }, { "jge", "", NUMBER,          NOARG, 3 },
		{ "cmp", "w", REGISTER, REGISTER,        3 }, { "cmp", "w", PTR_IN_REGISTER, REGISTER,        3 }, { "cmp", "w", PTR_IN_NUMBER, REGISTER,        4 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "jmp", "", REGISTER,        NOARG, 2 },    { "je", "", REGISTER,        NOARG, 2 },   { "jne", "", REGISTER,        NOARG, 2 }, { "jl", "", REGISTER,        NOARG, 2 }, { "jg", "", REGISTER,        NOARG, 2 }, { "jle", "", REGISTER,        NOARG, 2 }, { "jge", "", REGISTER,        NOARG, 2 },
		{ "cmp", "w", REGISTER, PTR_IN_NUMBER,   4 }, { "cmp", "w", PTR_IN_REGISTER, PTR_IN_NUMBER,   4 }, { "cmp", "w", PTR_IN_NUMBER, PTR_IN_NUMBER,   5 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "jmp", "", PTR_IN_NUMBER,   NOARG, 3 },    { "je", "", PTR_IN_NUMBER,   NOARG, 3 },   { "jne", "", PTR_IN_NUMBER,   NOARG, 3 }, { "jl", "", PTR_IN_NUMBER,   NOARG, 3 }, { "jg", "", PTR_IN_NUMBER,   NOARG, 3 }, { "jle", "", PTR_IN_NUMBER,   NOARG, 3 }, { "jge", "", PTR_IN_NUMBER,   NOARG, 3 },
		{ "cmp", "w", REGISTER, PTR_IN_REGISTER, 3 }, { "cmp", "w", PTR_IN_REGISTER, PTR_IN_REGISTER, 3 }, { "cmp", "w", PTR_IN_NUMBER, PTR_IN_REGISTER, 4 },      { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                          { "err", "", NOARG, NOARG, 1},                { "err", "", NOARG, NOARG, 1},                       { "err", "", NOARG, NOARG, 1},                     { "jmp", "", PTR_IN_REGISTER, NOARG, 2 },    { "je", "", PTR_IN_REGISTER, NOARG, 2 },   { "jne", "", PTR_IN_REGISTER, NOARG, 2 }, { "jl", "", PTR_IN_REGISTER, NOARG, 2 }, { "jg", "", PTR_IN_REGISTER, NOARG, 2 }, { "jle", "", PTR_IN_REGISTER, NOARG, 2 }, { "jge", "", PTR_IN_REGISTER, NOARG, 2 },
	};
	header = std::vector<uint8_t>(16);
	//header = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
}


Lexer::~Lexer()
{
}

Lexer::Lexer(bool debug) : Lexer()
{
	this->debug = debug;
}

std::vector<uint8_t> Lexer::analise(std::vector<Lexeme> operations)
{
	std::vector<uint8_t> res;
	program = operations;
	analise_sizes(); // считаем размер будущей программы
	analise_named_pointers(); // подставляем вместо именованых указателей их адреса
	compile(); // компилируем

	for (auto inst : program)
	{
		res = concat_vectors(res, inst.bin); // записываем программу в массив
	}

	res = concat_vectors(header, res);

	return res; // возращаем скомпилироавною программу
}

void Lexer::analise_sizes()
{
	for (int i = 0; i < program.size(); i++)
	{
		if (program[i].type == CPU_INSTRUCTION)
		{
			for (int j = 0; j < instruction_table.size(); j++)
			{
				if (program[i].cmd == instruction_table[j].name && program[i].arg0_type == instruction_table[j].arg0_type && program[i].arg1_type == instruction_table[j].arg1_type && (program[i].size_identifier == instruction_table[j].size_identifier || instruction_table[j].size_identifier == ""))
				{
					program[i].size = instruction_table[j].size;
				
					break;
				}

			}
			if (program[i].size == 0)
			{
				char buf[70];
				sprintf_s(buf, "Line %d can't understand \"%s\", check arguments and data type", program[i].line, program[i].full_command.c_str());
				throw (std::string)buf;
			}
		}
		else if (program[i].type == PREPROCESSOR_INSTRUCTION)
		{
			program[i].size = program[i].bin.size();
		}
	}
}

void Lexer::analise_named_pointers()
{
	if (debug)
		printf("\n\nAnalised instructions\n");
	std::vector<NamedPtr> definitions;
	for (int i = 0; i < program.size(); i++)
	{
		if (program[i].type == CPU_INSTRUCTION)
			continue;
		else if (program[i].type == POINT_DEFINITION || program[i].type == PREPROCESSOR_INSTRUCTION)
		{
			definitions.push_back(NamedPtr(program[i].named_ptr, get_instruction_addres(i)));
			if(debug)
				printf("Named ptr (%.4X, \"%s\")\n", get_instruction_addres(i), program[i].named_ptr.c_str());
		}
	}
	
	for (int i = 0; i < program.size(); i++)
	{
		if (program[i].uses_POINT)
		{
			for (auto p : definitions)
			{
 				if (utilities::delete_brackets(program[i].arg0) == p.name)
				{
					program[i].arg0 = std::to_string(p.address);
					program[i].uses_POINT = false;
				}
				if (delete_brackets(program[i].arg1) == p.name)
				{
					program[i].arg1 = std::to_string(p.address);
					program[i].uses_POINT = false;
				}
			}

			//if (debug)
			//	printf("%d : %s %s %s %s\n", program[i].line, program[i].cmd.c_str(), program[i].size_identifier.c_str(), program[i].arg0.c_str(), program[i].arg1.c_str());

			if ((program[i].uses_POINT))
			{
				char buf[70];
				sprintf_s(buf, "Line %d unknown pointer \"%s\"", program[i].line, program[i].arg1.c_str());
				throw (std::string)buf;
			}
		}
	}
}

void Lexer::compile()
{
	if (debug)
		printf("\n\nCompiled binary\n");
	for (int i = 0; i < program.size(); i++)
	{
		if (program[i].type == CPU_INSTRUCTION)
		{

			for (int j = 0; j < instruction_table.size(); j++)
			{
				if (program[i].cmd != instruction_table[j].name)
					continue;
				else if (program[i].cmd == instruction_table[j].name && program[i].arg0_type == instruction_table[j].arg0_type && program[i].arg1_type == instruction_table[j].arg1_type && (program[i].size_identifier == instruction_table[j].size_identifier || instruction_table[j].size_identifier == ""))
				{
					program[i].bin.push_back(j);

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

					if (debug)
					{
						printf("%-2d : { ", program[i].line);
						for (auto num : program[i].bin)
						{
							printf("0x%.2X, ", num);
						}
						printf("\b\b }\n");
					}
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
		else if (program[i].type == PREPROCESSOR_INSTRUCTION)
		{
	
		}
		else if (program[i].type == META_DATA)
		{
			if (program[i].cmd == "entry")
			{
				try
				{
					std::vector<uint8_t> addr = compile_number(program[i].arg0, 2);
					header[0] = addr[0];
					header[1] = addr[1];
				}
				catch (std::string e)
				{
					char buf[70];
					sprintf_s(buf, "Line %d %s", program[i].line, e.c_str());
					throw (std::string)buf;
				}
				
			}
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


