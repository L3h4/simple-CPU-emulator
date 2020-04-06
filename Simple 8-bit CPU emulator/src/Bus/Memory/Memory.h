#pragma once
#include<iostream>
#include<stdio.h>

#define u8 uint8_t
#define u16 uint16_t


class Memory // клас ќ«”
{
public:
	Memory();
	~Memory();

public:
	u8 memory[1024 * 2]; // 2кб озу

	template<typename T>
	void write(u16 addres, T value)
	{
		if (addres < 2048)
		{
			if (sizeof(value) == 2)
			{
				memory[addres] = (u8)(value >> 8);
				memory[addres + 1] = (u8)value;
			}
			else
			{
				memory[addres] = (u8)value;
			}
		}
		else 
		{
			throw "Bad Addres";
		}
	}

	template<typename T>
	T  read(u16 addres)
	{
		if (addres < 2048)
		{
			if (typeid(T) == typeid(u16))
			{
				return (u16)(memory[addres] << 8) + memory[addres + 1];
			}
			else
			{
				return memory[addres];
			}
		}
		else
		{
			throw "Bad Addres";
		}
	}

	
/*
public:	template<typename T>
	void write(u16 addres, T value); // метод записи ¬ ѕјћя“№
	

public:	template<typename T>
	T read(u16 addres); // метод чтени€ »« ѕјћя“»
	*/
	void print();
};

