# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Project_3_Related_Files.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project_3_Related_Files.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project_3_Related_Files.dir/flags.make

CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o: CMakeFiles/Project_3_Related_Files.dir/flags.make
CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o: ../p3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o -c /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/p3.cpp

CMakeFiles/Project_3_Related_Files.dir/p3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project_3_Related_Files.dir/p3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/p3.cpp > CMakeFiles/Project_3_Related_Files.dir/p3.cpp.i

CMakeFiles/Project_3_Related_Files.dir/p3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project_3_Related_Files.dir/p3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/p3.cpp -o CMakeFiles/Project_3_Related_Files.dir/p3.cpp.s

CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.requires:

.PHONY : CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.requires

CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.provides: CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.requires
	$(MAKE) -f CMakeFiles/Project_3_Related_Files.dir/build.make CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.provides.build
.PHONY : CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.provides

CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.provides.build: CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o


CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o: CMakeFiles/Project_3_Related_Files.dir/flags.make
CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o: ../simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o -c /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/simulation.cpp

CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/simulation.cpp > CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.i

CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/simulation.cpp -o CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.s

CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.requires:

.PHONY : CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.requires

CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.provides: CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.requires
	$(MAKE) -f CMakeFiles/Project_3_Related_Files.dir/build.make CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.provides.build
.PHONY : CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.provides

CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.provides.build: CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o


# Object files for target Project_3_Related_Files
Project_3_Related_Files_OBJECTS = \
"CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o" \
"CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o"

# External object files for target Project_3_Related_Files
Project_3_Related_Files_EXTERNAL_OBJECTS =

Project_3_Related_Files: CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o
Project_3_Related_Files: CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o
Project_3_Related_Files: CMakeFiles/Project_3_Related_Files.dir/build.make
Project_3_Related_Files: CMakeFiles/Project_3_Related_Files.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Project_3_Related_Files"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project_3_Related_Files.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project_3_Related_Files.dir/build: Project_3_Related_Files

.PHONY : CMakeFiles/Project_3_Related_Files.dir/build

CMakeFiles/Project_3_Related_Files.dir/requires: CMakeFiles/Project_3_Related_Files.dir/p3.cpp.o.requires
CMakeFiles/Project_3_Related_Files.dir/requires: CMakeFiles/Project_3_Related_Files.dir/simulation.cpp.o.requires

.PHONY : CMakeFiles/Project_3_Related_Files.dir/requires

CMakeFiles/Project_3_Related_Files.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project_3_Related_Files.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project_3_Related_Files.dir/clean

CMakeFiles/Project_3_Related_Files.dir/depend:
	cd /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug /Users/bingcheng/Desktop/VE280/proj3/Project-3-Related-Files/cmake-build-debug/CMakeFiles/Project_3_Related_Files.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project_3_Related_Files.dir/depend

