#pragma once
#include "olcPixelGameEngine.h"
#include "BusDevice.h"

#define u8 uint8_t
#define u16 uint16_t
class GPU : public BusDevice
{
public:
	GPU();
	~GPU();

private:
	//u8 GraphicMemory[1024];
	std::string buffer;
	u16 read16(u16 address)override;
	u8 read8(u16 address) override;

	void write16(u16 address, u16 data) override;
	void write8(u16 address, u8 data) override;

public:
	//olc::Sprite screen = olc::Sprite(450, 400);
	bool frame_complete = false;

	void clock();

	void print_text(std::string text);

	void clear_buffer();

	const std::string& get_buffer();


};

