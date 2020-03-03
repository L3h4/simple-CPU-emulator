#include<iostream>
#include<stdio.h>
#include<vector>

#include"Parser.h"
#include"Lexer.h"
using namespace std;

#define pause() system("pause")

/*
	Простой компилятор для процессора Ox64cm
	кароче программа чтобы делать программы xD
	
	ASMC.exe file.asm -> file.bin
*/
struct 
{
	bool print_debug = false;
	string file_name;
} config;



// Простой парсер аргументов возвращает разрешение на начало парсинга кода (если мы запустим его с ключем help то компилировать ничего не нужно) 
bool parse_cmd_args(int argc, char *argv[]) 
{
	if (argc == 1)
		return false;

	for (int i = 1; i < argc; i++)
	{
		if ((string)argv[i] == "-h" || (string)argv[i] == "--help")
		{
			printf("USAGE: \"ASMC.EXE [options] source.asm\"\n\n");
			printf("\t%-2s %-7s  -  %s", "-h", "--help", "Shows this message\n");
			printf("\t%-2s %-7s  -  %s", "-d", "--debug", "Shows debug messages while compileing\n");
			return false;
		}
		else if ((string)argv[i] == "-d" || (string)argv[i] == "--debug")
		{
			config.print_debug = true;
		}
		else if (i == argc - 1)  // последним всегда идет имя файла
		{
			config.file_name = argv[argc - 1];
			return true;
		}
		else 
		{
			printf("Unknown argument %s use \"%s --help\" to get help\n", argv[i], argv[0]);
			return false;
		}
	}
	return true;
}


int main(int argc, char *argv[]) {
	
	if (parse_cmd_args(argc, argv)) 
	{
		printf("Compiling %s\n", config.file_name.c_str());

		Parser p(config.print_debug);
		Lexer l;
		vector<Lexeme> tokens;
		vector<uint8_t> program;
		try 
		{
			tokens = p.parse_from_file(config.file_name);
		}
		catch (string err_msg) 
		{
			printf("\nSYNTAX ERROR:\n\t%s\n\n", err_msg.c_str());
			pause();
			return 1;
		}
		try
		{
			program = l.analise(tokens);
		}
		catch (string err_msg)
		{
			printf("\nLEXICAL ERROR:\n\t%s\n\n", err_msg.c_str());
			pause();
			return 1;
		}
	}
	pause();
	return 0;
}