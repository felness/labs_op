# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fltww/lab1_op/lab5-7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fltww/lab1_op/lab5-7/build

# Include any dependencies generated for this target.
include CMakeFiles/calculation_node.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/calculation_node.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/calculation_node.dir/flags.make

CMakeFiles/calculation_node.dir/calculation_node.cpp.o: CMakeFiles/calculation_node.dir/flags.make
CMakeFiles/calculation_node.dir/calculation_node.cpp.o: ../calculation_node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fltww/lab1_op/lab5-7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/calculation_node.dir/calculation_node.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calculation_node.dir/calculation_node.cpp.o -c /home/fltww/lab1_op/lab5-7/calculation_node.cpp

CMakeFiles/calculation_node.dir/calculation_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculation_node.dir/calculation_node.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fltww/lab1_op/lab5-7/calculation_node.cpp > CMakeFiles/calculation_node.dir/calculation_node.cpp.i

CMakeFiles/calculation_node.dir/calculation_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculation_node.dir/calculation_node.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fltww/lab1_op/lab5-7/calculation_node.cpp -o CMakeFiles/calculation_node.dir/calculation_node.cpp.s

# Object files for target calculation_node
calculation_node_OBJECTS = \
"CMakeFiles/calculation_node.dir/calculation_node.cpp.o"

# External object files for target calculation_node
calculation_node_EXTERNAL_OBJECTS =

calculation_node: CMakeFiles/calculation_node.dir/calculation_node.cpp.o
calculation_node: CMakeFiles/calculation_node.dir/build.make
calculation_node: CMakeFiles/calculation_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fltww/lab1_op/lab5-7/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable calculation_node"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calculation_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/calculation_node.dir/build: calculation_node

.PHONY : CMakeFiles/calculation_node.dir/build

CMakeFiles/calculation_node.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/calculation_node.dir/cmake_clean.cmake
.PHONY : CMakeFiles/calculation_node.dir/clean

CMakeFiles/calculation_node.dir/depend:
	cd /home/fltww/lab1_op/lab5-7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fltww/lab1_op/lab5-7 /home/fltww/lab1_op/lab5-7 /home/fltww/lab1_op/lab5-7/build /home/fltww/lab1_op/lab5-7/build /home/fltww/lab1_op/lab5-7/build/CMakeFiles/calculation_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/calculation_node.dir/depend

