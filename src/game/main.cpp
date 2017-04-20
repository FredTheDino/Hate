#include <iostream>

// Engine
#include "hate/hate.h"

void load() {
	std::cout << "Hello world!" << std::endl;
}

void clean() {
	std::cout << "Goodbye!" << std::endl;
}

int main(int c, char** v) {
	Hate::Hate hate(&load, &clean);
	return 0;
}
