#include "misc.h"

namespace hate {
	std::vector<std::string> split(std::string source, char point) {
		std::vector<std::string> out;

		std::stringstream ss;
		ss.str(source);
		std::string item;

		while (std::getline(ss, item, point)) {
			// Remove empty strings
			if (item.size() != 0)
				out.push_back(item);
		}
		
		return out;
	}
}
