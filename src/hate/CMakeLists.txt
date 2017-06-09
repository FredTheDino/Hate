# Need this later for glew...
include (FindPkgConfig)

# GLOB the files
file (GLOB ENGINE_CODE "*.cpp" "*.h")

# Tell CMake this is a library
add_library (ENGINE STATIC ${ENGINE_CODE})

# Find the libraries that are requierd
find_package (OpenGL REQUIRED)
include_directories   (ENGINE ${OPENGL_INCLUDE_DIR})
target_link_libraries (ENGINE ${OPENGL_LIBRARIES})


target_link_libraries(ENGINE OpenAL)

# Hopefully, this is legacy
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	INCLUDE_DIRECTORIES(ENGINE "${CMAKE_SOURCE_DIR}/src/include")

	MESSAGE ("Windows detected")
	MESSAGE(${CMAKE_SOURCE_DIR})

	FILE(GLOB LIBRARIES "${CMAKE_SOURCE_DIR}/lib/x64/*.lib")

	target_link_libraries(ENGINE ${LIBRARIES})

else()
	INCLUDE(FindPkgConfig)

	PKG_SEARCH_MODULE(GLFW REQUIRED glfw3)
	PKG_SEARCH_MODULE(GLEW REQUIRED glew)

	INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(ENGINE ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
endif()
