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

std::string GPU::get_buffer()
{
	return buffer;
}

/*
olc::Sprite& GPU::get_screen()
{
	return olc::Sprite();//screen;
}
*/