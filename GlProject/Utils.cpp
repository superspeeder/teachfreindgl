#include "Utils.h"

#include <ostream>
#include <istream>

std::string Read(std::string filePath) {
	try {
		std::ifstream file(filePath);
		if (!file.is_open()) {
			std::cerr << "Unable to open file" << std::endl;
			return "";
		}
		std::string str;
		std::string file_contents;
		try {
			while (std::getline(file, str))
			{
				file_contents += str;
				file_contents.push_back('\n');
			}
		}
		catch (...) {

		}
		file.close();
		return file_contents;
	}
	catch (...) {
		std::cerr << "\"HEY BUDDY\" - Blayke Alexanian";
		return "";
	}
//	return "";
}

