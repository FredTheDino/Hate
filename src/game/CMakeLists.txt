# Find those files!
file (GLOB GAME_FILES "*.cpp" "*.h")

# Make the exectuable
add_executable (GAME "${GAME_FILES}")

# Include the Hate lib
include_directories (GAME "${CMAKE_SOURCE_DIR}/src/hate")

# Link this with the engine
target_link_libraries (GAME ENGINE)

# Link the libs
include_directories   (GAME ${OPENGL_INCLUDE_DIR})
# Link OpenAL
include_directories (GAME "${CMAKE_SOURCE_DIR}/src/openal/include")
# Link GLEW
include_directories (GAME "${CMAKE_SOURCE_DIR}/src/glew/include")
# Link GLFW
include_directories (GAME "${CMAKE_SOURCE_DIR}/src/glfw/include")

