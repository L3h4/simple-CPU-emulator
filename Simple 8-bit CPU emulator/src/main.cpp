#include<iostream>
#include<stdio.h>
#include<string>
#include<windows.h>

using namespace std;

#include"Bus/Bus.h"
#include"cpu/Ox64cmCPU.h"
#include"Status.hpp"
#include"Bus/Memory/Memory.h"

/*
	Дело было вечером, делать было нечего. Короче я наваял эмулятор простого 8/16 битного процессора)
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
		bus.RAM.write<u8>(relative_address, program[relative_address - address]);
		//bus.RAM.write<u8>(123, 4);
	}
	printf("Your program located at 0x%.4X - 0x%.4X\n", address, relative_address);
}

// временный механизм заполнения памяти
void initialize_memory(std::string program_name) 
{
	// загрузить программу в память
	try
	{
		bus.load_from_file(program_name);
	}
	catch (std::string e)
	{
		printf("LOAD MEMORY ERROR \"%s\"\n", e.c_str());
		status.exit = true;
	}
}


void initialize_console_window() {
	// неведомая херня со стаковерфлоу чтобы настроить размер окна
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1100, 600, true);
}


std::string parse_args(int argc, char *argv[])
{
	// простой парсер аргументрв командной строки
	if (argc == 1)
	{
		printf("No input file specified\n");
	}

	for (int i = 1; i < argc; i++)
	{
		if ((string)argv[i] == "--help" || (string)argv[i] == "-h")
		{
			printf("USAGE: \"%s [options] -i program.bin\"\n\n", argv[0]);
			printf("\t%-2s %-7s  -  %s", "-h", "--help", "Shows this message\n");
			printf("\t%-2s %-7s  -  %s", "-i", "--in", "Input file\n");
			status.exit = true;
		}
		else if ((string)argv[i] == "-i" || (string)argv[i] == "--in")
		{
			if (i < argc)
				return argv[++i];
			else
				printf("No input file specified\n");
		}
		else
		{
			printf("Unknown argument \"%s\" use \"%s --help\" to get help\n", argv[i], argv[0]);
			return false;
		}
	}
	return "";
}


int main(int argc, char *argv[]) 
{
	// инициализирую переменные
	// они принимают указатели друг на друга
	status = Status(); 
	bus = Bus(&status);
	cpu = Ox64cmCPU(&bus, &status);
	bus.connect_cpu(&cpu);
	// переменная для хранения команды юзера
	string command;
	
	std::string program_file_name = parse_args(argc, argv);
	
	if (program_file_name == "")
		status.exit = true;
	initialize_console_window(); // настройка размеров окна

	if (!status.exit)
		initialize_memory(program_file_name);

	if(!status.exit)
		printf("Press enter to make step or type .help to get help\n");

	while (!status.exit) // главный цикл программы
	{
		if (!status.execute_til_hlt || status.exit || status.erorr) // процессор работает синхронно поэтому сначала мы ждем действий пользователя а потом делаем шаг(если процессор запущен в режиме виполнения до команды HALT, пользователя не спрашиваем, а сразу делаем шаг)
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
				printf("%s\n", cpu.regs.get_string(0).c_str());
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
				initialize_memory(program_file_name);
				cpu.reset();
				status.erorr = false;
				status.execute_til_hlt = false;
				status.exit = false;
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
		if (!status.erorr && !status.exit)
			cpu.step(); // выполнить операцию если ошибок нет, и процессор не выключился
		else
			printf("Can't make step, CPU freezed\n"); // иначе ничего не делаем
	}
	#ifdef DEBUG
	system("pause");
	#endif // DEBUG
	return 0;
}