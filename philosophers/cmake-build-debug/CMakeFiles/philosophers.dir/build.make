# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Users/tgriffit/Documents/myApps/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/tgriffit/Documents/myApps/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tgriffit/projects/philosophers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tgriffit/projects/philosophers/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/philosophers.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/philosophers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/philosophers.dir/flags.make

CMakeFiles/philosophers.dir/main.c.o: CMakeFiles/philosophers.dir/flags.make
CMakeFiles/philosophers.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tgriffit/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/philosophers.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers.dir/main.c.o -c /Users/tgriffit/projects/philosophers/main.c

CMakeFiles/philosophers.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/tgriffit/projects/philosophers/main.c > CMakeFiles/philosophers.dir/main.c.i

CMakeFiles/philosophers.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/tgriffit/projects/philosophers/main.c -o CMakeFiles/philosophers.dir/main.c.s

CMakeFiles/philosophers.dir/utils/ft_atoi.c.o: CMakeFiles/philosophers.dir/flags.make
CMakeFiles/philosophers.dir/utils/ft_atoi.c.o: ../utils/ft_atoi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tgriffit/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/philosophers.dir/utils/ft_atoi.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers.dir/utils/ft_atoi.c.o -c /Users/tgriffit/projects/philosophers/utils/ft_atoi.c

CMakeFiles/philosophers.dir/utils/ft_atoi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers.dir/utils/ft_atoi.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/tgriffit/projects/philosophers/utils/ft_atoi.c > CMakeFiles/philosophers.dir/utils/ft_atoi.c.i

CMakeFiles/philosophers.dir/utils/ft_atoi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers.dir/utils/ft_atoi.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/tgriffit/projects/philosophers/utils/ft_atoi.c -o CMakeFiles/philosophers.dir/utils/ft_atoi.c.s

CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.o: CMakeFiles/philosophers.dir/flags.make
CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.o: ../utils/ft_str_isdigit.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tgriffit/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.o -c /Users/tgriffit/projects/philosophers/utils/ft_str_isdigit.c

CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/tgriffit/projects/philosophers/utils/ft_str_isdigit.c > CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.i

CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/tgriffit/projects/philosophers/utils/ft_str_isdigit.c -o CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.s

CMakeFiles/philosophers.dir/utils/ft_isdigit.c.o: CMakeFiles/philosophers.dir/flags.make
CMakeFiles/philosophers.dir/utils/ft_isdigit.c.o: ../utils/ft_isdigit.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tgriffit/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/philosophers.dir/utils/ft_isdigit.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/philosophers.dir/utils/ft_isdigit.c.o -c /Users/tgriffit/projects/philosophers/utils/ft_isdigit.c

CMakeFiles/philosophers.dir/utils/ft_isdigit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/philosophers.dir/utils/ft_isdigit.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/tgriffit/projects/philosophers/utils/ft_isdigit.c > CMakeFiles/philosophers.dir/utils/ft_isdigit.c.i

CMakeFiles/philosophers.dir/utils/ft_isdigit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/philosophers.dir/utils/ft_isdigit.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/tgriffit/projects/philosophers/utils/ft_isdigit.c -o CMakeFiles/philosophers.dir/utils/ft_isdigit.c.s

# Object files for target philosophers
philosophers_OBJECTS = \
"CMakeFiles/philosophers.dir/main.c.o" \
"CMakeFiles/philosophers.dir/utils/ft_atoi.c.o" \
"CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.o" \
"CMakeFiles/philosophers.dir/utils/ft_isdigit.c.o"

# External object files for target philosophers
philosophers_EXTERNAL_OBJECTS =

philosophers: CMakeFiles/philosophers.dir/main.c.o
philosophers: CMakeFiles/philosophers.dir/utils/ft_atoi.c.o
philosophers: CMakeFiles/philosophers.dir/utils/ft_str_isdigit.c.o
philosophers: CMakeFiles/philosophers.dir/utils/ft_isdigit.c.o
philosophers: CMakeFiles/philosophers.dir/build.make
philosophers: CMakeFiles/philosophers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/tgriffit/projects/philosophers/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable philosophers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/philosophers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/philosophers.dir/build: philosophers
.PHONY : CMakeFiles/philosophers.dir/build

CMakeFiles/philosophers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/philosophers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/philosophers.dir/clean

CMakeFiles/philosophers.dir/depend:
	cd /Users/tgriffit/projects/philosophers/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tgriffit/projects/philosophers /Users/tgriffit/projects/philosophers /Users/tgriffit/projects/philosophers/cmake-build-debug /Users/tgriffit/projects/philosophers/cmake-build-debug /Users/tgriffit/projects/philosophers/cmake-build-debug/CMakeFiles/philosophers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/philosophers.dir/depend

