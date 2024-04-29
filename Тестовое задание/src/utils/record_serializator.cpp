#include "record_serializator.h"
#include <iostream>
#include <fstream>

std::string RecordSerializator::filename = "score.bin";

void RecordSerializator::serializeInt(int num, const std::string& filename)
{
	std::ofstream file(filename, std::ios::binary | std::ios::trunc);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(&num), sizeof(num));
		file.close();
	}
	else {
		std::cerr << "Error opening file for writing." << std::endl;
	}
}

int RecordSerializator::deserializeInt(const std::string& filename)
{
	int num = 0;
	std::ifstream file(filename, std::ios::binary);
	if (file.is_open()) {
		file.read(reinterpret_cast<char*>(&num), sizeof(num));
		file.close();
	}
	else {
		RecordSerializator::serializeInt(num, filename);
	}
	return num;
}
