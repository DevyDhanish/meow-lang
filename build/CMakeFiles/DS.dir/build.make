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
CMAKE_SOURCE_DIR = /home/dan/Coding/MeowLan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dan/Coding/MeowLan/build

# Include any dependencies generated for this target.
include CMakeFiles/DS.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DS.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DS.dir/flags.make

CMakeFiles/DS.dir/src/DS/list.c.o: CMakeFiles/DS.dir/flags.make
CMakeFiles/DS.dir/src/DS/list.c.o: ../src/DS/list.c
CMakeFiles/DS.dir/src/DS/list.c.o: CMakeFiles/DS.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dan/Coding/MeowLan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DS.dir/src/DS/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/DS.dir/src/DS/list.c.o -MF CMakeFiles/DS.dir/src/DS/list.c.o.d -o CMakeFiles/DS.dir/src/DS/list.c.o -c /home/dan/Coding/MeowLan/src/DS/list.c

CMakeFiles/DS.dir/src/DS/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS.dir/src/DS/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dan/Coding/MeowLan/src/DS/list.c > CMakeFiles/DS.dir/src/DS/list.c.i

CMakeFiles/DS.dir/src/DS/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS.dir/src/DS/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dan/Coding/MeowLan/src/DS/list.c -o CMakeFiles/DS.dir/src/DS/list.c.s

# Object files for target DS
DS_OBJECTS = \
"CMakeFiles/DS.dir/src/DS/list.c.o"

# External object files for target DS
DS_EXTERNAL_OBJECTS =

libDS.a: CMakeFiles/DS.dir/src/DS/list.c.o
libDS.a: CMakeFiles/DS.dir/build.make
libDS.a: CMakeFiles/DS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dan/Coding/MeowLan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libDS.a"
	$(CMAKE_COMMAND) -P CMakeFiles/DS.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DS.dir/build: libDS.a
.PHONY : CMakeFiles/DS.dir/build

CMakeFiles/DS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DS.dir/clean

CMakeFiles/DS.dir/depend:
	cd /home/dan/Coding/MeowLan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dan/Coding/MeowLan /home/dan/Coding/MeowLan /home/dan/Coding/MeowLan/build /home/dan/Coding/MeowLan/build /home/dan/Coding/MeowLan/build/CMakeFiles/DS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DS.dir/depend
