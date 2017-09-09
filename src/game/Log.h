#pragma once

#include <iostream>
#include <string>
#include <vector>

#define INFO_PREFIX "[INFO] "
#define WARN_PREFIX "[WARN] "
#define ERR_PREFIX  "[ERROR] "

namespace Log {

	static void info(std::string msg) {
		std::cout << INFO_PREFIX << msg << "\n";
	}

	static void warn(std::string msg) {
		std::cout << WARN_PREFIX << msg << "\n";
	}

	static void error(std::string msg) {
		std::cout << ERR_PREFIX << msg << "\n";
	}

	static void info(const char* msg) {
		std::cout << INFO_PREFIX << msg << "\n";
	}

	static void warn(const char* msg) {
		std::cout << WARN_PREFIX << msg << "\n";
	}

	static void error(const char* msg) {
		std::cout << ERR_PREFIX << msg << "\n";
	}

}