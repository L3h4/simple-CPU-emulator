#include<iostream>
#include<stdio.h>
#include <string>
#include<windows.h>

#include"InstructionSet.h"
#include"Memory.cpp"

using namespace std;


// Документация https://www.evernote.com/l/AfpYiDoi7_hKJJHEmHGxAVzqdoACyR6W718/




// разкоментируйте следующую строку, чтобы видеть дебаг комментарии
// #define PRINT_DEBUG

#define u8 uint8_t
#define u16 uint16_t

/*
	Документация https://www.evernote.com/l/AfpYiDoi7_hKJJHEmHGxAVzqdoACyR6W718/
	Дело быловечером, делать было нечего. Короче я наваял емулятор простого 8 битного процессора)
	точка входа на 695-й строке,
	программу писать где-то в районе 616-й строки
*/



// некоторые переменные
bool execute_til_HLT = false;


/*
void decode_execute_instruction(u8 opcode) {
	u8 *dest = nullptr;
	u8 *source = nullptr;
	u8 *addres = nullptr;
	u8 incrementor = 1;
	// Добро пожаловать в самую гущу говнокода )) Не пытайтесь понять)
	switch (opcode)
	{
	case 0x0: // NOP
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("NOP instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG
		break;

	case 0x1: // MOV R, d8
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента	
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALUold.parse_value(); // парсинг 2-го аргумента

		ALUold.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x2: // MOV R, R
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = bin_parser.parse_register(); // парсинг 2-го аргумента

		ALUold.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x3: // MOV R, [a8]
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register();// парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALUold.parse_pointer(); // парсинг 2-го аргумента

		ALUold.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x4: // MOV [a8], R
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALUold.parse_pointer(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = bin_parser.parse_register(); // парсинг 2-го аргумента

		ALUold.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x5: // MOV [a8], d8
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALUold.parse_pointer(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALUold.parse_value(); // парсинг 2-го аргумента

		ALUold.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x6: // MOV R, [R]
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALUold.parse_ptr_in_register(); // парсинг 2-го аргумента

		ALUold.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x7: // MOV [R], R
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALUold.parse_ptr_in_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = bin_parser.parse_register(); // парсинг 2-го аргумента

		ALUold.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x8: // ADD R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("ADD instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = bin_parser.parse_register(); // парсинг 2-го аргумента

		ALU.ADD(dest, source);
		Regs.PC++;
		break;
	case 0x9: // ADD R, d8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("ADD instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALUold.parse_value(); // парсинг 2-го аргумента

		ALU.ADD(dest, source);
		Regs.PC++;
		break;

	case 0xA: // SUB R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("SUB instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = bin_parser.parse_register(); // парсинг 2-го аргумента

		ALU.SUB(dest, source);
		Regs.PC++;
		break;

	case 0xB: // SUB R, d8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("SUB instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALUold.parse_value(); // парсинг 2-го аргумента

		ALU.SUB(dest, source);
		Regs.PC++;
		break;

	case 0xC: // INC R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("INC instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		source = &incrementor;
		Regs.PC++;
		ALU.ADD(dest, source);
		break;

	case 0xD: // DEC R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("DEC instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента

		source = &incrementor;
		Regs.PC++;
		ALU.SUB(dest, source);
		break;

	case 0xE: // CMP R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("CMP instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = bin_parser.parse_register(); // парсинг 2-го аргумента

		ALU.CMP(dest, source);
		Regs.PC++;
		break;
	case 0xF: // CMP R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("CMP instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = bin_parser.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALUold.parse_value(); // парсинг 2-го аргумента

		ALU.CMP(dest, source);
		Regs.PC++;
		break;
	case 0x10: // JMP a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JMP instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALUold.parse_value(); // парсинг 1-го аргумента

		ALUold.JMP(*addres);
		break;

	case 0x11: // JE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALUold.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALUold.JE(*addres);
		break;

	case 0x12: // JNE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JNE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALUold.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALUold.JNE(*addres);
		break;

	case 0x13: // JL a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JL instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALUold.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALUold.JL(*addres);
		break;

	case 0x14: // JG a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JG instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALUold.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALUold.JG(*addres);
		break;

	case 0x15: // JLE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JLE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALUold.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALUold.JLE(*addres);
		break;

	case 0x16: // JGE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JGE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALUold.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALUold.JGE(*addres);
		break;

	case 0x17: // HLT
#ifdef PRINT_DEBUG
		printf("HLT instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		printf("Program finished!\n");
		execute_til_HLT = false;
		break;
	case 0x18: // SYSCALL
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("SYSCALL instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		ALUold.SYSCALL();
		break;

	default:
		printf("ERROR instruction [0x%.2X] at 0x%.2X not found\n", opcode, Regs.PC);
		Regs.PC++;
		break;
	}
}
*/

