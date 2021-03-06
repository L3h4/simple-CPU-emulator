#include "RegisterFile.h"



RegisterFile::RegisterFile()
{
}


RegisterFile::~RegisterFile()
{
}




std::string RegisterFile::get_string(u8 code)
{
	char buf[150];
	if (code == 0)
	{
		
		// ����� �������� ��������� � �������
		sprintf_s(buf, "==========\nREGISTERS\nAX = 0x%.4X\nBX = 0x%.4X\nCX = 0x%.4X\nDX = 0x%.4X\n=========\nPC = 0x%.4X\nSP = 0x%.4X\nFLAGS\nS C Z\n%d %d %d\n==========", this->AX.value, this->BX.value, this->CX.value, this->DX.value, this->PC.value, this->SP.value, this->STATUS.S, this->STATUS.C, this->STATUS.Z);

	}
	else if (code == 1)
	{
		sprintf_s(buf, "AX = 0x%.4X\nBX = 0x%.4X\nCX = 0x%.4X\nDX = 0x%.4X\n", this->AX.value, this->BX.value, this->CX.value, this->DX.value);
	}
	else if (code == 2)
	{
		sprintf_s(buf, "PC = 0x%.4X\nSP = 0x%.4X\n", this->PC.value, this->SP.value);
	}
	else if (code == 3)
	{
		sprintf_s(buf, "%d %d %d", this->STATUS.S, this->STATUS.C, this->STATUS.Z);
	}
	else
	{
		switch (code)
		{
		case Ac:
			sprintf_s(buf, "%.2X", this->AX.lo);
			break;
		case Bc:
			sprintf_s(buf, "%.2X", this->BX.lo);
			break;
		case Cc:
			sprintf_s(buf, "%.2X", this->CX.lo);
			break;
		case Dc:
			sprintf_s(buf, "%.2X", this->DX.lo);
			break;
		case STATc:
			sprintf_s(buf, "%.2X", this->STATUS.value);
			break;

		case AXc:
			sprintf_s(buf, "%.4X", this->AX.value);
			break;
		case BXc:
			sprintf_s(buf, "%.4X", this->BX.value);
			break;
		case CXc:
			sprintf_s(buf, "%.4X", this->CX.value);
			break;
		case DXc:
			sprintf_s(buf, "%.4X", this->DX.value);
			break;

		case PCc:
			sprintf_s(buf, "%.4X", this->PC.value);
			break;
		case SPc:
			sprintf_s(buf, "%.4X", this->SP.value);
			break;

		default:
			sprintf_s(buf, "Cant understand register 0x%.2X", code);
			throw buf;
			break;
		}
	}

	return (std::string)buf;
}

std::string RegisterFile::get_string_name(u8 code)
{
	std::string name;
	switch (code)
	{
	case Ac:
		name = AX.name;
		break;
	case Bc:
		name = BX.name;
		break;
	case Cc:
		name = CX.name;
		break;
	case Dc:
		name = DX.name;
		break;
	case STATc:
		name = "STATUS";
		break;

	case AXc:
		name = AX.name16;
		break;
	case BXc:
		name = BX.name16;
		break;
	case CXc:
		name = CX.name16;
		break;
	case DXc:
		name = DX.name16;
		break;

	case PCc:
		name = PC.name16;
		break;
	case SPc:
		name = SP.name16;
		break;

	default:
		char buf[40];
		sprintf_s(buf, "Cant understand register 0x%.2X", code);
		throw buf;
		break;
	}

   return name;
}
