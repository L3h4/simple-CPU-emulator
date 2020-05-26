#include "CompilingUtilities.h"



std::vector<uint8_t> utilities::concat_vectors(std::vector<uint8_t> a, std::vector<uint8_t> b)
{
	a.insert(a.end(), b.begin(), b.end());
	return a;
}

bool utilities::has_brackets(std::string text)
{
	return text.substr(0, 1) == "[" && text.substr(text.size() - 1) == "]";
}

bool utilities::has_quotes(std::string text)
{
	return text.substr(0, 1) == "\"" && text.substr(text.size() - 1) == "\"";;
}

std::string utilities::delete_brackets(std::string text)
{
	if (has_brackets(text))
		return text.substr(1).substr(0, text.size() - 2);
	else
		return text;
}

std::string utilities::delete_quotes(std::string text)
{
	if (has_quotes(text))
		return text.substr(1).substr(0, text.size() - 2);
	else
		return text;
}



std::string utilities::trim(const std::string& str)
{
	// херобора со stackoverflow
	// trim first
	const std::string fill = " ";
	const std::string whitespace = " \t";
	std::string result;
	
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	result = str.substr(strBegin, strRange);

	// replace sub ranges
	auto beginSpace = result.find_first_of(whitespace);
	while (beginSpace != std::string::npos)
	{
		const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
		const auto range = endSpace - beginSpace;

		result.replace(beginSpace, range, fill);

		const auto newStart = beginSpace + fill.length();
		beginSpace = result.find_first_of(whitespace, newStart);
	}

	return result;
}

std::string utilities::to_lower(std::string text)
{
	std::transform(text.begin(), text.end(), text.begin(), std::tolower); 

	return text;
}

std::string utilities::replace_string(std::string subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) 
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

// валидаторы аргументов
bool utilities::is_instruction(std::string text)
{
	for (std::string possible_token : possible_cmds)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}
bool utilities::is_size_identifier(std::string text)
{
	for (std::string possible_token : possible_size_identifiers)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}



bool utilities::register8(std::string text)
{
	for (std::string possible_token : possible_registers8)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}
bool utilities::register16(std::string text)
{
	for (std::string possible_token : possible_registers16)
	{
		if (text == possible_token)
			return true;
	}
	return false;
}
bool utilities::dec_number(std::string text)
{
	if (text.substr(0, 1) == "-")
		text = text.substr(1);

	if (text == "")
		return false;

	for (auto ch : text)
		if (ch < '0' || ch > '9')
			return false;

	return true;
}
bool utilities::hex_number(std::string text)
{
	if (text.substr(0, 2) != "0x")
		return false;
	else
		text = text.substr(2);

	if(text == "")
		return false;

	for (auto ch : text)
		if (('9' < ch || ch < '0') && ('f' < ch || ch < 'a'))
			return false;

	return true;
}


bool utilities::ptr_in_register(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return register16(text) || register8(text);
}
bool utilities::ptr_in_dec_number(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return dec_number(text);
}
bool utilities::ptr_in_hex_number(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return hex_number(text);
}

bool utilities::named_ptr(std::string text)
{
	if (text == "")
		return false;

	if (dec_number(text.substr(0, 1)) || text.substr(text.size() - 1, 1) == ":")
		return false;

	for (auto ch : text)
		if ((ch < 'a' || ch > 'z') && (ch < '0' || ch > '9'))
			if (ch != '_' && ch != '-'&& ch != '.')
				return false;
	for (auto reg : possible_registers)
		if (reg == text)
			return false;
	return true;
}
bool utilities::ptr_in_named_ptr(std::string text)
{
	if (!has_brackets(text))
		return false;
	else
		text = delete_brackets(text);

	return named_ptr(text);
}
bool utilities::named_ptr_definition(std::string text)
{
	if (text.substr(text.size() - 1, 1) != ":")
		return false;
	else
		text = text.substr(0, text.size() - 2);

	return named_ptr(text);
}

bool utilities::is_preprocessor_instruction(std::string text)
{
	for (auto pos_inst : possible_preprocessor_cmds)
		if (pos_inst == text)
			return true;

	return false;
}

bool utilities::is_metadata(std::string text)
{
	for (auto pos_inst : possible_metadata_cmds)
		if (pos_inst == text)
			return true;
	return false;
}


// компиляторы аргументов
std::vector<uint8_t> utilities::compile_dec_number(std::string text, int size)
{
	std::vector<uint8_t> res;
	
	int x;
	sscanf_s(text.c_str(), "%d", &x);
	if (size == 1 || (size == 0 && x < 256))
	{
		res.push_back((uint8_t)x);
	}
	else if (size == 2 || (size == 0 && (x > 255 && x < 65536)))
	{
		uint8_t hi = x >> 8;
		uint8_t lo = x;
		res.push_back(hi);
		res.push_back(lo);
	}
	else
	{
		char buf[70];
		sprintf_s(buf, "Can't understand number \"%s\"", text.c_str());
		throw (std::string)buf;
	}
	return res;
}
std::vector<uint8_t> utilities::compile_hex_number(std::string text, int size)
{
	std::vector<uint8_t> res;
	int x;
	sscanf_s(text.c_str(), "0x%x", &x);
	if (size == 1 || (size == 0 && x < 256))
	{
		res.push_back((uint8_t)x);
	}
	else if (size == 2 || (size == 0 && (x > 255 && x < 65536)))
	{
		uint8_t hi = x >> 8;
		uint8_t lo = x;
		res.push_back(hi);
		res.push_back(lo);
	}
	else
	{
		char buf[70];
		sprintf_s(buf, "Can't understand number \"%s\"", text.c_str());
		throw (std::string)buf;
	}
	return res;
}
std::vector<uint8_t> utilities::compile_number(std::string text, int size)
{
	if (hex_number(text))
		return compile_hex_number(text, size);
	else if (dec_number(text))
		return compile_dec_number(text, size);
	else
	{
		char buf[70];
		sprintf_s(buf, "Can't compile number \"%s\"", text.c_str());
		throw (std::string)buf;
	}
}
std::vector<uint8_t> utilities::compile_register(std::string text)
{
	std::vector<uint8_t> res;

	if (text == "a")
	{
		res.push_back(0xA);
	}
	else if (text == "b")
	{
		res.push_back(0xB);
	}
	else if (text == "c")
	{
		res.push_back(0xC);
	}
	else if (text == "d")
	{
		res.push_back(0xD);
	}
	else if (text == "status")
	{
		res.push_back(0xAB);
	}
	else if (text == "ax")
	{
		res.push_back(0xAA);
	}
	else if (text == "bx")
	{
		res.push_back(0xBB);
	}
	else if (text == "cx")
	{
		res.push_back(0xCC);
	}
	else if (text == "dx")
	{
		res.push_back(0xDD);
	}
	else if (text == "pc")
	{
		res.push_back(0xEE);
	}
	else if (text == "sp")
	{
		res.push_back(0xFF);
	}
	else
	{
		char buf[70];
		sprintf_s(buf, "Can't understand register %s", text.c_str());
		throw (std::string)buf;
	}

	return res;
}

std::vector<uint8_t> utilities::compile_string(std::string text)
{
	std::vector<uint8_t> res;

	for (char ch : text)
	{
		res.push_back(ch);
	}
	res.push_back(0);
	return res;
}


