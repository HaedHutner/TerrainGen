#pragma once

#include <string>
#include <fstream>

namespace FileUtils {

	static std::string file_to_string(const std::string& file_path) {
		std::ifstream infile{ file_path };
		std::string content{ std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };

		return content;
	}

}