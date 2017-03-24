# Need this later for glew...
include (FindPkgConfig)

# GLOB the files
file (GLOB ENGINE_CODE "*.cpp" "*.h")

# Tell CMake this is a library
add_library (ENGINE ${ENGINE_CODE})

# Find the libraries that are requierd
PKG_SEARCH_MODULE (GLEW REQUIRED glew)
find_package ("OpenGL" REQUIRED)
find_package (glfw3 3.2 REQUIRED)

# Link the libs
include_directories (ENGINE ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
target_link_libraries(ENGINE ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
