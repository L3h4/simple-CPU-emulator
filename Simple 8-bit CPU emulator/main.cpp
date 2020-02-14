#include<iostream>
#include<stdio.h>
#include<string>
#include<windows.h>

using namespace std;

#include"Bus.h"
#include"Ox64cmCPU.h"
#include"Status.hpp"


/*
	������������ https://www.evernote.com/l/AfpYiDoi7_hKJJHEmHGxAVzqdoACyR6W718/
	���� ���� �������, ������ ���� ������. ������ � ������ �������� �������� 8/16 ������� ����������)
	
*/

// ������� ���������� ��� ����� ������ ��� 1 � 2 �������� ����������
#define u8 uint8_t 
#define u16 uint16_t

// ������ ���������� ����������
// ������ �������� �� ��������� ���������� ���������� � �������� ������� ������
Status status;
// ���� ������ � ������, �� ��� ����� ��� ���������� (���� ��� ������ ���)
Bus bus;
// ���������
Ox64cmCPU cpu;

// ����������� ������� � ��� �� ������
void load_program(u16 address, u8 program[], u16 size) {
	u16 relative_address = address;
	for (; relative_address - address < size; relative_address++) {
		bus.write(relative_address, program[relative_address - address]);
	}
	printf("Your program located at 0x%.4X - 0x%.4X\n", address, relative_address);
}

// ��������� �������� ���������� ������
void initialize_memory() 
{

	// ����������� ���� ��� ��� ������ ������� ����� ���� (
	// ���� ��� �������� ������ �������� MOV
	// ������� ��������� ��� �����
	u8 MOV_inst_test_program[] = {
		0x10,0xA,0x3F,		  // MOV A, 0x3F
		0x50,0xBB,0x02,0x34,  // MOV BX, 0x0234
		0x11,0x0B,0xEF,       //MOV [B], 0xEF
		0x72,0x02,0x35,0x0,0x1//MOV [0x0235], [0x0001]
	};
	
	// ��������� ��������� � ������
	load_program(0, MOV_inst_test_program, sizeof(MOV_inst_test_program));
}


void initialize_console_window() {
	// ��������� ����� �� ������������ ����� ��������� ������ ����
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1100, 600, true);
}


int main() {
	// ������������� ����������
	// ��� ��������� ��������� ���� �� �����
	status = Status(); 
	bus = Bus(&status);
	cpu = Ox64cmCPU(&bus, &status);
	bus.connect_cpu(&cpu);
	// ���������� ��� �������� ������� �����
	string command;
	

	initialize_console_window(); // ��������� �������� ����
	initialize_memory(); // ������ ������� �������� � ������
	printf("Press enter to make step or type .help to get help\n");

	while (true) // ������� ���� ���������
	{
		if (!status.execute_til_hlt) // ��������� �������� ��������� ������� ������� �� ���� �������� ������������ � ����� ������ ���(���� ��������� ������� � ������ ���������� �� ������� HALT, ������������ �� ����������, � ����� ������ ���)
		{
			// ��������� ����
			printf("# ");
			getline(cin, command);
			if (command == ".help")
			{
				// help ���������
				printf("Help message\n");
				printf("%-12s - %s\n", ".execute", "Execute program til HLT command. Warning if HLT wouldn't be found it can cause errors");
				printf("%-12s - %s\n", ".registers", "Show what is in registers");
				printf("%-12s - %s\n", ".memory", "Show what is in memory");
				printf("%-12s - %s\n", ".reset", "Write program to memory");
				printf("%-12s - %s\n", ".disassemble", "Print disassembly");
				printf("%-12s - %s\n", ".exit", "Exit CPU emulator program"); 
				continue;
			}
			else if (command == ".execute" || command == ".exec")
			{
				// ��� ����� ���� ������� ��������� ������ �������� � ������ ���������� �� ������� HALT
				if (!status.erorr) // �������������� ���� ������ ���, �� ��������
					status.execute_til_hlt = true;
			}
			else if (command == ".registers" || command == ".regs")
			{
				// ��� ����� ���� ������� � ������� ��������� ���������� ��������� � ������
				cpu.print_regs();
				continue;
			}
			else if (command == ".memory" || command == ".mem")
			{
				// ��� ����� ���� ������� � ������� ��������� ���������� ���� 2 �� ���
				bus.RAM.print();
				continue;
			}
			else if (command == ".reset")
			{
				// ��� ����� ���� ������� ���������� ����������
				initialize_memory();
				cpu.reset();
				status.erorr = false;
				status.execute_til_hlt = false;
				continue;
			}
			else if (command == ".disassemble" || command == ".dasm")
			{
				// ��� ����� ���� ������� � ������� ���������  ������������������ ������ 21 ���� ������
				cpu.print_disassembly(0, 20);
				continue;
			}
			else if (command == "") 
			{
				// ��� ����� ���� ������� ������ ������������ ��� ����������
			}
			else if (command == ".exit")
			{
				// ��� ����� ���� ������� ����� �� ���������
				return 0;
			}
			else
			{
				// ���� ������� �� ������� �� ������� ������
				printf("Error command %s not found\n", command.c_str());
				continue;
			}
		}
		if (!status.erorr)
			cpu.step(); // ��������� �������� ���� ������ ���
		else
			printf("Can't make step, CPU freezed\n"); // ����� ������ �� ������
	}
	system("pause");
	return 0;
}