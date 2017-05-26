#include <iostream>

// Engine
#include "hate.h"
#include "entity.h"
#include "math.h"

void load() {
	hate::Mat4 m;
	hate::Mat4 n;
	hate::Quat q(1, 0, 0, 0);

	n._[0][1] = 10;

	m.print();
	printf("\n--------\n\n");
	n.print();
	printf("\n--------\n\n");
	(n * m).print();
	printf("\n--------\n\n");
	q.print();
	std::cout << "Hello world!" << std::endl;
}

void clean() {
	std::cout << "Goodbye!" << std::endl;
}

int main(int c, char** v) {
	hate::Hate hate(&load, &clean);
	return 0;
}
