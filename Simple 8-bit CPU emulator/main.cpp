#include<iostream>
#include<stdio.h>
#include<string>
#include<windows.h>


// раскомментируйте следующую строку, чтобы видеть дебаг комментарии
#define PRINT_DEBUG

#include"Bus.h"
#include"Ox64cmCPU.h"
#include"Status.h"

using namespace std;


/*
	Документация https://www.evernote.com/l/AfpYiDoi7_hKJJHEmHGxAVzqdoACyR6W718/
	Дело было вечером, делать было нечего. Короче я наваял емулятор простого 8/16 битного процессора)
	
*/



#define u8 uint8_t
#define u16 uint16_t



Status status;
Bus bus;
Ox64cmCPU cpu;

// скопировать прграму в память процессора по адресу
void load_program(u16 address, u8 program[]) {
	u16 memory_adr = address;
	for (; memory_adr < sizeof(program) / sizeof(u8); memory_adr++) {
		bus.write(memory_adr, program[memory_adr]);
	}
	printf("Your program located at 0x%.4X - 0x%.4X\n", address, memory_adr);
	//::memcpy(&bus.RAM.memory, &program, sizeof(program)); // скопировать прграму в память процессора
}

void initialize_memory() {

	// компилятора пока что нет поєтому прграму пишем сюда (
	u8 hello_world_program[] = {
		0x0,
		0x10,0xA,0x3F, // MOV A, 0x3F
		0x50,0xBB,0x12,0x34 // MOV BX, 0x1234
	};

	// Hello world с циклом
	u8 hello_world_v2_program[] = {
		0x10, 0x11,     // JMP 0x12
		0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0xA, 0x0, // Hello, world\n\eol
		0x1, 0xA, 0x1,  // MOV AX, 1

		0x1, 0xD, 0x2,  // MOV DX, 0x2
		0x6, 0xB, 0xD,  // MOV BX, [DX]
		0xF, 0xB, 0x0,  // CMP BX, 0x0
		0x11, 0x24,		// JE 0x24
		0x18,		    // SYSCALL
		0xC, 0xD,       // INC DX
		0x10, 0x17,     // JMP 0x17

		0x1, 0xA, 0x2,	// MOV AX, 2
		0x18,			// SYSCALL
		0x17            // HLT
	};
	load_program(0, hello_world_program);
}


void initialize_console_window() {
	// неведомая херня со стаковерфлоу чтобы настроить размер окна
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1100, 600, true);
}


int main() {
	status = Status();
	bus = Bus();
	cpu = Ox64cmCPU(&bus, &status);

	
	string command;


	initialize_console_window();
	initialize_memory();
	
	printf("Press enter to make step or type .help to get help\n");
	while (true)
	{
		if (!status.execute_til_hlt) {
			// Неболюшое меню
			printf("# ");
			getline(cin, command);
			if (command == ".help")
			{
				// help сообщение
				printf("Help message\n");
				printf("%-10s - %s\n", ".execute", "Execute program til HLT command. Warning if HLT wouldn't be found it can cause errors & executing non executable sections");
				printf("%-10s - %s\n", ".registers", "Show what is in registers");
				printf("%-10s - %s\n", ".memory", "Show what is in memory");
				printf("%-10s - %s\n", ".reset", "Write program to memory");
				printf("%-10s - %s\n", ".disassemble", "Print disassembly");
				printf("%-10s - %s\n", ".exit", "Exit CPU emulator program"); 
				continue;
			}
			else if (command == ".execute" || command == ".exec")
			{
				status.execute_til_hlt = true;
			}
			else if (command == ".registers" || command == ".regs")
			{
				cpu.regs.print();
				continue;
			}
			else if (command == ".memory" || command == ".mem")
			{
				bus.RAM.print();
				continue;
			}
			else if (command == ".reset")
			{
				initialize_memory();
				cpu.reset();
				continue;
			}
			else if (command == ".disassemble" || command == ".dasm")
			{
				cpu.print_disassembly(0, 20);
				continue;
			}
			else if (command == "") {}
			else if (command == ".exit")
			{
				return 0;
			}
			else
			{
				printf("Error command %s not found\n", command.c_str());
				continue;
			}
		}
		
		cpu.step();
	}
	system("pause");
	return 0;
}