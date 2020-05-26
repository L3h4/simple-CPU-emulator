#pragma once
#include<iostream>

#include "../../olcPixelGameEngine.h"

#define u8 uint8_t
#define u16 uint16_t
class GPU
{
public:
	GPU();
	~GPU();

private:
	u8 GraphicMemory[1024];
	std::string buffer;

public:
	//olc::Sprite screen = olc::Sprite(450, 400);
	bool frame_complete = false;

	void clock();

	void print_text(std::string text);

	void clear_buffer();

	std::string get_buffer();


};

