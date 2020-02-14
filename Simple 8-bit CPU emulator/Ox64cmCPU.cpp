#include "Ox64cmCPU.h"



Ox64cmCPU::Ox64cmCPU(Bus * b, Status * s)
{
	// конструктор процессора
	this->bus = b;
	this->status = s;

	// »нициализаци€ сэта инструкций
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
	/*
		потом в коде € смогу легко получать нужные обработчики команд и аргументов типа 
		opcodes[код операции] и из этого € получаю обьект »Ќ—“– ÷»я, которою € смогу обрабатывать 
		ќбь€вление структуры »Ќ—“–” ÷»я в файле Ox64cmCPU.h
	*/
	this->reset();
}

void Ox64cmCPU::step()
{
	u8 opcode = bus->read(this->PC.value);
	u16 PC_backup = this->PC.value;
	if (!status->erorr) // если ошибок нет то парсим (парсеры могут подымать ошибки)
	{
		std::string op_dasm = this->opcodes[opcode].name;
		std::string arg1_dasm = (this->*opcodes[opcode].get_arg1)();
		std::string arg2_dasm = (this->*opcodes[opcode].get_arg2)();
		#ifdef DEBUG
		printf("0x%.4X | %s %s,%s\n", PC_backup, op_dasm.c_str(), arg1_dasm.c_str(), arg2_dasm.c_str());
		#endif //DEBUG
	}
	if (!status->erorr) // если ошибок нет то выполн€ем
	{
		(this->*opcodes[opcode].execute)();
		this->PC.value++;
	}
}

void Ox64cmCPU::reset()
{
	this->AX.value = 0;
	this->BX.value = 0;
	this->CX.value = 0;
	this->DX.value = 0;

	this->PC.value = 0;
	this->SP.value = 0;

	this->STATUS.value = 0;
}

void Ox64cmCPU::print_debug()
{
}

void Ox64cmCPU::print_disassembly(u16 start, u16 size)
{
	// функци€ дл€  дизассемблинга 
	// по сути делает то же самое что и ф-ци€ step() но просто не запускает обработчик операции, и после своей работы возвращает все назад
	u16 PC_backup = this->PC.value;
	this->PC.value = start;
	for (int i = 0; i < size; i++)
	{
		u16 INST_ADDR = this->PC.value;
		u8 opcode = bus->read(this->PC.value);

		std::string op_dasm = this->opcodes[opcode].name;
		std::string arg1_dasm = (this->*opcodes[opcode].get_arg1)();
		std::string arg2_dasm = (this->*opcodes[opcode].get_arg2)();

		printf("0x%.4X | %s %s,%s\n", INST_ADDR, op_dasm.c_str(), arg1_dasm.c_str(), arg2_dasm.c_str());

		this->PC.value++;
	}
	this->PC.value = PC_backup;
}


void Ox64cmCPU::print_regs() 
{
	// ¬ывод значений регистров в консоль
	printf("==========\n");
	printf("REGISTERS\n");
	printf("AX = 0x%.4X\n", this->AX.value);
	printf("BX = 0x%.4X\n", this->BX.value);
	printf("CX = 0x%.4X\n", this->CX.value);
	printf("DX = 0x%.4X\n", this->DX.value);
	printf("=========\n");
	printf("PC = 0x%.4X\n", this->PC.value);
	printf("SP = 0x%.4X\n", this->SP.value);
	printf("FLAGS\n");
	printf("S C Z\n");
	printf("%d %d %d\n", this->STATUS.S, this->STATUS.C, this->STATUS.Z);
	printf("==========\n");
}
Ox64cmCPU::Register* Ox64cmCPU::parse_reg(u8 code)
{
	enum
	{
		Ac = 0xA,
		Bc = 0xB,
		Cc = 0xC,
		Dc = 0xD,
		STATc = 0xAB,

		AXc = 0xAA,
		BXc = 0xBB,
		CXc = 0xCC,
		DXc = 0xDD,

		PCc = 0xEE,
		SPc = 0xFF,
	};
	switch (code)
	{
	case Ac:
		return &this->AX;
	case Bc:
		return &this->BX;
	case Cc:
		return &this->CX;
	case Dc:
		return &this->DX;
	case AXc:
		return &this->AX;
	case BXc:
		return &this->BX;
	case CXc:
		return &this->CX;
	case DXc:
		return &this->DX;
	case PCc:
		return &this->PC;
	case SPc:
		return &this->SP;
	default:
		char buf[40];
		sprintf_s(buf, "Can't parse register %.2X", code);
		//raise error
		status->raise_exception(this->PC.value, status->UNKNOWN_REGISTER, buf);
		return nullptr;
		break;
	}
}


