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

// ��������a ��������, ����� ��� �������������� � �������������� �������
struct Lexeme
{
	std::string full_command; // ������ ������ � �������� � �����������
	std::string cmd; // ������ �������
	std::string size_identifier; // ������ � ������� �������� word ��� byte
	std::string arg0; // �������� 1
	std::string arg1; // �������� 2
	std::string named_ptr; // ���� ���������� �������� ������� �������� start:
	type type; // ������ ������� �������� �������� �� ��� ���������� ��� ����� ������ 
	int line; // ����� ������ �� ������� ��������� ���������� (����� ��� ������ ������)
};


const std::vector<std::string> possible_cmds = { "mov", "nop", "jmp" };
const std::vector<std::string> possible_size_identifiers = { "byte", "b", "word", "w" };
const std::vector<std::string> possible_registers = { "a", "b", "c", "d", "ax", "bx", "cx", "dx", "pc", "sp" };
const std::vector<std::string> possible_registers16 = { "ax", "bx", "cx", "dx", "pc", "sp" };
const std::vector<std::string> possible_registers8 = { "a", "b", "c", "d" };