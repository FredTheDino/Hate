#include "input.h"
#include "loader.h"
#include "core.h"
#include "clock.h"
#include "misc.h"
#include <map>
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

	std::map<std::string, std::vector<input>> key_map;
	std::map<std::string, key_state> state_map;
	long input_map_edit_time = 0;
	float reload_timer = 0;

	void reload_input_map(std::string path, bool use_timer) {
		const float time_to_reload = 0.2f;

		long edit_time = get_edit_time(path);
		if (input_map_edit_time != edit_time) {
			input_map_edit_time = edit_time;
			if (use_timer) {
				reload_timer = 0;
			} else {
				key_map.clear();
				state_map.clear();
				load_input_map(path);
			}
		}

		if (reload_timer > 1 + time_to_reload) return;

		reload_timer += get_clock_delta();
		if (reload_timer > time_to_reload) {
			reload_timer += 1;

			key_map.clear();
			state_map.clear();
			load_input_map(path);
		}
	}

	// Input format:
	// name [K/J] (joy_id) button
	void load_input_map(std::string path) {
		std::ifstream file;
		file.open(get_real_path(path));

		if (file) {
			input_map_edit_time = get_edit_time(path);
		} else {
			// Something went wrong.
		}
		
		std::string line;
		while (std::getline(file, line)) {
			
			// Check that it isn't a comment
			if (line[0] == '#') continue;

			auto parse = split(line, ' ');
			auto name = parse[0];
			input i;
			if (parse[1] == "K") {
				// Make sure they're uppercase
				for (auto& c : parse[2]) { c = toupper(c); }
				
				// Is it a single key?
				if (parse[2].size() == 1) {
					i.button = toupper(parse[2][0]);
				} else {
					// It's a special key
					if (parse[2] == "SPACE") {
						i.button = GLFW_KEY_SPACE;
					} else if (parse[2] == "UP") {
						i.button = GLFW_KEY_UP;
					} else if (parse[2] == "DOWN") {
						i.button = GLFW_KEY_DOWN;
					} else if (parse[2] == "LEFT") {
						i.button = GLFW_KEY_LEFT;
					} else if (parse[2] == "RIGHT") {
						i.button = GLFW_KEY_RIGHT;
					} else if (parse[2] == "LEFT_SHIFT") {
						i.button = GLFW_KEY_LEFT_SHIFT;
					} else if (parse[2] == "RIGHT_SHIFT") {
						i.button = GLFW_KEY_RIGHT_SHIFT;
					} else if (parse[2] == "RIGHT_CONTROL") {
						i.button = GLFW_KEY_RIGHT_CONTROL;
					} else if (parse[2] == "LEFT_CONTROL") {
						i.button = GLFW_KEY_LEFT_CONTROL;
					} else if (parse[2] == "RIGHT_SUPER") {
						i.button = GLFW_KEY_RIGHT_SUPER;
					} else if (parse[2] == "LEFT_SUPER") {
						i.button = GLFW_KEY_LEFT_SUPER;
					} 
				}
			} else if (parse[1] == "J") {
				// TODO: Do parsing for the input.
			}

			auto it = key_map.find(name);
			if (it == key_map.end()) {
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
