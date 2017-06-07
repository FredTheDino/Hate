# Need this later for glew...
include (FindPkgConfig)

# GLOB the files
file (GLOB ENGINE_CODE "*.cpp" "*.h")

# Tell CMake this is a library
add_library (ENGINE STATIC ${ENGINE_CODE})

# Find the libraries that are requierd
find_package (OpenGL REQUIRED)
# Hopefully, this is legacy
# PKG_SEARCH_MODULE (GLEW REQUIRED glew)
# find_package (PkgConfig REQUIRED)
# pkg_search_module (GLFW REQUIRED glfw3)

# Hope for legacy
# include_directories (ENGINE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
# target_link_libraries (ENGINE ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

# Link the libs
include_directories   (ENGINE ${OPENGL_INCLUDE_DIR})
target_link_libraries (ENGINE ${OPENGL_LIBRARIES})

# Link OpenAL
include_directories (ENGINE "${CMAKE_SOURCE_DIR}/src/openal/include")
target_link_libraries (ENGINE ${OpenAL})

# Link GLEW
include_directories (ENGINE "${CMAKE_SOURCE_DIR}/src/glew/include")
target_link_libraries (ENGINE glew)

# Link GLFW
include_directories (ENGINE "${CMAKE_SOURCE_DIR}/src/glfw/include")
target_link_libraries (ENGINE glfw)
