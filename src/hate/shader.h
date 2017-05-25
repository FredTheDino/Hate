#pragma once
#include <unordered_map>
#include "platform.h"

namespace hate {
	/**
	 * This is the master shader, which
	 * everything goes through to get 
	 * renderd. 
	 *
	 * This engine is opted for using a 
	 * master shader that does almost 
	 * everything and it does it fast.
	 */
	class Shader {
		public:
			// Creates a new Shader.
			// This assumes the fragment and
			// vertex shader is in the same file.
			Shader(String path);
		
			// Uninitalises the shader.
			~Shader();

			// Binds the shader for use.
			void bind();

#ifdef DEBUG
			// Checks if the shader is dirty and recompiles 
			// if this is the case. If the compilation
			// doesn't succseed, it pretends the shader
			// isn't dirty and runs with that is has.
			void recompileIfChanged();

			// If the engine should recompile the next time.
			double recompileTimer = 0;
			
			// The last time the file was changed.
			long lastTimeStamp = 0;
#endif
			/**
			 * Gets the location of the uniform with the specified name.
			 *
			 * If nothing is found, -1 is returned.
			 */
			int location(std::string name);
		private:
			// A list of the uniforms and thier locations.
			std::unordered_map<std::string, int> uniforms;

			// The program.
			GLuint program;

			// Compiles the shader
			GLuint compile();

			// Path to the file
			std::string path;
	};
}
