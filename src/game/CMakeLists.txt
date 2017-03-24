# Find those files!
file (GLOB GAME_FILES "*.cpp" "*.h")

# Make the exectuable
add_executable (GAME "${GAME_FILES}")

# Include the Hate lib
include_directories (GAME "${CMAKE_SOURCE_DIR}/src")

# Link this with the engine
target_link_libraries (GAME ENGINE)

