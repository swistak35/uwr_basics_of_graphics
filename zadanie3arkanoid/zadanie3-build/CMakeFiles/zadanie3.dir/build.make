# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3-build

# Include any dependencies generated for this target.
include CMakeFiles/zadanie3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zadanie3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zadanie3.dir/flags.make

CMakeFiles/zadanie3.dir/main.cpp.o: CMakeFiles/zadanie3.dir/flags.make
CMakeFiles/zadanie3.dir/main.cpp.o: /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/zadanie3.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/zadanie3.dir/main.cpp.o -c /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3/main.cpp

CMakeFiles/zadanie3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zadanie3.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3/main.cpp > CMakeFiles/zadanie3.dir/main.cpp.i

CMakeFiles/zadanie3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zadanie3.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3/main.cpp -o CMakeFiles/zadanie3.dir/main.cpp.s

CMakeFiles/zadanie3.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/zadanie3.dir/main.cpp.o.requires

CMakeFiles/zadanie3.dir/main.cpp.o.provides: CMakeFiles/zadanie3.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/zadanie3.dir/build.make CMakeFiles/zadanie3.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/zadanie3.dir/main.cpp.o.provides

CMakeFiles/zadanie3.dir/main.cpp.o.provides.build: CMakeFiles/zadanie3.dir/main.cpp.o

# Object files for target zadanie3
zadanie3_OBJECTS = \
"CMakeFiles/zadanie3.dir/main.cpp.o"

# External object files for target zadanie3
zadanie3_EXTERNAL_OBJECTS =

zadanie3: CMakeFiles/zadanie3.dir/main.cpp.o
zadanie3: CMakeFiles/zadanie3.dir/build.make
zadanie3: CMakeFiles/zadanie3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable zadanie3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zadanie3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zadanie3.dir/build: zadanie3
.PHONY : CMakeFiles/zadanie3.dir/build

CMakeFiles/zadanie3.dir/requires: CMakeFiles/zadanie3.dir/main.cpp.o.requires
.PHONY : CMakeFiles/zadanie3.dir/requires

CMakeFiles/zadanie3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zadanie3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zadanie3.dir/clean

CMakeFiles/zadanie3.dir/depend:
	cd /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3 /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3 /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3-build /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3-build /home/swistak35/Projekty/uwr_basics_of_graphics/zadanie3arkanoid/zadanie3-build/CMakeFiles/zadanie3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zadanie3.dir/depend
