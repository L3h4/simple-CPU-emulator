#pragma once
#include<vector>
#include<stdio.h>
#include<iostream>
#include<sstream>
#include<cctype>
#include<algorithm>
#include<string>
#include<fstream>


#include "../Utilities/CompilingUtilities.h"
#include"../Operation/Operation.h"

// класс парсер отвечает за парсинг исходног файла на лексемы
class Parser
{
public:
	Parser();
	~Parser();
	Parser(bool dbg);

public:
	std::vector<Lexeme> parse_from_file(std::string file_name);


private:
	Lexeme parse_line(std::string line, int line_N);


private:
	bool debug;
};


