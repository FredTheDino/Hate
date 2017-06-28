#include "shader.h"
#include "loader.h"
#include "clock.h"
#include <string>
#include <fstream>

namespace hate {
	bool check_glsl_error(GLuint target, GLenum flag, const char* message, bool is_program = false) {
		GLint success = 1;
		if (is_program) {
			glGetProgramiv(target, flag, &success);
		} else {
			glGetShaderiv(target, flag, &success);
		}

		if (success == GL_FALSE) {
			GLchar error[512];

			GLsizei length = 0;
			if (is_program) {
				glGetProgramInfoLog(target, sizeof(error), &length, error);
			} else {
				glGetShaderInfoLog(target, sizeof(error), &length, error);
			}

			printf("(%s): %s\n", message, error);
			return false;
		}
		return true;
	}

	GLuint compile_shader(std::string const& source, GLenum shader_type) {
		GLuint shader = glCreateShader(shader_type);
		if (!shader) {
			return -1;
		}

		const GLchar* src = (GLchar*) source.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		if (!check_glsl_error(shader, GL_COMPILE_STATUS, "Shader Compilation")) {
			glDeleteShader(shader); // Don't leak the shader.
			return -1;
		}
		return shader;
	}

	GLuint link_program(GLuint vertex_shader, GLuint fragment_shader) {
		GLuint program = glCreateProgram();

		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);

		if(!check_glsl_error(program, GL_LINK_STATUS, "Program Linking", true)) {
			//We don't need the program anymore.
			glDeleteProgram(program);

			return -1;
		}

		glDetachShader(program, vertex_shader);
		glDetachShader(program, fragment_shader);

		return program;
	}

	void read_file_to_buffer(std::string path, std::vector<GLchar>* buffer) {
		std::string real_path = get_real_path(path);
		std::ifstream file(real_path);

		if (!file) {
			printf("Error loading file: %s\n", path.c_str());
			return;
		}

		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		buffer->resize(length);

		file.read(&(*buffer)[0], length);
		file.close();
		
		// We need this, since C-strings are 
		// null terminated and OpenGL is a C api.
		buffer->push_back('\0');
	}

	// @Hack: We currently assume target and replacement is 
	// the same size, might wanna fix that if we want to 
	// make this public.
	bool find_and_replace(std::vector<GLchar>* source, std::string target, std::string replacement) {
		int edit_location = 0;
		for (; edit_location < source->size(); edit_location++) {
			// We found the start, atleast we think so.
			bool found = true;
			for (int i = 0; i < target.size(); i++) {
				if ((*source)[edit_location + i] != target[i]) {
					// Okay, we actually found the start.
					found = false;
					break;
				}
			}
			if (found)
				break;
		}

		if (edit_location == source->size() - 1) {
			// We didn't find the target.
			return false;
		}

		for (int i = 0; i < replacement.size(); i++) {
			(*source)[edit_location + i] = replacement[i];
		}
		return true;
	}

	Shader load_shader(std::string path) {
		std::vector<GLchar> source;
		read_file_to_buffer(path, &source);
		Shader s;
		s.path = path;
		s.program = -1;
	
		GLuint vert_shader = compile_shader(&source[0], GL_VERTEX_SHADER);
		if (vert_shader == -1) {
			return s;
		}

		// Converts the fragment shader to the vertex shader.
		// @Hack: The target and replace has to be the same size.
		find_and_replace(&source, std::string("VERT"), std::string("FRAG"));

		GLuint frag_shader = compile_shader(&source[0], GL_FRAGMENT_SHADER);
		if (frag_shader == -1) {
			glDeleteShader(vert_shader);
			return s;
		}

		// We succeeded with compiling everything.
		GLuint program = link_program(vert_shader, frag_shader);
		if (program == -1) {
			//Don't leak shaders.
			glDeleteShader(vert_shader);
			glDeleteShader(frag_shader);
			return s;
		}
		s.program = program;

	#ifdef DEBUG
		s.edit_time = get_edit_time(path);
	#endif

		return s;
	}

	void delete_shader(Shader s) {
		glDeleteProgram(s.program);
	}

	void use_shader(Shader& s) {
		glUseProgram(s.program);
		float t = glfwGetTime();
		glUniform1f(0, t);
	}

	void recompile_shader(Shader* s, bool use_timer) {
		const float time_to_compile = 0.2f;

		long edit_time = get_edit_time(s->path);
		if (edit_time != s->edit_time) {
			s->edit_time = edit_time;
			if (use_timer) {
				s->timer = 0;
			} else {
				Shader _s = load_shader(s->path);
				if (_s.program != -1) {
					delete_shader(*s);
					*s = _s;
				}

			}
		}

		if (s->timer > 1 + time_to_compile) return;

		s->timer += get_clock_delta();
		if (s->timer > time_to_compile) {
			s->timer++;
			Shader _s = load_shader(s->path);
			if (_s.program != -1) {
				delete_shader(*s);
				*s = _s;
			}
		}
	}
}
