#pragma once
#include<iostream>
#include"Ox64cmCPU.h"
#include"Status.hpp"

#define u8 uint8_t
#define u16 uint16_t

class Ox64cmCPU;

// ���� ����
class Bus
{
public:
	Bus() {}
	Bus(Status *s);

	void connect_cpu(Ox64cmCPU *c);

private:
	class Memory // ���� ���
	{
	public:
		u8 memory[1024 * 2]; // 2�� ���
		void write(u16 addres, u8 value); // ����� ������ � ������
		u8 read(u16 addres); // ����� ������ �� ������
		void print();
	};
public:
	u8 read(u16 addres); // ����� ������ �� ����

	void write(u16 addres, u8 data); // ����� ������ �� ����


public: // ������� �� ���� (���)
	Memory RAM; // ���


private:
		Status *status;
		Ox64cmCPU *cpu;
};