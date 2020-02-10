#include "Ox64cmCPU.h"



Ox64cmCPU::Ox64cmCPU(Bus * b, Status * s)
{
	this->bus = b;
	this->status = s;
	using a = Ox64cmCPU;
	opcodes = {
		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},

		{"MOV", &a::MOV, &a::R,   &a::V},    {"MOV", &a::MOV, &a::aR,   &a::V},    {"MOV", &a::MOV, &a::A,     &a::V},  {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"MOV", &a::MOV, &a::R,   &a::R},    {"MOV", &a::MOV, &a::aR,   &a::R},    {"MOV", &a::MOV, &a::A,     &a::R},  {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"MOV", &a::MOV, &a::R,   &a::A},    {"MOV", &a::MOV, &a::aR,   &a::A},    {"MOV", &a::MOV, &a::A,     &a::A},  {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"MOV", &a::MOV, &a::R,   &a::aR},   {"MOV", &a::MOV, &a::aR,   &a::aR},   {"MOV", &a::MOV, &a::A,     &a::aR}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"MOV", &a::MOV, &a::R16, &a::V16},  {"MOV", &a::MOV, &a::aR16, &a::V16},  {"MOV", &a::MOV, &a::A16,  &a::V16}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"MOV", &a::MOV, &a::R16, &a::R16},  {"MOV", &a::MOV, &a::aR16, &a::R16},  {"MOV", &a::MOV, &a::A16,  &a::R16}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"MOV", &a::MOV, &a::R16, &a::A16},  {"MOV", &a::MOV, &a::aR16, &a::A16},  {"MOV", &a::MOV, &a::A16,  &a::A16}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"MOV", &a::MOV, &a::R16, &a::aR16}, {"MOV", &a::MOV, &a::aR16, &a::aR16}, {"MOV", &a::MOV, &a::A16, &a::aR16}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},

		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA},
		{"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}, {"NOP", &a::NOP, &a::NA, &a::NA}
	};
	this->reset();
}

void Ox64cmCPU::step()
{
	u16 PC_backup = regs.PC.value;
	u8 opcode = *bus->read(regs.PC.value);

	std::string op_dasm = this->opcodes[opcode].name;
	std::string arg1_dasm = (this->*opcodes[opcode].get_arg1)();
	std::string arg2_dasm = (this->*opcodes[opcode].get_arg2)();
#ifdef DEBUG
	printf("0x%.4X | %s %s %s\n", PC_backup, op_dasm.c_str(), arg1_dasm.c_str(), arg2_dasm.c_str());
#endif //DEBUG
	(this->*opcodes[opcode].execute)();
	regs.PC.value++;
}

void Ox64cmCPU::reset()
{
	regs.AX.value = 0;
	regs.BX.value = 0;
	regs.CX.value = 0;
	regs.DX.value = 0;

	regs.PC.value = 0;
	regs.SP.value = 0;

	regs.STATUS.value = 0;
}

void Ox64cmCPU::print_debug()
{
}

void Ox64cmCPU::print_disassembly(u16 start, u16 size)
{
	u16 PC_backup = regs.PC.value;
	for (int i = 0; i < size; i++)
	{
		u16 INST_ADDR = regs.PC.value;
		u8 opcode = *bus->read(regs.PC.value);

		std::string op_dasm = this->opcodes[opcode].name;
		std::string arg1_dasm = (this->*opcodes[opcode].get_arg1)();
		std::string arg2_dasm = (this->*opcodes[opcode].get_arg2)();

		printf("0x%.4X | %s %s %s\n", INST_ADDR, op_dasm.c_str(), arg1_dasm.c_str(), arg2_dasm.c_str());

		regs.PC.value++;
	}
	regs.PC.value = PC_backup;
}





