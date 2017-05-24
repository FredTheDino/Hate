#include <stdio.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include "shader.h"
#include "loader.h"
#include "hate.h"

namespace hate {

	bool checkError(GLuint target, GLenum flag, const char* prefix, bool isProgram) {
		GLint successfull = 0;
		if (isProgram) {
			glGetProgramiv(target, flag, &successfull);
		} else {
			glGetShaderiv(target, flag, &successfull);
		}
		if (successfull == GL_FALSE) {
			GLchar error[1024] = {0};

			GLsizei length = 0;
			if (isProgram) {
				glGetProgramInfoLog(target, sizeof(error), &length, error);
			} else {
				glGetShaderInfoLog(target, sizeof(error), &length, error);
			}

			printf("(%s): %s\n", prefix, error + 1);
			return false;
		}
		return true;
	}

	GLuint compileShader(String source, bool vertex) {
		GLuint shader = glCreateShader(vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		const GLchar* src = source.c_str();
		int length = source.size();
		glShaderSource(shader, 1, &src, &length);

		if (!checkError(shader, GL_COMPILE_STATUS, "Shader Compilation", false)) {
			glDeleteShader(shader); // Don't leak the shader.
			return -1;
		}

		return shader;
	}

	GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader) {
		GLuint program = glCreateProgram();

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		if(!checkError(program, GL_LINK_STATUS, "Program Linking", true)) {
			//We don't need the program anymore.
			glDeleteProgram(program);
			//Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return -1;
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		return program;
	}

	void readFileToBuffer(std::string& path, std::vector<GLchar>* buffer) {
		// Read the entire file into a stream.
		auto file = Hate::LOADER->openText(path);
		file->seekg(0, std::ios::end);
		auto length = file->tellg();
		file->seekg(0, std::ios::beg);

		buffer->resize(length);

		file->read(&(*buffer)[0], length);
		file->close();
		delete file;
	}

	void toFragmentShader(std::vector<GLchar>* buffer) {
		// Replace "VERT" with "FRAG"
		// Assumes the first big V is the begning of the VERT define
		// @Hack
		int start = 0;
		for (int i = 0; i < buffer->size(); i++) {
			if ((*buffer)[i] == 'V') {
				start = i;
			}
		}

		GLchar diff[4] = {'F', 'R', 'A', 'G'};
		for (int i = 0; i < sizeof(diff); i++) {
			(*buffer)[start + i] = diff[i];
		}
	}

	GLuint Shader::compile() {
		std::vector<GLchar> buffer;
		readFileToBuffer(path, &buffer);

		GLuint vertexShader = compileShader(&buffer[0], true);

		toFragmentShader(&buffer);

		GLuint fragmentShader = compileShader(&buffer[0], false);

		if (vertexShader == -1 || fragmentShader == -1) throw 1;

		GLuint program = linkProgram(vertexShader, fragmentShader);
		if (program == -1) throw 2;

		glValidateProgram(program);
		if (!checkError(program, GL_VALIDATE_STATUS, "Validation Error", true)) throw 3;

		return program;
	}

	Shader::Shader(String path) {
		this->path = path;

#ifdef DEBUG
		// Initalize the timestamp!
		struct stat attr;
		stat(path.c_str(), &attr);
		lastTimeStamp = attr.st_mtime;
#endif
		program = compile();
	}

	Shader::~Shader() {
		glDeleteProgram(program);
	}

	void Shader::bind() {
		glUseProgram(program);
	}


#ifdef DEBUG
	void Shader::recompileIfChanged() {
		struct stat attr;
		stat(path.c_str(), &attr);
		long newTimeStamp = attr.st_mtime;

		if (lastTimeStamp != newTimeStamp) {
			lastTimeStamp = newTimeStamp;
			// We should recompile everything!
			GLuint newProgram;
			try {
				newProgram = compile();
			} catch (int e) {
				return;
			}

			glDeleteProgram(program);
			
			program = newProgram;
		}
	}
#endif
}
