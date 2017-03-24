#include <iostream>

// Engine
#include "hate/hate.h"

int main(int c, char** v) {
	if (callMe() == 1) {
		std::cout << "Hello!" << std::endl;
		return 2;
	}
	return 0;
}
