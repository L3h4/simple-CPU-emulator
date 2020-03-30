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


private:
	bool debug;
};


