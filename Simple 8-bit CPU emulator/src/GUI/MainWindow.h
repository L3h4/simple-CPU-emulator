#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngine.h"
// Override base class with your custom functionality

class MainWindow : public olc::PixelGameEngine
{
public:
	MainWindow()
	{
		sAppName = "Simple cpu emulator";
		
	}

private:
	Ox64cmCPU* cpu;
	Bus* bus;
	Status* status;
	std::vector<DisassembledInstruction> disassembled;

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		//printf("hello\n");

		disassembled = cpu->get_disassembly(0, 0xff);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);

		if (GetKey(olc::Key::R).bPressed)
			cpu->reset();

		if ((GetKey(olc::Key::SPACE).bPressed || status->execute_til_hlt) && !status->erorr && !status->exit)
		{
			cpu->step();
		}

		if (GetKey(olc::Key::E).bPressed)
			status->execute_til_hlt = !status->execute_til_hlt;

		//if (status->exit)
		//	exit(0);

		draw_video_output();
		draw_sidebar();
		print_disassembly();

		return true;
	}

public:
	void coonect_cpu_bus_status(Ox64cmCPU* cpu, Bus* bus, Status *status)
	{
		this->cpu = cpu;
		this->bus = bus;
		this->status = status;
	}

private:
	void draw_sidebar()
	{
		olc::vi2d panel_offset = olc::vi2d(455, 0);

		olc::vi2d line_offset = olc::vi2d(10, 7);
		olc::vi2d line_size = olc::vi2d(0, 15);
		olc::vi2d second_col = olc::vi2d(60, 0);


		

		FillRect(panel_offset, olc::vi2d(200 - 1, 400 - 1), olc::BLUE);

		FillRect(panel_offset, olc::vi2d(200 - 1, 20 - 1), olc::DARK_BLUE);
		DrawRect(panel_offset, olc::vi2d(200 - 1, 130 - 1), olc::WHITE);

		DrawString(panel_offset + line_offset, "Ox64cm DEBUG", olc::WHITE, 1);

		line_offset += line_size;

		DrawString(panel_offset + line_offset - olc::vi2d(5, 0), "FLAGS:", olc::WHITE, 1);
		line_offset += line_size;
		DrawString(panel_offset + line_offset, "S", cpu->regs.STATUS.S ? olc::RED : olc::WHITE, 1);
		DrawString(panel_offset + line_offset + olc::vi2d(15, 0), "C", cpu->regs.STATUS.C ? olc::RED : olc::WHITE, 1);
		DrawString(panel_offset + line_offset + olc::vi2d(30, 0), "Z", cpu->regs.STATUS.Z ? olc::RED : olc::WHITE, 1);

		line_offset += line_size;

		DrawString(panel_offset + line_offset - olc::vi2d(5, 0), "==================", olc::WHITE, 1);
		line_offset += line_size;

		DrawString(panel_offset + line_offset - olc::vi2d(5, 0), "REGISTERS:", olc::WHITE, 1);
		line_offset += line_size;

		DrawString(panel_offset + line_offset, "AX=", olc::WHITE, 1); DrawString(panel_offset + line_offset + olc::vi2d(24 ,0), cpu->regs.get_string(0xAA), olc::GREEN, 1);
		DrawString(panel_offset + line_offset + olc::vi2d(60, 0), "BX=", olc::WHITE, 1); DrawString(panel_offset + line_offset + second_col + olc::vi2d(24, 0), cpu->regs.get_string(0xBB), olc::GREEN, 1);
		line_offset += line_size;

		DrawString(panel_offset + line_offset, "CX=", olc::WHITE, 1); DrawString(panel_offset + line_offset + olc::vi2d(24, 0), cpu->regs.get_string(0xCC), olc::GREEN, 1);
		DrawString(panel_offset + line_offset + olc::vi2d(60, 0), "DX=", olc::WHITE, 1); DrawString(panel_offset + line_offset + second_col + olc::vi2d(24, 0), cpu->regs.get_string(0xDD), olc::GREEN, 1);
		line_offset += line_size;

		DrawString(panel_offset + line_offset, "PC=", olc::WHITE, 1); DrawString(panel_offset + line_offset + olc::vi2d(24, 0), cpu->regs.get_string(0xEE), olc::GREEN, 1);
		DrawString(panel_offset + line_offset + olc::vi2d(60, 0), "SP=", olc::WHITE, 1); DrawString(panel_offset + line_offset + second_col + olc::vi2d(24, 0), cpu->regs.get_string(0xFF), olc::GREEN, 1);
		line_offset += line_size;

		DrawRect(panel_offset + olc::vi2d(0, 130 - 1), olc::vi2d(200 - 1, 270 - 1), olc::WHITE);

	}

	void draw_video_output()
	{
		DrawString(olc::vi2d(115, 190), "Video does not implemented yet", olc::WHITE);

		DrawString(olc::vi2d(115, 300), "SPACE - Make 1 step\n    R - Reset\n    E - Satrt\stop execution", olc::WHITE);
	}

	void print_disassembly()
	{
		olc::vi2d position(457, 130);
		olc::vi2d offset(0, 13);


		DisassembledInstruction ci(0, "");

		int ci_index;

		for (int i = 0; i < disassembled.size(); i++)
		{
			if (disassembled[i].address == cpu->regs.PC.value)
			{
				ci = disassembled[i];
				ci_index = i;
			}
		}
		//макс лох inc.

		for (int i = ci_index - 9; i < ci_index + 13; i++)
		{
			auto di = i >= 0 ? disassembled[i] : DisassembledInstruction(0, "");


			//disassembly_ofset + i >= 0 ? cpu->regs.PC.value == di.address ? ">" + di.text : di.text : ""
			DrawString(position, i == ci_index ? ">" + di.text : " " + di.text, i == ci_index ? olc::RED : olc::WHITE);
			
			position += offset;
		}


	}

	
};
