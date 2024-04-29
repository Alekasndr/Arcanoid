#pragma once
#include <string>
class RecordSerializator
{
public:
	static void serializeInt(int num, const std::string& filename);
	static int deserializeInt(const std::string& filename);
	static std::string filename;
};

