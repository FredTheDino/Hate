#include <iostream>

// Engine
#include "hate.h"
#include "entity.h"
#include "math.h"

void load() {
	std::cout << "Hello world!" << std::endl;
}

void clean() {
	std::cout << "Goodbye!" << std::endl;
}

int main(int c, char** v) {
	hate::Hate hate(&load, &clean);
	return 0;
}
