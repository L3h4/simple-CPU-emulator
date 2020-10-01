#include "GPU.h"



GPU::GPU()
{
	//screen = olc::Sprite(450, 400);
	//screen.SetPixel(10, 10, olc::RED);
}


GPU::~GPU()
{
	//screen.~Sprite();
}

u16 GPU::read16(u16 address)
{
	return u16();
}

u8 GPU::read8(u16 address)
{
	return u8();
}

void GPU::write16(u16 address, u16 data)
{
}

void GPU::write8(u16 address, u8 data)
{
}

void GPU::clock()
{
}

void GPU::print_text(std::string text)
{
	buffer += text;
}

void GPU::clear_buffer()
{
	buffer = "";
}

const std::string&  GPU::get_buffer()
{
	return buffer;
}

/*
olc::Sprite& GPU::get_screen()
{
	return olc::Sprite();//screen;
}
*/