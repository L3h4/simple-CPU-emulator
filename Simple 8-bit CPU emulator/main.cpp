#include<iostream>
#include<stdio.h>
#include <string>
#include<windows.h>
// Документация https://www.evernote.com/l/AfpYiDoi7_hKJJHEmHGxAVzqdoACyR6W718/


using namespace std;

// разкоментируйте следующую строку, чтобы видеть дебаг комментарии
// #define PRINT_DEBUG

#define u8 uint8_t

/*
	Документация https://www.evernote.com/l/AfpYiDoi7_hKJJHEmHGxAVzqdoACyR6W718/
	Дело быловечером, делать было нечего. Короче я наваял емулятор простого 8 битного процессора)
	точка входа на 695-й строке,
	программу писать где-то в районе 616-й строки
*/

u8 memory[256]; // "оперативная память"
void mem_write(u8 addres, u8 value) {
	memory[addres] = value;
}
u8 mem_read(u8 addres) {
	return memory[addres];
}
void mem_print() {
	printf("MEMORY");
	for (short int i = 0; i < sizeof(memory); i++) {
		if (i % 16 == 0) {
			printf("\n");
			printf("  0x%.2X  |  ", i);
		}
		printf(" %.2X ", memory[i]);
	}
	printf("\n==========================================================================\n\n");
}


// некоторые переменные
bool execute_til_HLT = false;
string stdout_buffer;

// Регистры
struct
{
	// Регистры общего назначения
	u8 AX;
	u8 BX;
	u8 CX;
	u8 DX;

	u8 PC; // Счетчик программы
	u8 SP; // Указатель стэка

	struct {
		bool Z; // Флаг ноля
		bool C; // Флаг переноса
		bool S; // Флаг знака (0 : + | 1 : -)
	} STATUS;

	void print() {
		// Вывод значений регистров в консоль
		printf("==========\n");
		printf("REGISTERS\n");
		printf("AX = 0x%.2X\n", Regs.AX);
		printf("BX = 0x%.2X\n", Regs.BX);
		printf("CX = 0x%.2X\n", Regs.CX);
		printf("DX = 0x%.2X\n", Regs.DX);
		printf("=========\n");
		printf("PC = 0x%.2X\n", Regs.PC);
		printf("SP = 0x%.2X\n", Regs.SP);
		printf("FLAGS\n");
		printf("S C Z\n");
		printf("%d %d %d\n", Regs.STATUS.S, Regs.STATUS.C, Regs.STATUS.Z);
		printf("==========\n");
	}
} Regs;


struct
{
	void MOV(u8 *dest, u8 *source)
	{
		// просто копирую значение из source в dest
		::memcpy(dest, source, sizeof(u8));
	}

	void ADD(u8 *oprand1, u8 *operand2)
	{
		// обнуляю флаги
		Regs.STATUS.C = false;
		Regs.STATUS.S = false;
		Regs.STATUS.Z = false;
		// Выставляю флаги
		if (short int(*oprand1) + short int(*operand2) > 255)
		{
			Regs.STATUS.C = true;
		}
		if (u8(*oprand1 + *operand2) == 0)
		{
			Regs.STATUS.Z = true;
		}
		// провожу операцию
		*oprand1 += *operand2;
	}

	void SUB(u8 *oprand1, u8 *operand2)
	{
		// обнуляю флаги
		Regs.STATUS.C = false;
		Regs.STATUS.Z = false;

		// Выставляю флаги
		if (short int(*oprand1) - *operand2 < 0)
		{
			Regs.STATUS.S = true;
		}
		if (*oprand1 - *operand2 == 0)
		{
			Regs.STATUS.Z = true;
		}
		// провожу операцию
		*oprand1 -= *operand2;
	}

	void CMP(u8 *oprand1, u8 *operand2)
	{
		// обнуляю флаги
		Regs.STATUS.C = false;
		Regs.STATUS.S = false;
		Regs.STATUS.Z = false;

		// Выставляю флаги
		if (short int(*oprand1) - *operand2 < 0)
		{
			Regs.STATUS.S = true;
		}
		if (u8(*oprand1 - *operand2) == 0)
		{
			Regs.STATUS.Z = true;
		}

	}

	void JMP(u8 addres)
	{
		Regs.PC = addres;
	}

	void JE(u8 addres)
	{
		//  безусловный переход
		if (Regs.STATUS.Z) {
			JMP(addres);
		}
	}

	void JNE(u8 addres)
	{
		if (!Regs.STATUS.Z) {
			JMP(addres);
		}
	}

	void JL(u8 addres)
	{
		if (Regs.STATUS.S) {
			JMP(addres);
		}
	}

	void JG(u8 addres)
	{
		if (!Regs.STATUS.S) {
			JMP(addres);
		}
	}

	void JLE(u8 addres)
	{
		if (Regs.STATUS.S || Regs.STATUS.Z) {
			JMP(addres);
		}
	}

	void JGE(u8 addres)
	{
		if (!Regs.STATUS.S || Regs.STATUS.Z) {
			JMP(addres);
		}
	}

	void SYSCALL()
	{

		if (Regs.AX == 1)
		{
			stdout_buffer += char(Regs.BX);
		}
		else if (Regs.AX == 2)
		{
			printf("==============EMULATOR says:===================\n");
			printf("%s", stdout_buffer.c_str());
			printf("===============================================\n");
			stdout_buffer = "";
		}
	}

