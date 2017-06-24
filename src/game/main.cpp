#include <core.h>
#include <graphics.h>

using namespace hate;

int main(int c, char** v) {
	hate::init_hate();

	cam.zoom = 2.5f;

	hate::run_hate();

	return 0;
}