std::string Ox64cmCPU::V()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;
	regs.PC.value++;

	arg->set_type(IMMDATA);
	arg->value = *bus->read(regs.PC.value);


	if (!arg_id) 
	{
		sprintf_s(buf, "0x%.2X", arg->value);
	}
	else 
	{
		sprintf_s(buf, ", 0x%.2X", arg->value);
	}
	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::V16()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;

	arg->set_type(IMMDATA16);

	regs.PC.value++;
	u8 hi = *bus->read(regs.PC.value);

	regs.PC.value++;
	u8 lo = *bus->read(regs.PC.value);

	arg->value16 = (hi << 8) + lo;

	if (!arg_id)
	{
		sprintf_s(buf, "0x%.4X", arg->value16);
	}
	else
	{
		sprintf_s(buf, ", 0x%.4X", arg->value16);
	}

	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::R()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;
	regs.PC.value++;

	arg->set_type(REGISTER);
	arg->reg = regs.parse(*bus->read(regs.PC.value));


	if (!arg_id)
	{
		sprintf_s(buf, "%s", arg->reg->name.c_str());
	}
	else
	{
		sprintf_s(buf, ", %s", arg->reg->name.c_str());
	}
	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::aR()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;
	regs.PC.value++;

	arg->set_type(ADDRESS);
	arg->reg = regs.parse(*bus->read(regs.PC.value));
	arg->address = arg->reg->value;

	if (!arg_id)
	{
		sprintf_s(buf, "[%s]", arg->reg->name.c_str());
	}
	else
	{
		sprintf_s(buf, ", [%s]", arg->reg->name.c_str());
	}

	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::R16()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;

	regs.PC.value++;
	arg->set_type(REGISTER16);
	arg->reg = regs.parse(*bus->read(regs.PC.value));
	if (!arg_id)
	{
		sprintf_s(buf, "%s", arg->reg->name16.c_str());
	}
	else
	{
		sprintf_s(buf, ", %s", arg->reg->name16.c_str());
	}
	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::aR16()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;
	regs.PC.value++;

	arg->set_type(ADDRESS16);
	arg->reg = regs.parse(*bus->read(regs.PC.value));
	arg->address = arg->reg->value;

	if (!arg_id)
	{
		sprintf_s(buf, "[%s]", arg->reg->name16.c_str());
	}
	else
	{
		sprintf_s(buf, ", [%s]", arg->reg->name16.c_str());
	}
	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::A()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;

	arg->set_type(ADDRESS);

	regs.PC.value++;
	u8 hi = *bus->read(regs.PC.value);

	regs.PC.value++;
	u8 lo = *bus->read(regs.PC.value);

	arg->address = *bus->read((hi << 8) + lo);
	if (!arg_id)
	{
		sprintf_s(buf, "[0x%.4X]", arg->address);
	}
	else
	{
		sprintf_s(buf, ", [0x%.4X]", arg->address);
	}
	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::A16()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;

	arg->set_type(ADDRESS16);

	regs.PC.value++;
	u8 hi = *bus->read(regs.PC.value);

	regs.PC.value++;
	u8 lo = *bus->read(regs.PC.value);

	arg->address = (hi << 8) + lo;
	if (!arg_id)
	{
		sprintf_s(buf, "[0x%.4X]", arg->address);
	}
	else
	{
		sprintf_s(buf, ", [0x%.4X]", arg->address);
	}
	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::NA()
{
	char buf[15];
	sprintf_s(buf, "");
	arg_id = false;
	return std::string(buf);
}


#include"MOV.h"

void Ox64cmCPU::ADD()
{
	regs.STATUS.FLAGS.C = false;
	regs.STATUS.FLAGS.Z = false;
	regs.STATUS.FLAGS.S = false;

	
}

void Ox64cmCPU::SUB()
{
	regs.STATUS.FLAGS.C = false;
	regs.STATUS.FLAGS.Z = false;
	regs.STATUS.FLAGS.S = false;
}

void Ox64cmCPU::INC()
{
}

void Ox64cmCPU::DEC()
{
}

void Ox64cmCPU::CMP()
{
}

void Ox64cmCPU::JMP()
{
}

void Ox64cmCPU::JE()
{
}

void Ox64cmCPU::JNE()
{
}

void Ox64cmCPU::JL()
{
}

void Ox64cmCPU::JG()
{
}

void Ox64cmCPU::JLE()
{
}

void Ox64cmCPU::JGE()
{
}

void Ox64cmCPU::NOP()
{
}