	// ==================
	u8* parse_register()
	{
		// парсинг регистра
		u8 *res = nullptr;
		switch (memory[Regs.PC])
		{
		case 0xA:
			res = &Regs.AX;
			break;
		case 0xB:
			res = &Regs.BX;
			break;
		case 0xC:
			res = &Regs.CX;
			break;
		case 0xD:
			res = &Regs.DX;
			break;
		case 0xE:
			res = &Regs.PC;
			break;
		case 0xF:
			res = &Regs.SP;
			break;
		default:
			throw out_of_range("Can't parse register, " + to_string(memory[Regs.PC]));
			break;
		}
		return res;
	}

	u8* parse_ptr_in_register()
	{
		// парсинг регистра 
		u8 *res = nullptr;
		switch (memory[Regs.PC])
		{
		case 0xA:
			res = &memory[Regs.AX];
			break;
		case 0xB:
			res = &memory[Regs.BX];
			break;
		case 0xC:
			res = &memory[Regs.CX];
			break;
		case 0xD:
			res = &memory[Regs.DX];
			break;
		case 0xE:
			res = &memory[Regs.PC];
			break;
		case 0xF:
			res = &memory[Regs.SP];
			break;
		default:
			throw out_of_range("Can't parse register, " + to_string(memory[Regs.PC]));
			break;
		}
		return res;
	}

	u8* parse_value()
	{
		// парсинг значения 
		u8 *res = nullptr;
		res = &memory[Regs.PC];
		return res;
	}

	u8* parse_pointer()
	{
		// парсинг значения 
		u8 *res = nullptr;
		res = &memory[memory[Regs.PC]];
		return res;
	}
} ALU;

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

		dest = ALU.parse_register(); // парсинг 1-го аргумента	
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_value(); // парсинг 2-го аргумента

		ALU.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x2: // MOV R, R
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_register(); // парсинг 2-го аргумента

		ALU.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x3: // MOV R, [a8]
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register();// парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_pointer(); // парсинг 2-го аргумента

		ALU.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x4: // MOV [a8], R
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_pointer(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_register(); // парсинг 2-го аргумента

		ALU.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x5: // MOV [a8], d8
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_pointer(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_value(); // парсинг 2-го аргумента

		ALU.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x6: // MOV R, [R]
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_ptr_in_register(); // парсинг 2-го аргумента

		ALU.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x7: // MOV [R], R
		Regs.PC++; // увеличить PC
#ifdef PRINT_DEBUG
		printf("MOV instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_ptr_in_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_register(); // парсинг 2-го аргумента

		ALU.MOV(dest, source);
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента
		break;

	case 0x8: // ADD R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("ADD instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_register(); // парсинг 2-го аргумента

		ALU.ADD(dest, source);
		Regs.PC++;
		break;
	case 0x9: // ADD R, d8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("ADD instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_value(); // парсинг 2-го аргумента

		ALU.ADD(dest, source);
		Regs.PC++;
		break;

	case 0xA: // SUB R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("SUB instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_register(); // парсинг 2-го аргумента

		ALU.SUB(dest, source);
		Regs.PC++;
		break;

	case 0xB: // SUB R, d8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("SUB instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_value(); // парсинг 2-го аргумента

		ALU.SUB(dest, source);
		Regs.PC++;
		break;

	case 0xC: // INC R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("INC instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		source = &incrementor;
		Regs.PC++;
		ALU.ADD(dest, source);
		break;

	case 0xD: // DEC R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("DEC instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента

		source = &incrementor;
		Regs.PC++;
		ALU.SUB(dest, source);
		break;

	case 0xE: // CMP R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("CMP instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_register(); // парсинг 2-го аргумента

		ALU.CMP(dest, source);
		Regs.PC++;
		break;
	case 0xF: // CMP R, R
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("CMP instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		dest = ALU.parse_register(); // парсинг 1-го аргумента
		Regs.PC++; // увеличить PC, потому что MOV имеет 2 аргумента 
		source = ALU.parse_value(); // парсинг 2-го аргумента

		ALU.CMP(dest, source);
		Regs.PC++;
		break;
	case 0x10: // JMP a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JMP instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALU.parse_value(); // парсинг 1-го аргумента

		ALU.JMP(*addres);
		break;

	case 0x11: // JE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALU.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALU.JE(*addres);
		break;

	case 0x12: // JNE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JNE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALU.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALU.JNE(*addres);
		break;

	case 0x13: // JL a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JL instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALU.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALU.JL(*addres);
		break;

	case 0x14: // JG a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JG instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALU.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALU.JG(*addres);
		break;

	case 0x15: // JLE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JLE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALU.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALU.JLE(*addres);
		break;

	case 0x16: // JGE a8
		Regs.PC++;
#ifdef PRINT_DEBUG
		printf("JGE instruction! @ [0x%.2X]\n", opcode);
#endif // PRINT_DEBUG

		addres = ALU.parse_value(); // парсинг 1-го аргумента
		Regs.PC++;
		ALU.JGE(*addres);
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

		ALU.SYSCALL();
		break;

	default:
		printf("ERROR instruction [0x%.2X] at 0x%.2X not found\n", opcode, Regs.PC);
		Regs.PC++;
		break;
	}
}

u8 fetch_instruction() {
	return mem_read(Regs.PC);
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

	::memcpy(&memory, &program, sizeof(program)); // скопировать прграму в память процессора
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
	mem_print();
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
				mem_print();
				continue;
			}
			else if (command == ".reset")
			{
				initialize_memory();
				Regs.AX = 0x0;
				Regs.BX = 0x0;
				Regs.CX = 0x0;
				Regs.DX = 0x0;
				Regs.PC = 0x0;
				Regs.SP = 0x0;
				Regs.STATUS.C = false;
				Regs.STATUS.Z = false;
				Regs.STATUS.S = false;
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
		decode_execute_instruction(inst);

	}
	system("pause");
	return 0;
}