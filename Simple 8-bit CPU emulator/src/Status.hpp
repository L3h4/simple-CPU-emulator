#pragma once
#include<iostream>
#include<stdio.h>

#define u8 uint8_t
#define u16 uint16_t

class Status
{

public:
	bool execute_til_hlt = false; // режим виполнения программы до команды HLT (прекратить выполнение)
	bool execute_til_ie = false; // режим виполнения программы до команды IE (прервать выполнение)
	bool erorr = false; // флаг ошибки
	bool exit = false; //флаг выхода из программы

};

