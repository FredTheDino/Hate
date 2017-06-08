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
#include_directories (GAME "${CMAKE_SOURCE_DIR}/src/include")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
 	INCLUDE_DIRECTORIES(GAME "${CMAKE_SOURCE_DIR}/src/include")
 
 	MESSAGE ("Windows detected")
 	MESSAGE(${CMAKE_SOURCE_DIR})
 
 	FILE(GLOB LIBRARIES "${CMAKE_SOURCE_DIR}/lib/x64/*.lib")
 
 	target_link_libraries(GAME ${LIBRARIES})
 
endif()
