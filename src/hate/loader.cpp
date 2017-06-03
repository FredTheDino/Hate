#include "loader.h"
#include <fstream>
#define MAX_DEPTH 5

namespace hate {
	std::string os_path = "res/";

	void find_resource_location() {
		std::string name_of_file = ".res";
		std::ifstream file;
		for (int i = 0; i < MAX_DEPTH; i++) {
			file.open(get_real_path(name_of_file));
			if (file) {
				file.close();
				break;
			} else {
				os_path = "../" + os_path;
				if (i == MAX_DEPTH - 1) {
					// We totally failed... This is a critical error.
					printf("Failed to find resource directory.\n");
					throw -1;
				}
			}
		}
	}

	std::string get_real_path(std::string path) {
		return os_path + path;
	}
}
