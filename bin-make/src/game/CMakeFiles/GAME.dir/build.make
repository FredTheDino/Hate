# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Dev\C++\Hate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Dev\C++\Hate\bin-make

# Include any dependencies generated for this target.
include src/game/CMakeFiles/GAME.dir/depend.make

# Include the progress variables for this target.
include src/game/CMakeFiles/GAME.dir/progress.make

# Include the compile flags for this target's objects.
include src/game/CMakeFiles/GAME.dir/flags.make

src/game/CMakeFiles/GAME.dir/main.cpp.obj: src/game/CMakeFiles/GAME.dir/flags.make
src/game/CMakeFiles/GAME.dir/main.cpp.obj: src/game/CMakeFiles/GAME.dir/includes_CXX.rsp
src/game/CMakeFiles/GAME.dir/main.cpp.obj: ../src/game/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Dev\C++\Hate\bin-make\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/game/CMakeFiles/GAME.dir/main.cpp.obj"
	cd /d E:\Dev\C++\Hate\bin-make\src\game && C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\GAME.dir\main.cpp.obj -c E:\Dev\C++\Hate\src\game\main.cpp

src/game/CMakeFiles/GAME.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GAME.dir/main.cpp.i"
	cd /d E:\Dev\C++\Hate\bin-make\src\game && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Dev\C++\Hate\src\game\main.cpp > CMakeFiles\GAME.dir\main.cpp.i

src/game/CMakeFiles/GAME.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GAME.dir/main.cpp.s"
	cd /d E:\Dev\C++\Hate\bin-make\src\game && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Dev\C++\Hate\src\game\main.cpp -o CMakeFiles\GAME.dir\main.cpp.s

src/game/CMakeFiles/GAME.dir/main.cpp.obj.requires:

.PHONY : src/game/CMakeFiles/GAME.dir/main.cpp.obj.requires

src/game/CMakeFiles/GAME.dir/main.cpp.obj.provides: src/game/CMakeFiles/GAME.dir/main.cpp.obj.requires
	$(MAKE) -f src\game\CMakeFiles\GAME.dir\build.make src/game/CMakeFiles/GAME.dir/main.cpp.obj.provides.build
.PHONY : src/game/CMakeFiles/GAME.dir/main.cpp.obj.provides

src/game/CMakeFiles/GAME.dir/main.cpp.obj.provides.build: src/game/CMakeFiles/GAME.dir/main.cpp.obj


# Object files for target GAME
GAME_OBJECTS = \
"CMakeFiles/GAME.dir/main.cpp.obj"

# External object files for target GAME
GAME_EXTERNAL_OBJECTS =

src/game/GAME.exe: src/game/CMakeFiles/GAME.dir/main.cpp.obj
src/game/GAME.exe: src/game/CMakeFiles/GAME.dir/build.make
src/game/GAME.exe: src/hate/libENGINE.a
src/game/GAME.exe: ../lib/x64/glew32.lib
src/game/GAME.exe: ../lib/x64/glew32s.lib
src/game/GAME.exe: ../lib/x64/glfw3.lib
src/game/GAME.exe: ../lib/x64/glfw3dll.lib
src/game/GAME.exe: ../lib/x64/glew32.lib
src/game/GAME.exe: ../lib/x64/glew32s.lib
src/game/GAME.exe: ../lib/x64/glfw3.lib
src/game/GAME.exe: ../lib/x64/glfw3dll.lib
src/game/GAME.exe: src/openal/libOpenAL32.dll.a
src/game/GAME.exe: src/game/CMakeFiles/GAME.dir/linklibs.rsp
src/game/GAME.exe: src/game/CMakeFiles/GAME.dir/objects1.rsp
src/game/GAME.exe: src/game/CMakeFiles/GAME.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Dev\C++\Hate\bin-make\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GAME.exe"
	cd /d E:\Dev\C++\Hate\bin-make\src\game && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GAME.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/game/CMakeFiles/GAME.dir/build: src/game/GAME.exe

.PHONY : src/game/CMakeFiles/GAME.dir/build

src/game/CMakeFiles/GAME.dir/requires: src/game/CMakeFiles/GAME.dir/main.cpp.obj.requires

.PHONY : src/game/CMakeFiles/GAME.dir/requires

src/game/CMakeFiles/GAME.dir/clean:
	cd /d E:\Dev\C++\Hate\bin-make\src\game && $(CMAKE_COMMAND) -P CMakeFiles\GAME.dir\cmake_clean.cmake
.PHONY : src/game/CMakeFiles/GAME.dir/clean

src/game/CMakeFiles/GAME.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Dev\C++\Hate E:\Dev\C++\Hate\src\game E:\Dev\C++\Hate\bin-make E:\Dev\C++\Hate\bin-make\src\game E:\Dev\C++\Hate\bin-make\src\game\CMakeFiles\GAME.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/game/CMakeFiles/GAME.dir/depend

