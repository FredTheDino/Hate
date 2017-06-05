#include "input.h"
#include "loader.h"
#include "core.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

namespace hate {
	enum key_state {
		RELEASED	= 0,
		PRESSED		= 1,
		UP			= 2,
		DOWN		= 3,
	};

	struct input {
		// -1 if it's keyboard.
		int joy_id = -1;
		int button;
	};

	std::unordered_map<std::string, std::vector<input>> key_map;
	std::unordered_map<std::string, key_state> state_map;

	// Input format:
	// name [K/J] (joy_id) button

	// Because C++ doesn't offer this in the std library.
	std::vector<std::string> split(std::string source, char point) {
		std::vector<std::string> out;

		std::stringstream ss;
		ss.str(source);
		std::string item;

		while (std::getline(ss, item, point)) {
			out.push_back(item);
		}
		
		return out;
	}

	void load_input_map(std::string path) {
		std::ifstream file;
		file.open(get_real_path(path));
		
		std::string line;
		while (std::getline(file, line)) {
			
			// Check that it isn't a comment
			if (line[0] == '#') continue;

			auto parse = split(line, ' ');
			auto name = parse[0];
			input i;
			if (parse[1] == "K") {
				i.button = parse[2][0];
			} else if (parse[1] == "J") {
				// TODO: Do parsing for the input.
			}

			auto it = key_map.find(name);
			if (it != key_map.end()) {
				std::vector<input> inputs;
				inputs.push_back(i);
				key_map.insert(std::make_pair(name, inputs));
				state_map.insert(std::make_pair(name, UP));
			} else {
				key_map[name].push_back(i);
			}
		}
	}

	void update_input_map() {
		glfwPollEvents();
		for (auto it : state_map) {
			if (it.second == PRESSED) {
				state_map[it.first] = DOWN;
			}
			if (it.second == RELEASED) {
				state_map[it.first] = UP;
			}
		}

		// Only states we can enter with here are DOWN or RELEASED.
		// So we can make some assumptions.
		for (auto it : key_map) {
			key_state state = state_map[it.first];
			int s = GLFW_RELEASE;
			for (input i : it.second) {
				// This is keyboard input.
				if (i.joy_id == -1) {
					s = glfwGetKey(window, i.button);
				}

				if (!s) continue;

				if (state == UP) {
					state = PRESSED;
					break;
				} else {
					state = DOWN;
					break;
				}
			}

			if (s == GLFW_RELEASE && state == DOWN) {
				state = RELEASED;
			}
			state_map[it.first] = state;
		}
	}

	bool is_down(std::string name) {
		auto s = state_map[name];
		return s == DOWN || s == PRESSED;
	}

	bool is_pressed(std::string name) {
		auto s = state_map[name];
		return s == PRESSED;
	}

	bool is_up(std::string name) {
		auto s = state_map[name];
		return s == RELEASED || s == UP;
	}

	bool is_released(std::string name) {
		auto s = state_map[name];
		return s == RELEASED;
	}

	bool is_changed(std::string name) {
		auto s = state_map[name];
		return s == RELEASED || s == PRESSED;
	}
}
