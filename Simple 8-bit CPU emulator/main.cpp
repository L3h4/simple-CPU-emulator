#include<iostream>
#include<stdio.h>
#include<string>


using namespace std;

#include"Bus.h"
#include"Ox64cmCPU.h"
#include"Status.h"
#include"Memory.h"
#include"MainWindow.h"

/*
	Дело было вечером, делать было нечего. Короче я наваял эмулятор простого 8 битного процессора)
*/

// обявляю сокращения для типов данных для 1 и 2 байтовых переменных
#define u8 uint8_t 
#define u16 uint16_t

// создаю глобальные переменные
// статус отвечает за некоторые глобальные переменные
Status* status = nullptr;
// шина данных и адреса, на ней висят все устройства (пока что только ОЗУ)
Bus* bus = nullptr;
// процессор
Ox64cmCPU* cpu = nullptr;



// временный механизм заполнения памяти
void initialize_memory(std::string program_name) 
{
	// загрузить программу в память
	try
	{
		bus->load_from_file(program_name);
	}
	catch (const char* e)
	{
		printf("LOAD MEMORY ERROR \"%s\"\n", e);
		status->exit = true;
	}
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
			status->exit = true;
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
	status = new Status(); 
	bus = new Bus(status);
	cpu = new Ox64cmCPU(bus, status);
	bus->connect_cpu(cpu);
	// переменная для хранения команды юзера
	//string command;
	std::string program_file_name = parse_args(argc, argv);

	if (program_file_name == "")
		status->exit = true;

	if (!status->exit)
		initialize_memory(program_file_name);

	MainWindow window;
	bus->RAM.print();
	cpu->reset();

	window.coonect_cpu_bus_status(cpu, bus, status);

	if (window.Construct(600, 400, 2, 2) && !status->exit)
		window.Start();
	
	delete bus, status, cpu;
	
	return 0;
}