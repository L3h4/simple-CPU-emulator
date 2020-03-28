#pragma once
#include<iostream>
#include<vector>

// ���� ����������
enum type {
	CPU_INSTRUCTION,
	META_DATA,
	POINT_DEFINITION,
	NONE
};
enum arg_type {
	REGISTER,
	//REGISTER16,
	NUMBER,

	PTR_IN_REGISTER,
	//PTR_IN_REGISTER16,
	PTR_IN_NUMBER,
	NOARG
};

// ��������a ��������, ����� ��� �������������� � �������������� �������
struct Lexeme
{
	std::string full_command; // ������ ������ � �������� � �����������
	std::string cmd; // ������ �������
	std::string size_identifier; // ������ � ������� �������� word ��� byte
	std::string arg0; // �������� 1
	std::string arg1; // �������� 2
	arg_type arg0_type = NOARG;
	arg_type arg1_type = NOARG;
	std::string named_ptr; // ���� ���������� �������� ������� �������� start:
	type type; // ������ ������� �������� �������� �� ��� ���������� ��� ����� ������
	int line; // ����� ������ �� ������� ��������� ���������� (����� ��� ������ ������)
	int size = 0;
	std::vector<uint8_t> bin;
	bool uses_POINT;
};


const std::vector<std::string> possible_cmds = { "mov", "nop", "jmp" };
const std::vector<std::string> possible_size_identifiers = { "byte", "b", "word", "w" };
const std::vector<std::string> possible_registers = { "a", "b", "c", "d", "ax", "bx", "cx", "dx", "pc", "sp" };
const std::vector<std::string> possible_registers16 = { "ax", "bx", "cx", "dx", "pc", "sp" };
const std::vector<std::string> possible_registers8 = { "a", "b", "c", "d" };