#include "Print.h"
#include <iostream>

namespace WinMachStat {
	void Print::Hello() {

		std::cout << "Hello" << std::endl;
	}
	std::string Print::getHello() {
		return std::string("Hello");
	}
}