std::string Ox64cmCPU::V()
{
	char buf[15];
	OpArg *arg = nullptr;
	if (!arg_id)
		arg = &arg1;
	else
		arg = &arg2;
	this->PC.value++;

	arg->set_type(IMMDATA);
	arg->value = bus->read(this->PC.value);

	sprintf_s(buf, " 0x%.2X", arg->value);

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

	this->PC.value++;
	u8 hi = bus->read(this->PC.value);

	this->PC.value++;
	u8 lo = bus->read(this->PC.value);

	arg->value16 = (hi << 8) + lo;

	sprintf_s(buf, " 0x%.4X", arg->value16);


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
	this->PC.value++;

	arg->set_type(REGISTER);
	u8 reg_code = bus->read(this->PC.value);
	arg->reg = parse_reg(reg_code);

	if (arg->reg)
		sprintf_s(buf, " %s", arg->reg->name.c_str());
	else
		sprintf_s(buf, " Unknown %.2X", reg_code);


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
	this->PC.value++;

	arg->set_type(ADDRESS);
	u8 reg_code = bus->read(this->PC.value);
	arg->reg = parse_reg(reg_code);

	if (arg->reg) {
		sprintf_s(buf, " [%s]", arg->reg->name.c_str());
		arg->address = arg->reg->value;
	}
	else
		sprintf_s(buf, " [Unknown %.2X]", reg_code);
	
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

	this->PC.value++;
	arg->set_type(REGISTER16);
	u8 reg_code = bus->read(this->PC.value);
	arg->reg = parse_reg(reg_code);
	if (arg->reg)
		sprintf_s(buf, " %s", arg->reg->name16.c_str());
	else
		sprintf_s(buf, " Unknown %.2X", reg_code);
		 

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
	this->PC.value++;

	arg->set_type(ADDRESS16);
	u8 reg_code = bus->read(this->PC.value);
	arg->reg = parse_reg(reg_code);


	if (arg->reg) {
		arg->address = arg->reg->value;
		sprintf_s(buf, " [%s]", arg->reg->name16.c_str());
	}
	else
		sprintf_s(buf, " [Unknown %.2X]", reg_code);


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

	this->PC.value++;
	u8 hi = bus->read(this->PC.value);

	this->PC.value++;
	u8 lo = bus->read(this->PC.value);

	arg->address = bus->read((hi << 8) + lo);

	sprintf_s(buf, " [0x%.4X]", arg->address);

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

	this->PC.value++;
	u8 hi = bus->read(this->PC.value);

	this->PC.value++;
	u8 lo = bus->read(this->PC.value);

	arg->address = (hi << 8) + lo;

	sprintf_s(buf, " [0x%.4X]", arg->address);

	arg_id = !arg_id;
	return std::string(buf);
}
std::string Ox64cmCPU::NA()
{
	char buf[15];
	sprintf_s(buf, "\b ");
	arg_id = false;
	return std::string(buf);
}


#include"MOV.hpp" 

void Ox64cmCPU::ADD()
{
	this->STATUS.C = false;
	this->STATUS.Z = false;
	this->STATUS.S = false;
}

void Ox64cmCPU::SUB()
{
	this->STATUS.C = false;
	this->STATUS.Z = false;
	this->STATUS.S = false;
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


