// 
// I didn't know where to put this, so I made a new file.
// I might move this about but for now all lose procedures
// stay here.
//
#pragma once
#include <sstream>
#include <vector>

namespace hate {
	// Because C++ doesn't offer this in the std library, so here we are.
	extern std::vector<std::string> split(std::string source, char point = ' ');
}
