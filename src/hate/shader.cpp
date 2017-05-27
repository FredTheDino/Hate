#include <stdio.h>
#include <utility>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include "shader.h"
#include "loader.h"
#include "hate.h"

namespace hate {

	bool checkError(GLuint target, GLenum flag, const char* prefix, bool isProgram = false) {
		GLint success = 1;
		if (isProgram) {
			glGetProgramiv(target, flag, &success);
		} else {
			glGetShaderiv(target, flag, &success);
		}

		if (success == GL_FALSE) {
			GLchar error[512];

			GLsizei length = 0;
			if (isProgram) {
				glGetProgramInfoLog(target, sizeof(error), &length, error);
			} else {
				glGetShaderInfoLog(target, sizeof(error), &length, error);
			}

			printf("(%s): %s\n", prefix, error);
			return true;
		}
		return false;
	}

	GLuint compileShader(String source, bool vertex) {
		GLuint shader = glCreateShader(vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
		if (!shader) {
			printf("Cannot allocate shader.");
			return -1;
		}

		const GLchar* src = (GLchar*) source.c_str();
		glShaderSource(shader, 1, &src, NULL);

		glCompileShader(shader);

		if (checkError(shader, GL_COMPILE_STATUS, "Shader Compilation")) {
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

		if(checkError(program, GL_LINK_STATUS, "Program Linking", true)) {
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
		
		// The buffer read isn't null terminated, but it is now.
		buffer->push_back('\0');
	}

	void toFragmentShader(std::vector<GLchar>* buffer) {
		// Replace "VERT" with "FRAG"
		// Assumes the first big V is the begning of the VERT define
		// @Hack
		int start = 0;
		for (int i = 0; i < buffer->size(); i++) {
			if ((*buffer)[i] == 'V') {
				start = i;
				break;
			}
		}

		GLchar diff[4] = {'F', 'R', 'A', 'G'};
		for (int i = 0; i < sizeof(diff); i++) {
			(*buffer)[start + i] = diff[i];
		}
	}

	std::unordered_map<std::string, int> checkUniforms(GLuint program) {
		// Gets the number of uniforms
		GLint count = 0;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

		std::unordered_map<std::string, int> uniforms;

		for (int i = 0; i < count; i++) {
			char name[512];
			GLenum type;
			glGetActiveUniform(program, (GLuint)i, sizeof(name), nullptr, nullptr, &type, name);
			std::string s(name, 0, sizeof(name));
			uniforms.insert(std::make_pair(s, i));
		}
		return uniforms;
	}

	int Shader::location(std::string name) {
		auto location = uniforms.find(name);
		if (location != uniforms.end()) {
			return location->second;
		}
		return -1;
	}

	GLuint Shader::compile() {
		std::vector<GLchar> buffer;
		readFileToBuffer(path, &buffer);

		GLuint vertexShader = compileShader(&buffer[0], true);
		if (vertexShader == -1) throw 1;

		toFragmentShader(&buffer);

		GLuint fragmentShader = compileShader(&buffer[0], false);
		if (fragmentShader == -1) throw 1;

		GLuint program = linkProgram(vertexShader, fragmentShader);
		if (program == -1) throw 2;

		glValidateProgram(program);
		if (checkError(program, GL_VALIDATE_STATUS, "Validation Error", true)) throw 3;

		return program;
	}

#ifdef DEBUG
	long lastEditTime(std::string path) {
		struct stat attr;
		stat(Hate::LOADER->getRealPath(path).c_str(), &attr);
		return attr.st_mtime;
	}
#endif

	Shader::Shader(String path) {

#ifdef DEBUG
		lastTimeStamp = lastEditTime(path);
#endif

		this->path = path;
		program = compile();
		uniforms = checkUniforms(program);
	}

	Shader::~Shader() {
		glDeleteProgram(program);
	}

	void Shader::bind() {
		glUseProgram(program);
		glUniform1f(location("t"), Hate::CLOCK->getTime());

		Mat4 p = Hate::CAMERA->getProjection();
		glUniformMatrix4fv(location("projection"), &p._01 - &p._00, GL_TRUE, &p._00);
		Mat4 w = Hate::CAMERA->getWorld();
		glUniformMatrix4fv(location("world"), &w._01 - &w._00, GL_FALSE, &w._00);
	}


#ifdef DEBUG
	void Shader::recompileIfChanged() {
		// Check if the timestamp has changed
		long timeStamp = lastEditTime(path);

		if (lastTimeStamp != timeStamp) {
			lastTimeStamp = timeStamp;
			recompileTimer = 0;
			return;
		}

		recompileTimer += Hate::CLOCK->getDelta();
		float timeToRecompile = 0.1f;
		if (recompileTimer < timeToRecompile || 1 + timeToRecompile < recompileTimer) return;
		recompileTimer++;

		// We should recompile everything!
		printf("Recompiling shader...\n");
		GLuint newProgram;
		try {
			newProgram = compile();
		} catch (int e) {
			timeToRecompile = 0;
			printf("Failed to recompile shader (error: %d)\n", e);
			return;
		} catch(...) {
			timeToRecompile = 0;
			printf("Unknown error loading shader...\n");
			return;
		}

		glDeleteProgram(program);
		program = newProgram;
	}
#endif
}