u8 fetch_instruction() {
	return *RAM.read(Regs.PC);
}

void initialize_memory() {

	// компилятора пока что нет поєтому прграму пишем сюда (

	// Hello world без цыкла
	u8 hello_world_program[] = {
		0x10, 0x11,     // JMP 0x11
		0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0xA, 0x0, // Hello, world\n\eol
		0x1, 0xA, 0x1,  // MOV AX, 1

		0x3, 0xB, 0x2,  // MOV BX, 0x2
		0x18,			// SYSCALL
		0x3, 0xB, 0x3,  // MOV BX, 0x3
		0x18,			// SYSCALL
		0x3, 0xB, 0x4,  // MOV BX, 0x4
		0x18,			// SYSCALL
		0x3, 0xB, 0x5,  // MOV BX, 0x5
		0x18,			// SYSCALL
		0x3, 0xB, 0x6,  // MOV BX, 0x6
		0x18,			// SYSCALL
		0x3, 0xB, 0x7,  // MOV BX, 0x7
		0x18,			// SYSCALL
		0x3, 0xB, 0x8,  // MOV BX, 0x8
		0x18,			// SYSCALL
		0x3, 0xB, 0x9,  // MOV BX, 0x9
		0x18,			// SYSCALL
		0x3, 0xB, 0xA,  // MOV BX, 0xA
		0x18,			// SYSCALL
		0x3, 0xB, 0xB,  // MOV BX, 0xB
		0x18,			// SYSCALL
		0x3, 0xB, 0xC,  // MOV BX, 0xC
		0x18,			// SYSCALL
		0x3, 0xB, 0xD,  // MOV BX, 0xD
		0x18,			// SYSCALL
		0x3, 0xB, 0xE,  // MOV BX, 0xE
		0x18,			// SYSCALL
		0x3, 0xB, 0xF,  // MOV BX, 0xF
		0x18,			// SYSCALL
		0x3, 0xB, 0x10, // MOV BX, 0x10
		0x18,			// SYSCALL

		0x1, 0xA, 0x2, // MOV AX, 2
		0x18,			// SYSCALL
		0x17            // HLT
	};

	// Hello world с цыклом
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


	// подставте сюда название пограммы которую хотите запустить
#define program	hello_world_v2_program

	::memcpy(&RAM.memory, &program, sizeof(program)); // скопировать прграму в память процессора
}

void initialize_console_window() {
	// неведомая херня со стаковерфлоу чтобы настроить размер окна
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1100, 600, TRUE);
}

int main() {
	string command;
	initialize_console_window();
	initialize_memory();
	RAM.print();
	printf("Press enter to make step or type .help to get help\n");
	while (true)
	{
		if (!execute_til_HLT) {
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
				printf("%-10s - %s\n", ".exit", "Exit CPU emulator program");
				continue;
			}
			else if (command == ".execute" || command == ".exec")
			{
				execute_til_HLT = true;
			}
			else if (command == ".registers" || command == ".regs")
			{
				Regs.print();
				continue;
			}
			else if (command == ".memory" || command == ".mem")
			{
				RAM.print();
				continue;
			}
			else if (command == ".reset")
			{
				initialize_memory();
				Regs.AX.value = 0x0;
				Regs.BX.value = 0x0;
				Regs.CX.value = 0x0;
				Regs.DX.value = 0x0;
				Regs.PC = 0x0;
				Regs.SP = 0x0;
				Regs.STATUS.value = 0;
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

		u8 inst = fetch_instruction();
		//decode_execute_instruction(inst);

	}
	system("pause");
	return 0;
}