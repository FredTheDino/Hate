# Need this later for glew...
include (FindPkgConfig)

# GLOB the files
file (GLOB ENGINE_CODE "*.cpp" "*.h")

# Tell CMake this is a library
add_library (ENGINE ${ENGINE_CODE})

# Find the libraries that are requierd
PKG_SEARCH_MODULE (GLEW REQUIRED glew)
find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)

# Link the libs
include_directories (ENGINE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
target_link_libraries (ENGINE ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
