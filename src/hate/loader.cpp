#include "loader.h"
#include <fstream>
#include <sys/stat.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef _WIN32
// Way to go windows!
#include "basic.h"
#include "clock.h"
#endif

#define MAX_DEPTH 10

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
					assert(false);
				}
			}
		}
	}

	texture load_texture(std::string path, bool linear_filtering, GLenum wrap_style, bool use_mipmaps) {	
		int w, h, comp;
		unsigned char* pixels = stbi_load(get_real_path(path).c_str(), &w, &h, &comp, 0);

		GLuint tex;
		glGenTextures(1, &tex);

		glBindTexture(GL_TEXTURE_2D, tex);

		GLenum filter = linear_filtering ? GL_LINEAR : GL_NEAREST;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_style);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_style);

		if (use_mipmaps) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		GLenum format = GL_RGBA;
		if (comp == 1) {
			format = GL_RED;
		} else if (comp == 2) {
			format = GL_RED | GL_GREEN;
		} else if (comp == 3) {
			format = GL_RGB;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, format, GL_UNSIGNED_BYTE, pixels);

		texture t;
		t.tex_id = tex;
		t.w = w;
		t.h = h;

		return t;
	}

	void delete_texture(texture t) {
		glDeleteTextures(1, &t.tex_id);
	}

	long get_edit_time(std::string path) {
#ifdef __linux__
		struct stat attr;
    	stat(get_real_path(path).c_str(), &attr);
		return attr.st_mtime;
#elif _WIN32
		// On windows, we reload them every N seconds, because I have a life.
#define RELOAD_TIME 5
		return floor(get_clock_time() / RELOAD_TIME);
#endif
	}

	std::string get_real_path(std::string path) {
		return os_path + path;
	}
}
