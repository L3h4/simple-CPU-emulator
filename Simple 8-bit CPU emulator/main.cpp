#include<iostream>
#include<stdio.h>
#include<string>
#include<windows.h>

using namespace std;

#include"Bus.h"
#include"Ox64cmCPU.h"
#include"Status.hpp"


/*
	Документация https://www.evernote.com/l/AfpYiDoi7_hKJJHEmHGxAVzqdoACyR6W718/
	Дело было вечером, делать было нечего. Короче я наваял емулятор простого 8/16 битного процессора)
	
*/

// обявляю сокращения для типов данных для 1 и 2 байтовых переменных
#define u8 uint8_t 
#define u16 uint16_t

// создаю глобальные переменные
// статус отвечает за некоторые глобальные переменные и механизм подьема ошибок
Status status;
// шина данных и адреса, на ней висят все устройства (пока что только ОЗУ)
Bus bus;
// процессор
Ox64cmCPU cpu;

// скопировать прграму в ОЗУ по адресу
void load_program(u16 address, u8 program[], u16 size) {
	u16 relative_address = address;
	for (; relative_address - address < size; relative_address++) {
		bus.write(relative_address, program[relative_address - address]);
	}
	printf("Your program located at 0x%.4X - 0x%.4X\n", address, relative_address);
}

// временный механизм заполнения памяти
void initialize_memory() 
{

	// компилятора пока что нет поєтому прграму пишем сюда (
	// пока что работает только операция MOV
	// простая программа для теста
	u8 MOV_inst_test_program[] = {
		0x10,0xA,0x3F,		  // MOV A, 0x3F
		0x50,0xBB,0x02,0x34,  // MOV BX, 0x0234
		0x11,0x0B,0xEF,       //MOV [B], 0xEF
		0x72,0x02,0x35,0x0,0x1//MOV [0x0235], [0x0001]
	};
	
	// загрузить программу в память
	load_program(0, MOV_inst_test_program, sizeof(MOV_inst_test_program));
}


void initialize_console_window() {
	// неведомая херня со стаковерфлоу чтобы настроить размер окна
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1100, 600, true);
}


int main() {
	// инициализирую переменные
	// они принимают указатели друг на друга
	status = Status(); 
	bus = Bus(&status);
	cpu = Ox64cmCPU(&bus, &status);
	bus.connect_cpu(&cpu);
	// переменная для хранения команды юзера
	string command;
	

	initialize_console_window(); // настройка размеров окна
	initialize_memory(); // запись простой прграммы в память
	printf("Press enter to make step or type .help to get help\n");

	while (true) // главный цикл программы
	{
		if (!status.execute_til_hlt) // процессор работает синхронно поэтому сначала мы ждем действий пользователя а потом делаем шаг(если процессор запущен в режиме виполнения до команды HALT, пользователя не спрашиваем, а сразу делаем шаг)
		{
			// Неболюшое меню
			printf("# ");
			getline(cin, command);
			if (command == ".help")
			{
				// help сообщение
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
				// при вводе этой команды процессор начнет работать в режиме выполнения до команды HALT
				if (!status.erorr) // соответственно если ошибок нет, то стартуем
					status.execute_til_hlt = true;
			}
			else if (command == ".registers" || command == ".regs")
			{
				// при вводе этой команды в консоль выведется содержимое регистров и флагов
				cpu.print_regs();
				continue;
			}
			else if (command == ".memory" || command == ".mem")
			{
				// при вводе этой команды в консоль выведется содержимое ВСЕХ 2 кб озу
				bus.RAM.print();
				continue;
			}
			else if (command == ".reset")
			{
				// при вводе этой команды произойдет перезапуск
				initialize_memory();
				cpu.reset();
				status.erorr = false;
				status.execute_til_hlt = false;
				continue;
			}
			else if (command == ".disassemble" || command == ".dasm")
			{
				// при вводе этой команды в консоль выведется  дизассемблированые первые 21 байт памяти
				cpu.print_disassembly(0, 20);
				continue;
			}
			else if (command == "") 
			{
				// при вводе этой команды просто произведется шаг процессора
			}
			else if (command == ".exit")
			{
				// при вводе этой команды выход из программы
				return 0;
			}
			else
			{
				// если команда не найдена то вывести ошибку
				printf("Error command %s not found\n", command.c_str());
				continue;
			}
		}
		if (!status.erorr)
			cpu.step(); // выполнить операцию если ошибок нет
		else
			printf("Can't make step, CPU freezed\n"); // иначе ничего не делаем
	}
	system("pause");
	return 0;
}