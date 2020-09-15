#include "Bus.h"



Bus::Bus()
{

}

Bus::Bus(Status *s)
{
	this->RAM = Memory();
	this->status = s;
}

void Bus::connect_cpu(Ox64cmCPU *c)
{
	this->cpu = c;
}

void Bus::load_from_file(std::string file_name)
{
	// Читаю бинарник сишным способом потому что с++ный способ не работает
	FILE* f;
	fopen_s(&f, file_name.c_str(), "rb");
	
	if (!f)
	{
		char buf[100];
		sprintf_s(buf, "Cant open file \"%s\"", file_name.c_str());

		throw buf;
	}



	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	u8* bytes = new u8[size];

	fread_s(bytes, size, 1, size, f);
	
	fclose(f);

	
	
	for (int i = 0; i < size; i++)// заделка под чтение хедера и всего остального
	{
		if (i < 16)
			RAM.write<u8>(0x07F0 + i, (u8)bytes[i]);
		else
			RAM.write<u8>(i-16, (u8)bytes[i]);
	}

	delete[] bytes;
}
