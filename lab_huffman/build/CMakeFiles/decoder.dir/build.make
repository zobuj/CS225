# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/cs225/release-f22/release-f22/lab_huffman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/cs225/release-f22/release-f22/lab_huffman/build

# Include any dependencies generated for this target.
include CMakeFiles/decoder.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/decoder.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/decoder.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/decoder.dir/flags.make

CMakeFiles/decoder.dir/entry/decoder.cpp.o: CMakeFiles/decoder.dir/flags.make
CMakeFiles/decoder.dir/entry/decoder.cpp.o: ../entry/decoder.cpp
CMakeFiles/decoder.dir/entry/decoder.cpp.o: CMakeFiles/decoder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225/release-f22/release-f22/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/decoder.dir/entry/decoder.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/decoder.dir/entry/decoder.cpp.o -MF CMakeFiles/decoder.dir/entry/decoder.cpp.o.d -o CMakeFiles/decoder.dir/entry/decoder.cpp.o -c /workspaces/cs225/release-f22/release-f22/lab_huffman/entry/decoder.cpp

CMakeFiles/decoder.dir/entry/decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/decoder.dir/entry/decoder.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225/release-f22/release-f22/lab_huffman/entry/decoder.cpp > CMakeFiles/decoder.dir/entry/decoder.cpp.i

CMakeFiles/decoder.dir/entry/decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/decoder.dir/entry/decoder.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225/release-f22/release-f22/lab_huffman/entry/decoder.cpp -o CMakeFiles/decoder.dir/entry/decoder.cpp.s

# Object files for target decoder
decoder_OBJECTS = \
"CMakeFiles/decoder.dir/entry/decoder.cpp.o"

# External object files for target decoder
decoder_EXTERNAL_OBJECTS =

decoder: CMakeFiles/decoder.dir/entry/decoder.cpp.o
decoder: CMakeFiles/decoder.dir/build.make
decoder: src/libsrc.a
decoder: lib/libcs225.a
decoder: lib/liblodepng.a
decoder: CMakeFiles/decoder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/cs225/release-f22/release-f22/lab_huffman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable decoder"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/decoder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/decoder.dir/build: decoder
.PHONY : CMakeFiles/decoder.dir/build

CMakeFiles/decoder.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/decoder.dir/cmake_clean.cmake
.PHONY : CMakeFiles/decoder.dir/clean

CMakeFiles/decoder.dir/depend:
	cd /workspaces/cs225/release-f22/release-f22/lab_huffman/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/cs225/release-f22/release-f22/lab_huffman /workspaces/cs225/release-f22/release-f22/lab_huffman /workspaces/cs225/release-f22/release-f22/lab_huffman/build /workspaces/cs225/release-f22/release-f22/lab_huffman/build /workspaces/cs225/release-f22/release-f22/lab_huffman/build/CMakeFiles/decoder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/decoder.dir/depend

