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
include CMakeFiles/lexer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lexer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lexer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lexer.dir/flags.make

CMakeFiles/lexer.dir/src/lexer/lexer.c.o: CMakeFiles/lexer.dir/flags.make
CMakeFiles/lexer.dir/src/lexer/lexer.c.o: ../src/lexer/lexer.c
CMakeFiles/lexer.dir/src/lexer/lexer.c.o: CMakeFiles/lexer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dan/Coding/MeowLan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lexer.dir/src/lexer/lexer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lexer.dir/src/lexer/lexer.c.o -MF CMakeFiles/lexer.dir/src/lexer/lexer.c.o.d -o CMakeFiles/lexer.dir/src/lexer/lexer.c.o -c /home/dan/Coding/MeowLan/src/lexer/lexer.c

CMakeFiles/lexer.dir/src/lexer/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lexer.dir/src/lexer/lexer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dan/Coding/MeowLan/src/lexer/lexer.c > CMakeFiles/lexer.dir/src/lexer/lexer.c.i

CMakeFiles/lexer.dir/src/lexer/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lexer.dir/src/lexer/lexer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dan/Coding/MeowLan/src/lexer/lexer.c -o CMakeFiles/lexer.dir/src/lexer/lexer.c.s

# Object files for target lexer
lexer_OBJECTS = \
"CMakeFiles/lexer.dir/src/lexer/lexer.c.o"

# External object files for target lexer
lexer_EXTERNAL_OBJECTS =

liblexer.a: CMakeFiles/lexer.dir/src/lexer/lexer.c.o
liblexer.a: CMakeFiles/lexer.dir/build.make
liblexer.a: CMakeFiles/lexer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dan/Coding/MeowLan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library liblexer.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lexer.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lexer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lexer.dir/build: liblexer.a
.PHONY : CMakeFiles/lexer.dir/build

CMakeFiles/lexer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lexer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lexer.dir/clean

CMakeFiles/lexer.dir/depend:
	cd /home/dan/Coding/MeowLan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dan/Coding/MeowLan /home/dan/Coding/MeowLan /home/dan/Coding/MeowLan/build /home/dan/Coding/MeowLan/build /home/dan/Coding/MeowLan/build/CMakeFiles/lexer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lexer.dir/depend

